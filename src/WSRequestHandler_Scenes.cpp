#include <QString>
#include "Utils.h"

#include "WSRequestHandler.h"
#include "CustomSources.h"

/**
 * Switch to the specified scene.
 *
 * @param {String} `scene-name` Name of the scene to switch to.
 *
 * @api requests
 * @name SetCurrentScene
 * @category scenes
 * @since 0.3
 */
void WSRequestHandler::HandleSetCurrentScene(WSRequestHandler *req)
{
    if (!req->hasField("scene-name")) {
        req->SendErrorResponse("missing request parameters");
        return;
    }

    const char *sceneName = obs_data_get_string(req->data, "scene-name");

    OBSSourceAutoRelease source = obs_get_source_by_name(sceneName);

    if (source) {
        obs_frontend_set_current_scene(source);
        req->SendOKResponse();
    } else {
        req->SendErrorResponse("requested scene does not exist");
    }
}

/**
 * Get the current scene's name and source items.
 *
 * @return {String} `name` Name of the currently active scene.
 * @return {Source|Array} `sources` Ordered list of the current scene's source items.
 *
 * @api requests
 * @name GetCurrentScene
 * @category scenes
 * @since 0.3
 */
void WSRequestHandler::HandleGetCurrentScene(WSRequestHandler *req)
{
    OBSSourceAutoRelease currentScene = obs_frontend_get_current_scene();
    OBSDataArrayAutoRelease sceneItems = Utils::GetSceneItems(currentScene);

    OBSDataAutoRelease data = obs_data_create();
    obs_data_set_string(data, "name", obs_source_get_name(currentScene));
    obs_data_set_array(data, "sources", sceneItems);

    req->SendOKResponse(data);
}

/**
 * Get a list of scenes in the currently active profile.
 *
 * @return {String} `current-scene` Name of the currently active scene.
 * @return {Scene|Array} `scenes` Ordered list of the current profile's scenes (See `[GetCurrentScene](#getcurrentscene)` for more information).
 *
 * @api requests
 * @name GetSceneList
 * @category scenes
 * @since 0.3
 */
void WSRequestHandler::HandleGetSceneList(WSRequestHandler *req)
{
    OBSSourceAutoRelease currentScene = obs_frontend_get_current_scene();
    OBSDataArrayAutoRelease scenes = Utils::GetScenes();

    OBSDataAutoRelease data = obs_data_create();
    obs_data_set_string(data, "current-scene",
                        obs_source_get_name(currentScene));
    obs_data_set_array(data, "scenes", scenes);

    req->SendOKResponse(data);
}

class ReorderParams
{
public:
    std::deque<int> *emptySlots;
    std::vector<obs_sceneitem_t *> *newOrder;
    int count;

    ReorderParams(int count)
    {
        this->emptySlots = new std::deque<int>();
        this->newOrder = new std::vector<obs_sceneitem_t *> (count);
        this->count = 0;
    };
    ~ReorderParams()
    {
        delete emptySlots;
        delete newOrder;
    };
};

void WSRequestHandler::HandleSetSceneItemOrder(WSRequestHandler *req)
{
    QString sceneName = obs_data_get_string(req->data, "scene");

    obs_scene_t *scene = obs_scene_from_source(Utils::GetSceneFromNameOrCurrent(sceneName));

    if (!scene) {
        req->SendErrorResponse("requested scene doesn't exist");
        return;
    }

    OBSDataArrayAutoRelease items = obs_data_get_array(req->data, "items");
    if (!items) {
        req->SendErrorResponse("sceneItem order not specified");
        return;
    }

    int count = 0;
    auto countItems = [](obs_scene_t *scene, obs_sceneitem_t *item, void *params) -> bool {
        (* (int *) params)++;
        return true;
    };

    obs_scene_enum_items(scene, countItems, &count);
    blog(LOG_INFO, "scene item count %i", count);

    size_t item_count = obs_data_array_count(items);
    if (item_count == 0) {
        req->SendErrorResponse("cowardly refusing to rerder with empty item array");
        return;
    }

    ReorderParams *args = new ReorderParams(count);
    blog(LOG_INFO, "after scene check reserve");

    auto addInvisibleItems = [](obs_scene_t *scene, obs_sceneitem_t *item, void *params) -> bool {
        ReorderParams *reorderParams = (ReorderParams *) params;

        if (!obs_sceneitem_visible(item))
        {
            blog(LOG_INFO, "set not visible new order: %i", reorderParams->count);
            reorderParams->newOrder->at(reorderParams->count) = item;
        } else {
            blog(LOG_INFO, "scene item visible, pushing empty slot %i", reorderParams->count);
            reorderParams->emptySlots->push_back(reorderParams->count);
        }
        reorderParams->count++;
        return true;
    };

    obs_scene_enum_items(scene, addInvisibleItems, args);

    blog(LOG_INFO, "empty slots size: %zu", args->emptySlots->size());
    blog(LOG_INFO, "items got from req %zu", item_count);

    if ((size_t) args->emptySlots->size() != item_count) {
        req->SendErrorResponse("request item count does not match visible item count in a scene");
        return;
    }

    for (size_t i = 0; i < item_count; i++) {
        OBSDataAutoRelease item = obs_data_array_item(items, i);
        obs_sceneitem_t *sceneItem = Utils::GetSceneItemFromItem(obs_scene_get_source(scene), item);
        if (!sceneItem) {
            req->SendErrorResponse("Invalid sceneItem id or name in order");
            blog(LOG_INFO, "can't get scene item");
            return;
        }

        int n = args->emptySlots->front();
        blog(LOG_INFO, "pop empty slots: %i", n);
        args->newOrder->at(n) = sceneItem;
        args->emptySlots->pop_front();
        obs_sceneitem_release(sceneItem);
    }

    blog(LOG_INFO, "new order size: %zu", args->newOrder->size());
    bool res = obs_scene_reorder_items(scene, args->newOrder->data(), count);
    blog(LOG_INFO, "scene reorder result: %i", res);

    blog(LOG_INFO, "before scene release");
    obs_scene_release(scene);

    blog(LOG_INFO, "before args destructor");
    delete args;

    blog(LOG_INFO, "before send ok response");
    req->SendOKResponse();
}
