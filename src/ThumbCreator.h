#include <QString>
#include <QHostInfo>

#include "WSEvents.h"
#include "obs-websocket.h"
#include <QProcess>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

#include <iostream>

class ThumbCreator : public QThread {
  private:
    QString url;
    QString source_name;
    QString image_id;
    bool isMedia;
  
 public:
   ThumbCreator(QString url, QString source_name, QString image_id, bool isMedia) {
     this->url = url;
     this->source_name = source_name;
     this->image_id = image_id;
     this->isMedia = isMedia;
   };
   
   void run() {
      blog(LOG_INFO, "inside get source image: %s %s %s", this->image_id.toStdString().c_str(),
      this->url.toStdString().c_str(), this->source_name.toStdString().c_str());
      QString cmd;
      
      QHash<QString, QString> srcData;
      
      QFuture<QStringList> future;
       if(this->isMedia) {
          future = QtConcurrent::run([=]() {
            QProcess ffprobe;
            QStringList args;
            args <<  "-v" << "error" << "-select_streams" << "v:0" << "-show_entries" << "stream=width,height" << "-of" << "csv=s=x:p=0" << this->url;
            blog(LOG_INFO, "ffprobe start");
            ffprobe.start("ffprobe", args);
            ffprobe.waitForFinished();
            blog(LOG_INFO, "ffprobe finished");
            QString output(ffprobe.readAllStandardOutput());
            blog(LOG_INFO, "ffprobe got output");
            QStringList size = output.split('x', QString::SkipEmptyParts);
         
            int width = size[0].toInt();
            int height = size[1].toInt();
            blog(LOG_INFO, "media source dimensions: %i %i", width, height);   
            
            QStringList out;
            out << size[0] << size[1];
            return out;
      });
      }
  
      QString fileName = this->image_id + (this->isMedia ? ".jpg" : ".png");
      if(!this->isMedia) {
	      cmd = "DISPLAY=:0 python /apps/tools/screenshot.py " + this->url
	        + " " + fileName;
      } else {
	      cmd = "ffmpeg -i " + this->url + " -vframes 1 -filter scale='640:-1' /var/www/html/thumbs/" 
	       + fileName;
      }
  
      blog(LOG_INFO, "thumb cmd: %s", cmd.toStdString().c_str());
      int ret = system(cmd.toStdString().c_str());
      if(ret > 0) {
         blog(LOG_INFO, "failed to create thumbnail for source: %s", this->url.toStdString().c_str());
         return;
      }
      
      QString s3Upload = "aws s3 cp /var/www/html/thumbs/" + fileName + " s3://tellyo-liveproducer-dev/vt/";
      int s3Ret = system(s3Upload.toStdString().c_str());
      if(s3Ret > 0) {
         blog(LOG_INFO, "failed to upload thumbnail to s3");
         return;
      }
      
      QString url = "https://d1wvo40j13vzat.cloudfront.net/vt/" + fileName;
    
      blog(LOG_INFO, "image url: %s", url.toStdString().c_str());
      
      
      srcData["thumbUrl"] = url;
      
      if(this->isMedia) {
         future.waitForFinished();
         QStringList dimensions = future.result();
         srcData["width"] = dimensions[0];
         srcData["height"] = dimensions[1];
      }
  
      WSEvents::thumbsLock.lock();
      WSEvents::processedSourceThumbs.insert(this->source_name, srcData);
      WSEvents::thumbsLock.unlock();
   }
};
