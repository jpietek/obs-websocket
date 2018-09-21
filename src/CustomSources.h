#ifndef CUSTOMSOURCES_H
#define CUSTOMSOURCES_H

#include<QHash>
#include<QMutex>
#include<QMutableHashIterator>
#include <QHostInfo>
#include <QString>

#include "WSRequestHandler.h"
#include "WSEvents.h"
#include "ThumbCreator.h"
#include "Utils.h"

#include <unistd.h>
#include "Audio.h"

struct AddSourceData {
   obs_source_t* source;
   bool visible;
};

class CustomSources : public QObject {
    Q_OBJECT
    
   private:
      static QString GetRandomString(int len);
      static void AddSource(void *_data, obs_scene_t *scene);
      static bool RemoveSource(void* p, obs_source_t* src);
      static void ClearScene(const char*);
      
   public:
      static void HandleAddMediaSource(WSRequestHandler* req);
      static void HandleRemoveSource(WSRequestHandler* req);
      static void HandleAddBrowserSource(WSRequestHandler* req);
      static void HandleClearSession(WSRequestHandler* req);
      static void HandleClearScene(WSRequestHandler* req);
};

#endif
