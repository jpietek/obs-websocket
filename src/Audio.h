#ifndef AUDIO_H
#define AUDIO_H

#include <QHash>
#include <QSet>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QMutex>
#include <QThread>

#include <obs.hpp>
#include <obs-frontend-api.h>

#include "obs-websocket.h"

#include <queue>
#include <boost/circular_buffer.hpp>

#include "WSRequestHandler.h"

class Audio : public QObject {
    Q_OBJECT
    
   private:
      static QHash<QString, obs_volmeter_t*> audioMonitorMap;
      static QHash<QString, double> audioMonitorLevel;
      static QHash<QString, boost::circular_buffer<double>*> audioBuffer;
      
      static bool audioMonitorStarted;
      static QMutex audioLock;
      
      static bool TurnOnAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p);
      static bool TurnOffAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p);

      static void HandleVolumeLevel(void *data, const float magnitude[MAX_AUDIO_CHANNELS],
         const float peak[MAX_AUDIO_CHANNELS],
         const float inputPeak[MAX_AUDIO_CHANNELS]);
    
   public:
      static void SetProgramAudioVolume(WSRequestHandler* req);
      static void PlayAudio(WSRequestHandler* req);
      static void StopAudio(WSRequestHandler* req);
      static QHash<QString, double> GetAudioLevels();
      static bool areLevelsEmpty();
      static void startAudioMonitor();
      static bool isAudioMonitorStarted();
      
      static bool TurnOnSourceAudioMonitor(obs_source_t* source, obs_data_t* audio_opts);
      static bool TurnOffSourceAudio(void *p, obs_source* source);
      
      static obs_data_t* GetAudioOutputOpts(QString sceneName);
};

#endif
