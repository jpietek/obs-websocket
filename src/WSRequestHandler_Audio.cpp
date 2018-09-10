#include "WSRequestHandler.h"
#include "WSEvents.h"
#include "math.h"

void WSRequestHandler::PlayAudio(WSRequestHandler* req) {
  const char* name = obs_data_get_string(req->data, "sceneName");
  obs_source_t* s = obs_get_source_by_name(name);
  obs_source_set_muted(s, false);
  
  blog(LOG_INFO, "switch audio monitor source: %s", name);
  obs_enum_sources(TurnOffSourceAudio, nullptr);
  
  obs_source_t* programSource = obs_frontend_get_current_scene();
  const char* programName = obs_source_get_name(programSource);
  obs_source_release(programSource);
  
  blog(LOG_INFO, "compare scene with program: %s %s", name, programName);
  OBSData audio_opts = obs_data_create();
  if(strcmp(name, programName) == 0) {
    blog(LOG_INFO, "source from active scene, output true");
    obs_data_set_bool(audio_opts, "output", true);
  } else {
    blog(LOG_INFO, "source not from current scene, output false");
    obs_data_set_bool(audio_opts, "output", false);
  }
  
  blog(LOG_INFO, "turn on audio monitor");
  obs_scene_t* scene = obs_scene_from_source(s);
  obs_scene_enum_items(scene, TurnOnAudioMonitor, audio_opts);
  obs_scene_release(scene);
  WSRequestHandler::audioMonitorStarted = true;
  req->SendOKResponse(nullptr);
}

void WSRequestHandler::StopAudio(WSRequestHandler* req) {
  WSRequestHandler::audioMonitorStarted = false;
  const char* name = obs_data_get_string(req->data, "sceneName");
  obs_source_t* s = obs_get_source_by_name(name);
  blog(LOG_INFO, "switch audio monitor source: %s", name);
  obs_scene_enum_items(obs_scene_from_source(s), TurnOffAudioMonitor, nullptr);
  obs_source_release(s);
  req->SendOKResponse(nullptr);
}

bool WSRequestHandler::TurnOnAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p) {
  if(!obs_sceneitem_visible(item)) {
     return true;
  }
  
  obs_data_t* audio_opts = (obs_data_t*) p;
  obs_source_t* source = obs_sceneitem_get_source(item);
  
  return WSRequestHandler::TurnOnSourceAudioMonitor(source, audio_opts);
}

bool WSRequestHandler::TurnOnSourceAudioMonitor(obs_source_t* source, obs_data_t* audio_opts) {
   const char* sourceName = obs_source_get_name(source);
  
  blog(LOG_INFO, "switch audio monitor source: %s", sourceName);
  if(obs_data_get_bool(audio_opts, "output")) {
    obs_source_set_monitoring_type(source, (obs_monitoring_type)2);
  } else {
    obs_source_set_monitoring_type(source, (obs_monitoring_type)1);
  }
  
  WSRequestHandler::audioLock.lock();
  
  obs_data_t* data = obs_data_create();
  obs_data_set_string(data, "sourceName", sourceName);
  
  obs_volmeter_t* volmeter = obs_volmeter_create(OBS_FADER_CUBIC);
  obs_volmeter_set_update_interval(volmeter, 10);
  obs_volmeter_attach_source(volmeter, source);
  obs_volmeter_add_callback(volmeter, HandleVolumeLevel, data);
  WSRequestHandler::audioMonitorMap.insert(sourceName, volmeter);
  
  blog(LOG_INFO, "setup buffer");
  boost::circular_buffer<double>* buf = new boost::circular_buffer<double>(100);
  buf->set_capacity(100);
  WSRequestHandler::audioBuffer[sourceName] = buf;
  WSRequestHandler::audioLock.unlock();

  return true;
}

bool WSRequestHandler::TurnOffSourceAudio(void *p, obs_source* source) {
  const char* sourceName = obs_source_get_name(source);
  obs_source_set_monitoring_type(source, (obs_monitoring_type)0);
  
  WSRequestHandler::audioLock.lock();
  obs_volmeter_t* volmeter = WSRequestHandler::audioMonitorMap[sourceName];
  obs_volmeter_destroy(volmeter);
  WSRequestHandler::audioMonitorMap.remove(sourceName);
  WSEvents::audioMonitorLevel.remove(sourceName);
  WSRequestHandler::audioLock.unlock();
}

bool WSRequestHandler::TurnOffAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p) {
  obs_source_t* source = obs_sceneitem_get_source(item);
  const char* sourceName = obs_source_get_name(source);
  obs_source_set_monitoring_type(source, (obs_monitoring_type)0);
  
  WSRequestHandler::audioLock.lock();
  obs_volmeter_t* volmeter = WSRequestHandler::audioMonitorMap[sourceName];
  obs_volmeter_destroy(volmeter);
  WSRequestHandler::audioMonitorMap.remove(sourceName);
  WSEvents::audioMonitorLevel.remove(sourceName);
  WSRequestHandler::audioLock.unlock();
  return true;
}

void WSRequestHandler::HandleVolumeLevel(void *data,
	const float magnitude[MAX_AUDIO_CHANNELS],
	const float peak[MAX_AUDIO_CHANNELS],
	const float inputPeak[MAX_AUDIO_CHANNELS])
{ 
  	if(data == nullptr) {
	  blog(LOG_INFO, "audio monitoring: got null data, sth went wrong");
	}
	
   const char* sourceName = obs_data_get_string((obs_data_t*)data, "sourceName");
	double peakLinear = pow(10.0f, peak[1] / 20.0f);
	double inputPeakLinear = pow(10.0f, inputPeak[1] / 20.0f);
	
   boost::circular_buffer<double>* buf = WSRequestHandler::audioBuffer[sourceName];
   buf->push_back(peakLinear);
   
   blog(LOG_INFO, "buffer size: %i %i", buf->size(), buf->capacity());
   
   double maxPeak = 0;
   double pows = 0;
   for(int i = 0; i < buf->size(); i++) {
      maxPeak = std::max(buf->at(i), maxPeak);
      pows += std::pow(buf->at(i), 2);
   }
   
   double rms = std::sqrt(pows / 100.0);

	obs_data_t* levels = obs_data_create();
   blog(LOG_INFO, "audio level: %f %f", rms, maxPeak);
	obs_data_set_double(levels, "peak", rms);
	obs_data_set_double(levels, "input peak", inputPeakLinear);
	
	WSEvents::audioMonitorLevel[sourceName] = levels;
}
  
  
