/*
obs-websocket
Copyright (C) 2016-2017	Stéphane Lepin <stephane.lepin@gmail.com>
Copyright (C) 2017	Mikhail Swift <https://github.com/mikhailswift>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#ifndef WSREQUESTHANDLER_H
#define WSREQUESTHANDLER_H

#include <QHash>
#include <QSet>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QMutex>

#include <obs.hpp>
#include <obs-frontend-api.h>

#include "obs-websocket.h"

struct SourceThumbData {
   const char* url;
   char* source_name;
   char* image_id;
   bool isMedia;
};

class WSRequestHandler : public QObject {
  Q_OBJECT

  public:
    explicit WSRequestHandler(QWebSocket* client);
    ~WSRequestHandler();
    void processIncomingMessage(QString textMessage);
    bool hasField(QString name);
    

  private:
    QWebSocket* _client;
    const char* _messageId;
    const char* _requestType;
    OBSDataAutoRelease data;

    void SendOKResponse(obs_data_t* additionalFields = NULL);
    void SendErrorResponse(const char* errorMessage);
    void SendErrorResponse(obs_data_t* additionalFields = NULL);
    void SendResponse(obs_data_t* response);

    static QHash<QString, void(*)(WSRequestHandler*)> messageMap;
    static QSet<QString> authNotRequired;
    
    static QHash<QString, obs_volmeter_t*> audioMonitorMap;
    static QMutex audioLock;
    
    static void HandleGetVersion(WSRequestHandler* req);
    static void HandleGetAuthRequired(WSRequestHandler* req);
    static void HandleAuthenticate(WSRequestHandler* req);

    static void HandleSetHeartbeat(WSRequestHandler* req);

    static void HandleSetFilenameFormatting(WSRequestHandler* req);
    static void HandleGetFilenameFormatting(WSRequestHandler* req);

    static void HandleSetCurrentScene(WSRequestHandler* req);
    static void HandleGetCurrentScene(WSRequestHandler* req);
    static void HandleGetSceneList(WSRequestHandler* req);

    static void HandleSetSceneItemOrder(WSRequestHandler* req);
    static void HandleSetSceneItemRender(WSRequestHandler* req);
    static void HandleSetSceneItemPosition(WSRequestHandler* req);
    static void HandleSetSceneItemTransform(WSRequestHandler* req);
    static void HandleSetSceneItemCrop(WSRequestHandler* req);
    static void HandleGetSceneItemProperties(WSRequestHandler* req);
    static void HandleSetSceneItemProperties(WSRequestHandler* req);
    static void HandleDuplicateSceneItem(WSRequestHandler* req);
    static void HandleDeleteSceneItem(WSRequestHandler* req);
    static void HandleResetSceneItem(WSRequestHandler* req);

    static void HandleGetStreamingStatus(WSRequestHandler* req);
    static void HandleStartStopStreaming(WSRequestHandler* req);
    static void HandleStartStopRecording(WSRequestHandler* req);
    static void HandleStartStreaming(WSRequestHandler* req);
    static void HandleStopStreaming(WSRequestHandler* req);
    static void HandleStartRecording(WSRequestHandler* req);
    static void HandleStopRecording(WSRequestHandler* req);

    static void HandleStartStopReplayBuffer(WSRequestHandler* req);
    static void HandleStartReplayBuffer(WSRequestHandler* req);
    static void HandleStopReplayBuffer(WSRequestHandler* req);
    static void HandleSaveReplayBuffer(WSRequestHandler* req);

    static void HandleSetRecordingFolder(WSRequestHandler* req);
    static void HandleGetRecordingFolder(WSRequestHandler* req);

    static void HandleGetTransitionList(WSRequestHandler* req);
    static void HandleGetCurrentTransition(WSRequestHandler* req);
    static void HandleSetCurrentTransition(WSRequestHandler* req);

    static void HandleSetVolume(WSRequestHandler* req);
    static void HandleGetVolume(WSRequestHandler* req);
    static void HandleToggleMute(WSRequestHandler* req);
    static void HandleSetMute(WSRequestHandler* req);
    static void HandleGetMute(WSRequestHandler* req);
    static void HandleSetSyncOffset(WSRequestHandler* req);
    static void HandleGetSyncOffset(WSRequestHandler* req);
    static void HandleGetSpecialSources(WSRequestHandler* req);
    static void HandleGetSourcesList(WSRequestHandler* req);
    static void HandleGetSourceTypesList(WSRequestHandler* req);
    static void HandleGetSourceSettings(WSRequestHandler* req);
    static void HandleSetSourceSettings(WSRequestHandler* req);

    static void HandleSetCurrentSceneCollection(WSRequestHandler* req);
    static void HandleGetCurrentSceneCollection(WSRequestHandler* req);
    static void HandleListSceneCollections(WSRequestHandler* req);

    static void HandleSetCurrentProfile(WSRequestHandler* req);
    static void HandleGetCurrentProfile(WSRequestHandler* req);
    static void HandleListProfiles(WSRequestHandler* req);

    static void HandleSetStreamSettings(WSRequestHandler* req);
    static void HandleGetStreamSettings(WSRequestHandler* req);
    static void HandleSaveStreamSettings(WSRequestHandler* req);

    static void HandleSetTransitionDuration(WSRequestHandler* req);
    static void HandleGetTransitionDuration(WSRequestHandler* req);

    static void HandleGetStudioModeStatus(WSRequestHandler* req);
    static void HandleGetPreviewScene(WSRequestHandler* req);
    static void HandleSetPreviewScene(WSRequestHandler* req);
    static void HandleTransitionToProgram(WSRequestHandler* req);
    static void HandleEnableStudioMode(WSRequestHandler* req);
    static void HandleDisableStudioMode(WSRequestHandler* req);
    static void HandleToggleStudioMode(WSRequestHandler* req);

    static void HandleSetTextGDIPlusProperties(WSRequestHandler* req);
    static void HandleGetTextGDIPlusProperties(WSRequestHandler* req);
    static void HandleSetTextFreetype2Properties(WSRequestHandler* req);
    static void HandleGetTextFreetype2Properties(WSRequestHandler* req);
    static void HandleSetBrowserSourceProperties(WSRequestHandler* req);
    static void HandleGetBrowserSourceProperties(WSRequestHandler* req);
    
    // sources
    static void HandleAddMediaSource(WSRequestHandler* req);
    static void HandleAddBrowserSource(WSRequestHandler* req);
    static void HandleRemoveSource(WSRequestHandler* req);
    static void HandleClearSession(WSRequestHandler* req);
    static void HandleClearScene(WSRequestHandler* req);
    static void ClearScene(const char*);
    static bool RemoveSource(void* p, obs_scene_item* item);
    static void AddSource(void *_data, obs_scene_t *scene);
    static void HandleGetSourceImage(SourceThumbData* data);
    
    // outputs
    static void SetupStreamingOutput(WSRequestHandler* req);
    static void AddCustomOutput(WSRequestHandler* req);
    static void StopCustomOutput(WSRequestHandler* req);
    static void HandleRestartOBS(WSRequestHandler* req);
    
    // audio
    static void PlayAudio(WSRequestHandler* req);
    static void StopAudio(WSRequestHandler* req);
    
    static bool TurnOffAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p);
    static bool TurnOnAudioMonitor(obs_scene_t *scene, obs_sceneitem_t *item, void *p);
    static bool TurnOffSourceAudio(void *p, obs_source *source);
    static void HandleVolumeLevel(void *data, 
	const float magnitude[MAX_AUDIO_CHANNELS], 
	const float peak[MAX_AUDIO_CHANNELS],
	const float inputPeak[MAX_AUDIO_CHANNELS]);
};

#endif // WSPROTOCOL_H
