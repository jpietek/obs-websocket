#include <QString>
#include <QImage>
#include <QFile>
#include "Utils.h"
#include <unistd.h>
#include <math.h>
#include <thread>
#include <chrono>

#include "WSRequestHandler.h"
#include "WSEvents.h"

struct AddSourceData {
   obs_source_t* source;
   bool visible;
};

QMutex renderLock {
};

QMutex browserLock {
};

QMutex mediaSourceLock {
};

void GenerateRandom(char* id, int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        id[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    id[len] = '\0';
    blog(LOG_INFO, "img id: %s", id);
}

void WSRequestHandler::HandleGetSourceImage(SourceThumbData* data) {
  std::string cmd;
  
  if(!data->isMedia) {
    cmd += "DISPLAY=:0 python /apps/tools/screenshot.py ";
    cmd += data->url;
    cmd += " ";
    cmd += data->image_id;
    cmd += ".png";
  } else {
    cmd += "ffmpeg -i ";
    cmd += data->url;
    cmd += " -vframes 1 -filter scale='640:-1' /var/www/html/thumbs/";
    cmd += data->image_id;
    cmd += ".jpg";
  }
  
  int ret = system(cmd.c_str());
  if(ret > 0) {
    blog(LOG_INFO, "failed to create thumbnail for source: %s", cmd.c_str());
    return;
  }
  
  std::string url = "http://";
  char* hostname = (char*) malloc(32 * sizeof(char));
  hostname[31] = '\0';
  gethostname(hostname, 31*sizeof(char));
  url += hostname;
  url += ".aws-dev.intranet/thumbs/";
  url += data->image_id;
  data->isMedia ? url += ".jpg" : url += ".png";
  blog(LOG_INFO, "image url: %s", url.c_str());
  
  char* url_t = (char*) malloc(sizeof(char) * strlen(url.c_str()));
  strcpy(url_t, strdup(url.c_str()));
  WSEvents::thumbsLock.lock();
  WSEvents::processedSourceThumbs.insert(data->source_name, url_t);
  WSEvents::thumbsLock.unlock();
  
  free(data);
}

void WSRequestHandler::HandleAddMediaSource(WSRequestHandler* req) {
  blog(LOG_INFO, "inside add scene");
  
  const char* scene_name = obs_data_get_string(req->data, "sceneName");
  const char* source_name = obs_data_get_string(req->data, "sourceName");
  
  obs_source_t* existing_source = obs_get_source_by_name(source_name);
  if(existing_source != nullptr) {
    blog(LOG_INFO, "source already exists: %s", obs_source_get_name(existing_source));
    obs_source_release(existing_source);
    req->SendErrorResponse("source already exists");
    return;
  }
  obs_source_release(existing_source);
  
  OBSData source_settings = obs_data_create();
  const char* input_url = obs_data_get_string(req->data, "url");

  long zoom = obs_data_get_int(req->data, "zoom");
  if(zoom <= 0 || zoom > 100) {
    zoom = 0;
  }
  obs_data_set_bool(source_settings, "is_local_file", false);
  obs_data_set_bool(source_settings, "hw_decode", true);
  obs_data_set_bool(source_settings, "clear_on_media_end", false);
  obs_data_set_string(source_settings, "input", input_url);
  obs_data_set_bool(source_settings, "restart_on_activate", false);
  obs_data_set_int(source_settings, "zoom", zoom);
  
  blog(LOG_INFO, "source created:  %s", source_name);
  obs_source_t* src = obs_source_create("ffmpeg_source", source_name, source_settings, NULL);
  obs_scene_t* new_scene = obs_scene_from_source(obs_get_source_by_name(scene_name));
  
  AddSourceData data;
  data.source = src;
  data.visible = true;
  
  obs_scene_atomic_update(new_scene, AddSource, &data);
  
  SourceThumbData* src_thumb_data = (struct SourceThumbData*) malloc(sizeof(struct SourceThumbData));
  src_thumb_data->source_name = (char *)malloc(sizeof(source_name));
  strcpy(src_thumb_data->source_name, source_name);
  
  char* id = (char*) malloc(32 * sizeof(char));
  GenerateRandom(id, 32);
  src_thumb_data->image_id = id;
  src_thumb_data->url = strdup(input_url);
  src_thumb_data->isMedia = true;
  
  blog(LOG_INFO, "before get media source image thread");
  std::thread t1(WSRequestHandler::HandleGetSourceImage, src_thumb_data);
  t1.detach();
  
  blog(LOG_INFO, "before media source release");
  obs_source_release(src);
  
  OBSDataAutoRelease resp = obs_data_create();
  obs_data_set_string(resp, "sourceName", source_name);
  req->SendOKResponse(resp);
}

void WSRequestHandler::AddSource(void *_data, obs_scene_t *scene)
{
   AddSourceData* data = (AddSourceData*)_data;
   OBSSceneItem sceneitem;
   sceneitem = obs_scene_add(scene, data->source);
   obs_sceneitem_set_visible(sceneitem, data->visible);
}

void WSRequestHandler::HandleRemoveSource(WSRequestHandler* req) {
  blog(LOG_INFO, "inside remove source");
  
  const char* source_name = obs_data_get_string(req->data, "sourceName");
  OBSSourceAutoRelease s = obs_get_source_by_name(source_name);
  
  TurnOffSourceAudio(nullptr, s);
  obs_source_remove(s);
   
  req->SendOKResponse(nullptr);
}

void WSRequestHandler::HandleAddBrowserSource(WSRequestHandler* req) {
  const char* scene_name = obs_data_get_string(req->data, "sceneName");
  const char* source_name = obs_data_get_string(req->data, "sourceName");
  double fps = obs_data_get_double(req->data, "fps");
  bool local = obs_data_get_bool(req->data, "isLocal");
  
  obs_source_t* existing_source = obs_get_source_by_name(source_name);
  if(existing_source != nullptr) {
    blog(LOG_INFO, "source already exists: %s", obs_source_get_name(existing_source));
    obs_source_release(existing_source);
    req->SendErrorResponse("source already exists");
    return;
  }
  obs_source_release(existing_source);
  
  obs_data_t* browser_settings = obs_data_create();
  const char* url = obs_data_get_string(req->data, "url");
  obs_data_set_bool(browser_settings, "is_local_file", local);
  if(local) {
    obs_data_set_string(browser_settings, "local_file", obs_data_get_string(req->data, "localFile"));
  } else {
    obs_data_set_string(browser_settings, "url", url);
  }
  
  obs_data_set_int(browser_settings, "zoom", 100);
  obs_data_set_int(browser_settings, "scroll_vertical", 3);
  obs_data_set_int(browser_settings, "fps", fps);
  
  int browser_width = obs_data_get_int(req->data, "width");
  int browser_height = obs_data_get_int(req->data, "height");
  
  obs_data_set_int(browser_settings, "height", browser_height);
  obs_data_set_int(browser_settings, "width", browser_width);
  
  OBSDataArrayAutoRelease cmd_arr = obs_data_array_create();
  OBSDataAutoRelease c1 = obs_data_create();
  obs_data_set_string(c1, "value", "--incognito");
  OBSDataAutoRelease c2 = obs_data_create();
  obs_data_set_string(c2, "value", "--disable-application-cache");
  OBSDataAutoRelease c3 = obs_data_create();
  obs_data_set_string(c3, "value", "--disable-local-storage");
  obs_data_array_push_back(cmd_arr, c1);
  obs_data_array_push_back(cmd_arr, c2);
  obs_data_array_push_back(cmd_arr, c3);
  obs_data_set_array(browser_settings, "cef_command_line", cmd_arr);
  
  obs_source_t* browser = obs_source_create("linuxbrowser-source", source_name, browser_settings, NULL);
  blog(LOG_INFO, "browser created:  %s %s", source_name, url);
  obs_scene_t* new_scene = obs_scene_from_source(obs_get_source_by_name(scene_name));
    
  AddSourceData data;
  data.source = browser;
  data.visible = true;
  
  obs_scene_atomic_update(new_scene, AddSource, &data);
  char* rand_image_id = (char*)malloc(32 * sizeof(char));
  GenerateRandom(rand_image_id, 32);
  blog(LOG_INFO, "rand_image_id: %s", rand_image_id);
  
  SourceThumbData* src_thumb_data = (struct SourceThumbData*) malloc(sizeof(struct SourceThumbData));
  src_thumb_data->url = strdup(url);
  src_thumb_data->image_id = rand_image_id;
  char* src_name_t = (char*) malloc(sizeof(source_name));
  strcpy(src_name_t, source_name);
  src_thumb_data->source_name = src_name_t;
  src_thumb_data->isMedia = false;
  
  blog(LOG_INFO, "before get source image thread");
  std::thread t1(WSRequestHandler::HandleGetSourceImage, src_thumb_data);
  t1.detach();
  
  blog(LOG_INFO, "before browser source release");
  obs_source_release(browser);
  
  OBSDataAutoRelease resp = obs_data_create();
  obs_data_set_string(resp, "sourceName", source_name);
  req->SendOKResponse(resp);
}

void WSRequestHandler::HandleClearSession(WSRequestHandler* req) {
  char scenes[][8] = {"Scene 1", "Scene 2", "Scene 3", "Scene 4", "Scene 5", "Scene 6", "Scene 7", "Scene 8"};
  for(int i = 0; i < 8; i++) {
    WSRequestHandler::ClearScene(scenes[i]);
  }
  req->SendOKResponse();
}

bool WSRequestHandler::RemoveSource(void* p, obs_scene_item* item) {
  obs_source_t* src = obs_sceneitem_get_source(item);
  TurnOffSourceAudio(nullptr, src);
  obs_source_remove(src);
  return true;
}

void WSRequestHandler::ClearScene(const char* name) {
   auto removeSceneItemSource = [](obs_scene_t* scene, obs_sceneitem_t* item, void* params) -> bool {
      RemoveSource(nullptr, item);
      return true;
  };
  OBSScene scene = obs_scene_from_source(obs_get_source_by_name(name));
  obs_scene_enum_items(scene, removeSceneItemSource, nullptr);
}

void WSRequestHandler::HandleClearScene(WSRequestHandler* req) {
  const char* scene_name = obs_data_get_string(req->data, "sceneName");
  WSRequestHandler::ClearScene(scene_name);
  req->SendOKResponse(nullptr);
}
