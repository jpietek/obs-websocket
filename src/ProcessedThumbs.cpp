#include "ProcessedThumbs.h"

QHash<QString, QHash<QString, QString>> ProcessedThumbs::processedSourceThumbs {};
QMutex ProcessedThumbs::thumbsLock {};

bool ProcessedThumbs::empty()
{
    return processedSourceThumbs.empty();
}

void ProcessedThumbs::insertThumb(QString sourceName, QHash<QString, QString> sourceData)
{
    thumbsLock.lock();
    processedSourceThumbs.insert(sourceName, sourceData);
    thumbsLock.unlock();
}

obs_data_t *ProcessedThumbs::pullProcessedThumbs()
{
    obs_data_t *sources = obs_data_create();
    thumbsLock.lock();
    QMutableHashIterator<QString, QHash<QString, QString>> i(processedSourceThumbs);

    while (i.hasNext()) {
        i.next();
        QString sourceName = i.key();
        QHash<QString, QString> srcData = i.value();

        obs_data_t *srcDataObs = obs_data_create();
        obs_data_set_string(srcDataObs, "thumbnailUrl", srcData["thumbUrl"].toStdString().c_str());
        if (srcData["thumbUrl"].endsWith(".jpg")) {
            obs_data_set_int(srcDataObs, "width", srcData["width"].toInt());
            obs_data_set_int(srcDataObs, "height", srcData["height"].toInt());
        }

        blog(LOG_INFO, "source thumb to notify: %s ", sourceName.toUtf8());
        obs_data_set_obj(sources, sourceName.toUtf8(), srcDataObs);
        blog(LOG_INFO, "before erase");
        i.remove();
    }

    thumbsLock.unlock();
    return sources;
}
