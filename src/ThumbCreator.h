#include <QString>
#include <QHostInfo>

#include "WSEvents.h"
#include "obs-websocket.h"

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
  
      if(!this->isMedia) {
	cmd = "DISPLAY=:0 python /apps/tools/screenshot.py " + this->url
	  + " " + this->image_id + ".png";
      } else {
	cmd = "ffmpeg -i " + this->url + " -vframes 1 -filter scale='640:-1' /var/www/html/thumbs/" 
	  + this->image_id + ".jpg";
      }
  
      blog(LOG_INFO, "thumb cmd: %s", cmd.toStdString().c_str());
      int ret = system(cmd.toStdString().c_str());
      if(ret > 0) {
	blog(LOG_INFO, "failed to create thumbnail for source: %s", this->url.toStdString().c_str());
	return;
      }
  
      QString url = "http://" + QHostInfo::localHostName() 
	+ ".aws-dev.intranet/thumbs/" 
	+ this->image_id + (this->isMedia ? ".jpg" : ".png");
    
      blog(LOG_INFO, "image url: %s", url.toStdString().c_str());
  
      WSEvents::thumbsLock.lock();
      WSEvents::processedSourceThumbs.insert(this->source_name, url);
      WSEvents::thumbsLock.unlock();
   }
};
