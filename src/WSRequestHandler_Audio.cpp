#include "WSRequestHandler.h"
#include "Audio.h"

void WSRequestHandler::SetProgramVolume(WSRequestHandler* req) {   
  return Audio::SetProgramAudioVolume(req);
}

void WSRequestHandler::PlayAudio(WSRequestHandler* req) {
   return Audio::PlayAudio(req);
}


void WSRequestHandler::StopAudio(WSRequestHandler* req) {
   return Audio::StopAudio(req);
}
