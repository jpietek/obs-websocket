#include <QString>
#include <QHostInfo>

#include "WSEvents.h"
#include "obs-websocket.h"
#include <QProcess>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
#include <QFile>

#include <iostream>
#include "ProcessedThumbs.h"

class ThumbCreator : public QObject {
  private:
    QString url;
    QString source_name;
    QString image_id;
    QString browserWidth;
    QString browserHeight;
    bool isMedia;
  
 public:
   ThumbCreator(QString url, QString source_name, QString image_id, QString browserWidth, 
                QString browserHeight, bool isMedia) {
     this->url = url;
     this->source_name = source_name;
     this->image_id = image_id;
     this->browserWidth = browserWidth;
     this->browserHeight = browserHeight;
     this->isMedia = isMedia;
   };
   
   void run() {
      QtConcurrent::run([=]() {
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
               blog(LOG_INFO, "ffprobe args: %s", args.join(" ").toStdString().c_str());
               ffprobe.start("ffprobe", args);
               ffprobe.waitForFinished();
            
               QString output(ffprobe.readLine());
               QStringList dimensions = output.split('x');
            
               QStringList out;
               if(dimensions.size() != 2) {
                  return out;
               }
            
               int width = dimensions[0].toInt();
               int height = dimensions[1].toInt();
               blog(LOG_INFO, "media source dimensions: %i %i", width, height);   
            
               out << dimensions[0] << dimensions[1];
               return out;
            });
         }
  
         QString fileName = this->image_id + (this->isMedia ? ".jpg" : ".png");
         if(!this->isMedia) {
            cmd = "DISPLAY=:0 node /apps/lsp/screenshot/screenshot.js " + this->url + 
               + " /var/www/html/thumbs/" + fileName + " " + this->browserWidth + " " + this->browserHeight;
         } else {
            cmd = "ffmpeg -i " + this->url + " -vframes 1 -filter scale='640:-1' /var/www/html/thumbs/" 
	       +    fileName;
      }
  
         blog(LOG_INFO, "thumb cmd: %s", cmd.toStdString().c_str());
         int ret = system(cmd.toStdString().c_str());
         if(ret > 0) {
            blog(LOG_INFO, "failed to create thumbnail for source: %s", this->url.toStdString().c_str());
            return;
         }
      
         QString localThumbPath = "/var/www/html/thumbs/" + fileName;
         QString bucketName = getenv("S3_BUCKET_NAME");
         QString s3Upload = "aws s3 cp " + localThumbPath + " s3://" + bucketName + "/vt/";
         blog(LOG_INFO, "before s3 upload: %s", s3Upload.toStdString().c_str());
         int s3Ret = system(s3Upload.toStdString().c_str());
         blog(LOG_INFO, "after s3 upload");
         if(s3Ret > 0) {
            blog(LOG_INFO, "failed to upload thumbnail to s3");
            return;
         }
      
         QFile file(localThumbPath);
         file.remove();
      
         QString cdnPrefix = getenv("CDN_PREFIX");
         blog(LOG_INFO, "cdn prefix: %s", cdnPrefix.toStdString().c_str());
         QString url = "https://" + cdnPrefix + "/vt/" + fileName;
         blog(LOG_INFO, "image url: %s", url.toStdString().c_str());      
         srcData["thumbUrl"] = url;
      
         if(this->isMedia) {
            blog(LOG_INFO, "wait for resolution future to finish");
            future.waitForFinished();
            blog(LOG_INFO, "after resolution future");
            QStringList dimensions = future.result();
            if(!dimensions.isEmpty()) {
               srcData["width"] = dimensions[0];
               srcData["height"] = dimensions[1];
            }
         }
         blog(LOG_INFO, "before insert thumb");
         ProcessedThumbs::insertThumb(this->source_name, srcData);
      });
   }
};
