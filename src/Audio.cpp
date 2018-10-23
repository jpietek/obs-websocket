#include "Audio.h"

QHash<QString, obs_volmeter_t*> Audio::audioMonitorMap;
QHash<QString, double> Audio::audioMonitorLevel;
QHash<QString, boost::circular_buffer<double>*> Audio::audioBuffer;
QMutex Audio::audioLock;
bool Audio::audioMonitorStarted = false;

// public 

bool Audio::areLevelsEmpty() {
   return audioMonitorLevel.empty();
}

void Audio::startAudioMonitor() {
   audioMonitorStarted = true;
}

bool Audio::isAudioMonitorStarted() {
   return audioMonitorStarted;
}


QHash<QString, double> Audio::GetAudioLevels() {
   return audioMonitorLevel;
}

void Audio::SetProgramAudioVolume(WSRequestHandler* req) {   
   blog(LOG_INFO, "before faders get");
   obs_fader** faders = (struct obs_fader**) obs_audio_mix_faders();
   blog(LOG_INFO, "get program fader");
   obs_fader* programFader = faders[0];
  
   float normalizedVolume = obs_data_get_double(req->data, "volumeLevel");
   float db = 60.0 * normalizedVolume - 60.0;
   blog(LOG_INFO, "program fader values %f %f", normalizedVolume, db);
   obs_fader_set_db(programFader, db);
  
   req->SendOKResponse();
}

void Audio::PlayAudio(WSRequestHandler* req) {
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
  
   if(!audioBuffer.contains("program")) {
      audioLock.lock();
      blog(LOG_INFO, "setup program buffer");
      boost::circular_buffer<double>* buf = new boost::circular_buffer<double>(25);
      buf->set_capacity(25);
      audioBuffer["program"] = buf;
      audioLock.unlock();
   }
  
   blog(LOG_INFO, "before meters get");
   obs_volmeter** meters = (struct obs_volmeter**) obs_audio_mix_meters();
   blog(LOG_INFO, "get single meter");
   obs_volmeter* programVolmeter = meters[0];
   obs_data_t* programAudioData = obs_data_create();
   obs_data_set_string(programAudioData, "sourceName", "program");
   if(programVolmeter != nullptr) {
      blog(LOG_INFO, "program volmeter not null");
      obs_volmeter_add_callback(programVolmeter, HandleVolumeLevel, programAudioData);
   }
  
   blog(LOG_INFO, "after program volmeter callback");
   audioMonitorStarted = true;
      req->SendOKResponse(nullptr);
   }

void Audio::StopAudio(WSRequestHandler* req) {
   audioMonitorStarted = false;
   const char* name = obs_data_get_string(req->data, "sceneName");
   obs_source_t* s = obs_get_source_by_name(name);
   blog(LOG_INFO, "switch audio monitor source: %s", name);
   obs_scene_enum_items(obs_scene_from_source(s), TurnOffAudioMonitor, nullptr);
   obs_source_release(s);
   req->SendOKResponse(nullptr);
 }


// private

 bool Audio::TurnOnAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p) {
   if(!obs_sceneitem_visible(item)) {
      return true;
   }
  
   obs_data_t* audio_opts = (obs_data_t*) p;
   obs_source_t* source = obs_sceneitem_get_source(item);
  
   return TurnOnSourceAudioMonitor(source, audio_opts);
}

bool Audio::TurnOnSourceAudioMonitor(obs_source_t* source, obs_data_t* audio_opts) {
   const char* sourceName = obs_source_get_name(source);
  
   if(audioMonitorMap.contains(sourceName)) {
      blog(LOG_INFO, "monitor for source already exists: %s", sourceName);
   }
   
   blog(LOG_INFO, "switch audio monitor source: %s", sourceName);
   if(obs_data_get_bool(audio_opts, "output")) {
      obs_source_set_monitoring_type(source, (obs_monitoring_type)2);
   } else {
      obs_source_set_monitoring_type(source, (obs_monitoring_type)1);
   }
  
   audioLock.lock();
  
   obs_data_t* data = obs_data_create();
   obs_data_set_string(data, "sourceName", sourceName);
  
   obs_volmeter_t* volmeter = obs_volmeter_create(OBS_FADER_CUBIC);
   obs_volmeter_set_update_interval(volmeter, 10);
   obs_volmeter_attach_source(volmeter, source);
   obs_volmeter_add_callback(volmeter, HandleVolumeLevel, data);

   audioMonitorMap.insert(sourceName, volmeter);
  
   blog(LOG_INFO, "setup source buffer %s", sourceName);
   boost::circular_buffer<double>* buf = new boost::circular_buffer<double>(25);
   buf->set_capacity(25);
   audioBuffer[sourceName] = buf;
   audioLock.unlock();

   return true;
}

bool Audio::TurnOffSourceAudio(void *p, obs_source* source) {
   const char* sourceName = obs_source_get_name(source);
   obs_source_set_monitoring_type(source, (obs_monitoring_type)0);
  
   audioLock.lock();
   obs_volmeter_t* volmeter = audioMonitorMap[sourceName];
   obs_volmeter_destroy(volmeter);
   delete audioBuffer[sourceName];
   audioBuffer.remove(sourceName);
   audioMonitorMap.remove(sourceName);
   audioMonitorLevel.remove(sourceName);
   audioLock.unlock();
}

bool Audio::TurnOffAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p) {
   obs_source_t* source = obs_sceneitem_get_source(item);
   const char* sourceName = obs_source_get_name(source);
   obs_source_set_monitoring_type(source, (obs_monitoring_type)0);
  
   audioLock.lock();
   
   obs_volmeter_t* volmeter = audioMonitorMap[sourceName];
   obs_volmeter_destroy(volmeter);
   audioMonitorMap.remove(sourceName);
   
   audioMonitorLevel.remove(sourceName);
   
   audioLock.unlock();
   return true;
}

void Audio::HandleVolumeLevel(void *data, const float magnitude[MAX_AUDIO_CHANNELS],
   const float peak[MAX_AUDIO_CHANNELS],
   const float inputPeak[MAX_AUDIO_CHANNELS]) { 
   if(data == nullptr) {
      blog(LOG_INFO, "audio monitoring: got null data, sth went wrong");
   }
	
   const char* sourceName = obs_data_get_string((obs_data_t*)data, "sourceName");
	
   boost::circular_buffer<double>* buf = audioBuffer[sourceName];
   buf->push_back((double)peak[0]);
   
   double maxPeak = -60.0;
   for(int i = 0; i < buf->size(); i++) {
      maxPeak = std::max(buf->at(i), maxPeak);
   }
   
   double maxPeakNormalized = (maxPeak + 60.0) / 60.0;
   audioMonitorLevel[sourceName] = maxPeakNormalized;
}
