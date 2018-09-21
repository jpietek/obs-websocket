#ifndef PROCESSEDTHUMBS_H
#define PROCESSEDTHUMBS_H

#include<QHash>
#include<QMutex>
#include<QMutableHashIterator>
#include "WSRequestHandler.h"

class ProcessedThumbs : public QObject {
    Q_OBJECT
    
   private:
      static QHash<QString, QHash<QString, QString>> processedSourceThumbs;
      static QMutex thumbsLock;
      
   public:
      static bool empty();
      static void insertThumb(QString sourceName, QHash<QString, QString> sourceData);
      static obs_data_t* pullProcessedThumbs();
};

#endif
