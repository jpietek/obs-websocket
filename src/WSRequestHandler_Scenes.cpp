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
 void WSRequestHandler::HandleSetCurrentScene(WSRequestHandler* req) {
    if (!req->hasField("scene-name")) {
        req->SendErrorResponse("missing request parameters");
        return;
    }
    
    const char* sceneName = obs_data_get_string(req->data, "scene-name");
   
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
void WSRequestHandler::HandleGetCurrentScene(WSRequestHandler* req) {
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
void WSRequestHandler::HandleGetSceneList(WSRequestHandler* req) {
    OBSSourceAutoRelease currentScene = obs_frontend_get_current_scene();
    OBSDataArrayAutoRelease scenes = Utils::GetScenes();

    OBSDataAutoRelease data = obs_data_create();
    obs_data_set_string(data, "current-scene",
        obs_source_get_name(currentScene));
    obs_data_set_array(data, "scenes", scenes);

    req->SendOKResponse(data);
}

void WSRequestHandler::HandleSetSceneItemOrder(WSRequestHandler* req) {
    QString sceneName = obs_data_get_string(req->data, "scene");
    
    obs_scene_t* scene = obs_scene_from_source(Utils::GetSceneFromNameOrCurrent(sceneName));
    
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
   auto countItems = [](obs_scene_t* scene, obs_sceneitem_t* item, void* params) -> bool {
      (*(int*) params)++;
      return true;
   };
   
   obs_scene_enum_items(scene, countItems, &count);
   blog(LOG_INFO, "scene item count %i", count);

   size_t visibleCount = obs_data_array_count(items);
   
   std::deque<int> emptySlots;
   std::vector<obs_sceneitem_t*> newOrder;
   newOrder.reserve(count);
   blog(LOG_INFO, "after scene check reserve");
    
   for (int i = 0; i < count; i++) {
      OBSDataAutoRelease item = obs_data_array_item(items, i);
      obs_sceneitem_t* sceneItem = Utils::GetSceneItemFromItem(obs_scene_get_source(scene), item);
      
      if(!obs_sceneitem_visible(sceneItem)) {
         newOrder[i] = Utils::GetSceneItemFromItem(obs_scene_get_source(scene), item);
      } else {
         blog(LOG_INFO, "scene item visible, pushing empty slot %i", i);
         emptySlots.push_back(i);
      }
   }
  
  blog(LOG_INFO, "empty slots size: %i", emptySlots.size());
  blog(LOG_INFO, "visible count %i", visibleCount);
  
    for (size_t i = 0; i < visibleCount; i++) {
        OBSDataAutoRelease item = obs_data_array_item(items, i);
        obs_sceneitem_t* sceneItem = Utils::GetSceneItemFromItem(obs_scene_get_source(scene), item);
        if (!sceneItem) {
            req->SendErrorResponse("Invalid sceneItem id or name in order");
            blog(LOG_INFO, "can't get scene item");
            return;
        }
        
        blog(LOG_INFO, "got scene item");
        for (size_t j = 0; j < i; j++) {
            if (sceneItem == newOrder[j]) {
                req->SendErrorResponse("Duplicate sceneItem in specified order");
                for (size_t i = 0; i < count; i++) {
                    obs_sceneitem_release(newOrder[i]);
                 }
                return;
            }
        }
        int n = emptySlots.front();
        blog(LOG_INFO, "pop empty slots: %i", n);
        newOrder[n] = sceneItem;
        emptySlots.pop_front();
    }
    
    bool res = obs_scene_reorder_items(scene, newOrder.data(), count);
    blog(LOG_INFO, "scene reoder result %i", res);
    
    obs_scene_release(scene);
    for (size_t i = 0; i < count; i++) {
        obs_sceneitem_release(newOrder[i]);
    }
    
    req->SendOKResponse();

}
