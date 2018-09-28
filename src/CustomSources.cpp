#include "CustomSources.h"

// public

void CustomSources::UpdateOverlay(WSRequestHandler* req) {
   const char* url = obs_data_get_string(req->data, "url");
   const char* sourceName = obs_data_get_string(req->data, "sourceName");
   const char* localFile = obs_data_get_string(req->data, "localFile");

   obs_source_t* src = obs_get_source_by_name(sourceName);
   int width = obs_source_get_width(src);
   int height = obs_source_get_height(src);
   obs_source_release(src);
   
   blog(LOG_INFO, "before thumb creator run - overlay refresh %s %s %s", url, sourceName, localFile);
   ThumbCreator* thumbCreator = new ThumbCreator(QString::fromLocal8Bit(url),
       QString::fromLocal8Bit(sourceName), GetRandomString(32), QString::number(width), QString::number(height), false);
   
   thumbCreator->run();
   
   OBSDataAutoRelease sourceSettings = obs_data_create();
   obs_data_set_string(sourceSettings, "url", url);
   if(localFile != nullptr) {
       obs_data_set_string(sourceSettings, "local_file", localFile);
   }
  
   obs_data_set_obj(req->data, "sourceSettings", sourceSettings);
   blog(LOG_INFO, "handle source settings");
   WSRequestHandler::HandleSetSourceSettings(req);
}

void CustomSources::RefreshSource(WSRequestHandler* req) {
   obs_source_t* source = obs_get_source_by_name(obs_data_get_string(req->data, "sourceName"));
   const char* type = obs_source_get_id(source);
   if(strcmp(type, "ffmpeg_source") != 0) {
      return;
   }
   
   obs_data_t* emptySettings = obs_data_create();
   obs_source_update(source, emptySettings);
   obs_source_update_properties(source);
   obs_source_active(source);
}

void CustomSources::HandleRemoveSource(WSRequestHandler* req) {
  blog(LOG_INFO, "inside remove source");
  const char* sourceNameToRemove = obs_data_get_string(req->data, "sourceName");
  RemoveSourceByName(sourceNameToRemove);
  req->SendOKResponse(nullptr);
}

void CustomSources::HandleClearScene(WSRequestHandler* req) {
  const char* sceneName = obs_data_get_string(req->data, "sceneName");
  
  obs_source_t* previewScene = obs_frontend_get_current_preview_scene();
  const char* previewSceneName = obs_source_get_name(previewScene);
  
  obs_source_t* blankScene = Utils::GetSceneFromNameOrCurrent("Scene 9"); 
  obs_frontend_set_current_preview_scene(blankScene);
  
  if(strcmp(previewSceneName, sceneName) == 0) {
      blog(LOG_INFO, "clearing preview scene, set preview to blank");
      obs_source_t* blankScene = Utils::GetSceneFromNameOrCurrent("Scene 9");
      obs_frontend_set_current_preview_scene(blankScene);
  }
   
  CustomSources::ClearScene(sceneName);
  req->SendOKResponse(nullptr);
}

void CustomSources::HandleAddMediaSource(WSRequestHandler* req) {
  blog(LOG_INFO, "inside add scene");
  
  const char* scene_name = obs_data_get_string(req->data, "sceneName");
  const char* source_name = obs_data_get_string(req->data, "sourceName");
  
  bool sourceReference = obs_data_get_bool(req->data, "sourceReference");
  
  obs_source_t* existing_source = obs_get_source_by_name(source_name);
  if(existing_source != nullptr && !sourceReference) {
    blog(LOG_INFO, "source already exists: %s", obs_source_get_name(existing_source));
    obs_source_release(existing_source);
    req->SendErrorResponse("source already exists");
    return;
  }
  
  obs_source_t* src = nullptr;
  
  if(sourceReference) {
     src = existing_source;
  } else {
     obs_source_release(existing_source);
  
     OBSDataAutoRelease source_settings = obs_data_create();
     const char* input_url = obs_data_get_string(req->data, "url");
     bool loop = obs_data_get_bool(req->data, "loop");
     
     obs_data_set_bool(source_settings, "is_local_file", false);
     obs_data_set_bool(source_settings, "hw_decode", true);
     obs_data_set_bool(source_settings, "clear_on_media_end", false);
     obs_data_set_string(source_settings, "input", input_url);
     obs_data_set_bool(source_settings, "restart_on_activate", false);
     obs_data_set_bool(source_settings, "looping", loop);
     
     blog(LOG_INFO, "source created:  %s", source_name);
     src = obs_source_create("ffmpeg_source", source_name, source_settings, NULL);

     blog(LOG_INFO, "before src thumb data struct");
     
     ThumbCreator* thumbCreator = new ThumbCreator(QString::fromLocal8Bit(input_url),
         QString::fromLocal8Bit(source_name), GetRandomString(32), "", "", true);
     
     blog(LOG_INFO, "before thumb creator run");
     thumbCreator->run();
  }
  
  obs_scene_t* new_scene = obs_scene_from_source(obs_get_source_by_name(scene_name));
  
  AddSourceData data;
  data.source = src;
  data.visible = true;
  
  obs_enter_graphics();
  obs_scene_atomic_update(new_scene, AddSource, &data);
  obs_leave_graphics();
  
  obs_source_t* previewScene = obs_frontend_get_current_preview_scene();
  obs_source_t* programScene = obs_frontend_get_current_scene();
  OBSDataAutoRelease audio_opts = obs_data_create();
  
  if(Audio::isAudioMonitorStarted()) {
    bool audioMonitorAdded = false;
    
    if(previewScene != nullptr) {
      const char* previewSceneName = obs_source_get_name(previewScene);
      blog(LOG_INFO, "add media preview name: %s", previewSceneName, scene_name);
      if(strcmp(previewSceneName, scene_name) == 0) {
         const char* programSceneName = obs_source_get_name(programScene);

         blog(LOG_INFO, "add media program scene: %s", programSceneName);
         bool output = (programScene != nullptr && strcmp(programSceneName, scene_name) == 0) ? true : false;
         obs_data_set_bool(audio_opts, "output", output);
         Audio::TurnOnSourceAudioMonitor(src, audio_opts);
         audioMonitorAdded = true;
      }
    } else if(programScene != nullptr && strcmp(obs_source_get_name(programScene), scene_name) == 0 
       && !audioMonitorAdded) {
       obs_data_set_bool(audio_opts, "output", true);
       Audio::TurnOnSourceAudioMonitor(src, audio_opts);
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

void CustomSources::HandleClearSession(WSRequestHandler* req) {
  obs_source_t* previewScene = obs_frontend_get_current_preview_scene();
  obs_source_t* blankScene = Utils::GetSceneFromNameOrCurrent("Scene 9"); 
  obs_frontend_set_current_preview_scene(blankScene);
  
  obs_enum_sources(RemoveSource, nullptr);
  
  sleep(1);
  
  //ugly hack: try to remove one more time...
  obs_enum_sources(RemoveSource, nullptr);
  
  sleep(1);
  
  obs_frontend_set_current_preview_scene(previewScene);
  obs_source_release(previewScene);
  req->SendOKResponse();
}

void CustomSources::HandleAddBrowserSource(WSRequestHandler* req) {
  const char* scene_name = obs_data_get_string(req->data, "sceneName");
  const char* source_name = obs_data_get_string(req->data, "sourceName");
  double fps = obs_data_get_double(req->data, "fps");
  bool local = obs_data_get_bool(req->data, "isLocal");
  
  bool sourceReference = obs_data_get_bool(req->data, "sourceReference");
  
  obs_source_t* existing_source = obs_get_source_by_name(source_name);
  if(existing_source != nullptr && !sourceReference) {
    blog(LOG_INFO, "source already exists: %s", obs_source_get_name(existing_source));
    obs_source_release(existing_source);
    req->SendErrorResponse("source already exists");
    return;
  }
  
   obs_source_t* browser = nullptr;
  
   if(sourceReference) {
      browser = existing_source;
   } else {
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
      obs_data_set_bool(browser_settings, "hide_scrollbars", true);
  
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
  
      browser = obs_source_create("linuxbrowser-source", source_name, browser_settings, NULL);
      blog(LOG_INFO, "browser created:  %s %s", source_name, url);
      
      ThumbCreator* thumbCreator = new ThumbCreator(
         QString::fromLocal8Bit(url),
         QString::fromLocal8Bit(source_name),
         GetRandomString(32),
         QString::number(browser_width),
         QString::number(browser_height),
         false
      );
  
      thumbCreator->run();
   }
      
   obs_scene_t* new_scene = obs_scene_from_source(obs_get_source_by_name(scene_name));
    
   AddSourceData data;
   data.source = browser;
   data.visible = true;
  
   obs_enter_graphics();
   obs_scene_atomic_update(new_scene, AddSource, &data);
   obs_leave_graphics();
  
   blog(LOG_INFO, "before browser source release");
   obs_source_release(browser);      
  
   OBSDataAutoRelease resp = obs_data_create();
   obs_data_set_string(resp, "sourceName", source_name);
   req->SendOKResponse(resp);
}

// private

QString CustomSources::GetRandomString(int len) {
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

   QString randomString;
   for(int i=0; i < len; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   
   blog(LOG_INFO, "random string: %s", randomString.toStdString().c_str());
   return randomString;
}

void CustomSources::AddSource(void *_data, obs_scene_t *scene)
{
   AddSourceData* data = (AddSourceData*)_data;
   OBSSceneItem sceneitem;
   sceneitem = obs_scene_add(scene, data->source);
   obs_sceneitem_set_visible(sceneitem, data->visible);
}

bool CustomSources::RemoveSource(void* p, obs_source_t* src) {
  Audio::TurnOffSourceAudio(nullptr, src);
  obs_source_remove(src);
  return true;
}

void CustomSources::ClearScene(const char* name) {
   auto removeSceneItemSource = [](obs_scene_t* scene, obs_sceneitem_t* item, void* params) -> bool {
      obs_source_t* s = obs_sceneitem_get_source(item);
      RemoveSource(nullptr, s);
      return true;
  };
  OBSScene scene = obs_scene_from_source(obs_get_source_by_name(name));
  obs_scene_enum_items(scene, removeSceneItemSource, nullptr);
}

bool CustomSources::ActivateSource(obs_scene_t* scene, obs_sceneitem_t* item, void* params) {
   obs_source_t* s = obs_sceneitem_get_source(item);
   const char* sourceName = obs_source_get_name(s);
   const char* type = obs_source_get_id(s);
   if(strcmp(type, "ffmpeg_source") != 0) {
      return true;
   }
   
   obs_data_t* sourceSettings = obs_source_get_settings(s);   
   
   RemoveSourceByName(sourceName);
   obs_source_t* restartedSource = obs_source_create("ffmpeg_source", sourceName, sourceSettings, NULL);
   
   AddSourceData data;
   data.source = restartedSource;
   data.visible = true;
   
   obs_enter_graphics();
   obs_scene_atomic_update(scene, AddSource, &data);
   obs_leave_graphics();
   
   obs_source_release(restartedSource);
   return true;
}

void CustomSources::RemoveSourceByName(const char* sourceNameToRemove) {
  obs_source_t* s = obs_get_source_by_name(sourceNameToRemove);
  
  obs_source_t* previewScene = obs_frontend_get_current_preview_scene();
  const char* previewSceneName = obs_source_get_name(previewScene);
  
   auto checkPreviewScene = [](obs_scene_t* scene, obs_sceneitem_t* item, void* params) -> bool {
      obs_source_t* curSrc = obs_sceneitem_get_source(item);
      const char* curSourceName = obs_source_get_name(curSrc);
      const char* sourceNameToRemove = (const char*) params;
      blog(LOG_INFO, "remove src to remove vs cur preview src: %s %s", curSourceName, sourceNameToRemove);
       if(strcmp(curSourceName, sourceNameToRemove) == 0) {
          blog(LOG_INFO, "removing current preview source, set blank scene as preview");
          obs_source_t* blankScene = Utils::GetSceneFromNameOrCurrent("Scene 9");
          obs_frontend_set_current_preview_scene(blankScene);
          obs_source_release(blankScene);
      }
      return true;
  };
  
  obs_scene_enum_items(obs_scene_from_source(previewScene), checkPreviewScene, (void*)sourceNameToRemove);
  
  Audio::TurnOffSourceAudio(nullptr, s);
  obs_source_release(s);
  
  obs_source_remove(s);
  obs_frontend_set_current_preview_scene(previewScene);
  obs_source_release(previewScene);
}
