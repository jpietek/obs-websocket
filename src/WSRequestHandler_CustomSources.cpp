#include <QString>
#include <QImage>
#include <QFile>
#include "Utils.h"
#include <unistd.h>
#include <math.h>
#include <thread>
#include <chrono>

#include <QHostInfo>

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

QString GetRandomString(int len) {
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

   QString randomString;
   for(int i=0; i<len; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

void WSRequestHandler::HandleGetSourceImage(SourceThumbData* data) {
  blog(LOG_INFO, "inside get source image");
  QString cmd;
  
  if(!data->isMedia) {
    cmd = "DISPLAY=:0 python /apps/tools/screenshot.py " + data->url
      + " " + data->image_id + ".png";
  } else {
    cmd = "ffmpeg -i " + data->url + " -vframes 1 -filter scale='640:-1' /var/www/html/thumbs/" + data->image_id;
    + ".jpg";
  }
  
  int ret = system(cmd.toUtf8());
  if(ret > 0) {
    blog(LOG_INFO, "failed to create thumbnail for source: %s", data->url);
    return;
  }
  
  QString url = "http://" + QHostInfo::localHostName() 
    + ".aws-dev.intranet/thumbs/" 
    + data->image_id + (data->isMedia ? ".jpg" : ".png");
    
  blog(LOG_INFO, "image url: %s", url.toUtf8());
  
  WSEvents::thumbsLock.lock();
  WSEvents::processedSourceThumbs.insert(data->source_name.toUtf8(), url);
  WSEvents::thumbsLock.unlock();
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
  
  OBSDataAutoRelease source_settings = obs_data_create();
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
  
  obs_enter_graphics();
  obs_scene_atomic_update(new_scene, AddSource, &data);
  obs_leave_graphics();
  
  blog(LOG_INFO, "before src thumb data struct");
  
  SourceThumbData* src_thumb_data = new SourceThumbData();
  
  src_thumb_data->source_name = source_name;
  QString rand = GetRandomString(32);
  blog(LOG_INFO, "source name rand it: %s", rand.toUtf8());
  src_thumb_data->image_id = rand;
  src_thumb_data->url = input_url;
  src_thumb_data->isMedia = true;
  
  blog(LOG_INFO, "before get media source image thread");
  std::thread t1(WSRequestHandler::HandleGetSourceImage, src_thumb_data);
  t1.detach();

  obs_source_t* previewScene = obs_frontend_get_current_preview_scene();
  obs_source_t* programScene = obs_frontend_get_current_scene();
  OBSDataAutoRelease audio_opts = obs_data_create();
  
  if(WSRequestHandler::audioMonitorStarted) {
    bool audioMonitorAdded = false;
    
    if(previewScene != nullptr) {
      const char* previewSceneName = obs_source_get_name(previewScene);
      blog(LOG_INFO, "add media preview name: %s", previewSceneName, scene_name);
      if(strcmp(previewSceneName, scene_name) == 0 /*&& !WSRequestHandler::audioMonitorMap.empty()*/) {
	const char* programSceneName = obs_source_get_name(programScene);

	blog(LOG_INFO, "add media program scene: %s", programSceneName);
	bool output = (programScene != nullptr && strcmp(programSceneName, scene_name) == 0) ? true : false;
	obs_data_set_bool(audio_opts, "output", output);
	WSRequestHandler::TurnOnSourceAudioMonitor(src, audio_opts);
	audioMonitorAdded = true;
      }
    } else if(programScene != nullptr && strcmp(obs_source_get_name(programScene), scene_name) == 0 
      /*&& !WSRequestHandler::audioMonitorMap.empty()*/ && !audioMonitorAdded) {
       obs_data_set_bool(audio_opts, "output", true);
       WSRequestHandler::TurnOnSourceAudioMonitor(src, audio_opts);
    }
    
     if(previewScene != nullptr)
       obs_source_release(previewScene);

     if(programScene != nullptr)
       obs_source_release(programScene);
  }

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
  obs_source_t* s = obs_get_source_by_name(source_name);
  TurnOffSourceAudio(nullptr, s);
  obs_source_release(s);
  
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
  
  obs_enter_graphics();
  obs_scene_atomic_update(new_scene, AddSource, &data);
  obs_leave_graphics();
  
  blog(LOG_INFO, "before browser source release");
  obs_source_release(browser);
  
  SourceThumbData* src_thumb_data = new SourceThumbData();
  src_thumb_data->url = url;
  src_thumb_data->image_id = GetRandomString(32);
  src_thumb_data->source_name = source_name;
  src_thumb_data->isMedia = false;
  
  blog(LOG_INFO, "before get source image thread");
  std::thread t1(WSRequestHandler::HandleGetSourceImage, src_thumb_data);
  t1.detach();
  
  OBSDataAutoRelease resp = obs_data_create();
  obs_data_set_string(resp, "sourceName", source_name);
  req->SendOKResponse(resp);
}

void WSRequestHandler::HandleClearSession(WSRequestHandler* req) {
  obs_enum_sources(RemoveSource, nullptr);
  req->SendOKResponse();
}

bool WSRequestHandler::RemoveSource(void* p, obs_source_t* src) {
  TurnOffSourceAudio(nullptr, src);
  obs_source_remove(src);
  return true;
}

void WSRequestHandler::ClearScene(const char* name) {
   auto removeSceneItemSource = [](obs_scene_t* scene, obs_sceneitem_t* item, void* params) -> bool {
      obs_source_t* s = obs_sceneitem_get_source(item);
      RemoveSource(nullptr, s);
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
