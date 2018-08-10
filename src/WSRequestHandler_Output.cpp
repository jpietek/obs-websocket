#include "Utils.h"
#include <cstdlib>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "WSRequestHandler.h"
#include <signal.h>

void WSRequestHandler::SetupStreamingOutput(WSRequestHandler* req) {
  
  blog(LOG_INFO, "inside output");
 
  obs_video_info ovi;
  blog(LOG_INFO, "get video info");
  
  int fps_num = obs_data_get_int(req->data, "fpsNum");
  int fps_den = obs_data_get_int(req->data, "fpsDen");
  int width = obs_data_get_int(req->data, "width");
  int height = obs_data_get_int(req->data, "height");
  int bitrate = obs_data_get_int(req->data, "bitrate");
  
  bool streamAlreadyStarted = obs_frontend_streaming_active();
  if(streamAlreadyStarted) {
    req->SendErrorResponse("can't modify output params, stream already started");
    return;
  }
  
  blog(LOG_INFO, "fps to be updated %i %i", fps_num, fps_den);
  
  if(fps_num <= 0 || fps_den <= 0) {
    req->SendErrorResponse("cowardly refusing to use fps num or den <= 0");
    return;
  }
  
  if(width <= 0 || height <= 0 || bitrate <= 0) {
    req->SendErrorResponse("please provide reasonable width, height (pixels) and bitrate (kbps)");
    return;
  }
  
  bool res = obs_get_video_info(&ovi);
  blog(LOG_INFO, "video info result: %d", res);
  blog(LOG_INFO, "current output height: %i", ovi.output_height);
  blog(LOG_INFO, "current output width: %i", ovi.output_width);
  
  double fpsVal = (long double)ovi.fps_num / (long double)ovi.fps_den;
  blog(LOG_INFO, "fps val: %f", fpsVal);
  
  ovi.base_width = width;
  ovi.base_height = height;
  
  ovi.output_width = width;
  ovi.output_height = height;
  
  ovi.fps_den = fps_den;
  ovi.fps_num = fps_num;
  
  blog(LOG_INFO, "output height after update: %i", ovi.output_height);
  blog(LOG_INFO, "output width after update: %i", ovi.output_width);
  obs_service_t* s = obs_frontend_get_streaming_service();
  
  char* name = obs_frontend_get_current_profile();
  blog(LOG_INFO, "current profile: %s", name); 

  if(s == nullptr) {
    blog(LOG_INFO, "got null service");
  }
  
  blog(LOG_INFO, "got service: %s", obs_service_get_name(s));
  obs_service_get_settings(s);
  
  OBSData settings = obs_data_create();
  obs_data_release(settings);
  obs_data_set_int(settings, "bitrate", bitrate);
  obs_data_set_string(settings, "preset", "veryfast");
  obs_data_set_int(settings, "buffer_size", bitrate);
  obs_data_set_string(settings, "tune", "zerolatency");
  obs_data_set_int(settings, "keyint_sec",  3);
  obs_data_set_string(settings, "rate_control", "CBR");
  
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;
  char encoderJsonPath[512];
  strcat(encoderJsonPath, homedir);
  strcat(encoderJsonPath, "/.config/obs-studio/basic/profiles/Untitled/streamEncoder.json");
  
  blog(LOG_INFO, "write encoder settings to file:  %s", encoderJsonPath);
  obs_data_save_json_safe(settings, encoderJsonPath, "tmp", "bak");
  
  obs_service_apply_encoder_settings(s, settings, nullptr);
  obs_reset_video(&ovi);
  
  req->SendOKResponse(nullptr);
}

void WSRequestHandler::AddCustomOutput(WSRequestHandler* req) {
  
  int fps_num = obs_data_get_int(req->data, "fpsNum");
  int fps_den = obs_data_get_int(req->data, "fpsDen");
  int width = obs_data_get_int(req->data, "width");
  int height = obs_data_get_int(req->data, "height");
  int bitrate = obs_data_get_int(req->data, "bitrate");
  
  OBSData vsettings = obs_data_create();
  obs_data_set_int(vsettings, "bitrate", bitrate);
  obs_data_set_string(vsettings, "preset", "veryfast");
  obs_data_set_int(vsettings, "buffer_size", bitrate);
  obs_data_set_string(vsettings, "tune", "zerolatency");
  obs_data_set_int(vsettings, "keyint_sec",  3);
  obs_data_set_string(vsettings, "rate_control", "CBR");
 
  obs_encoder* venc = obs_video_encoder_create("obs_x264", "custom x264", vsettings, nullptr);
  obs_encoder_set_scaled_size(venc, width, height);
  obs_encoder_set_video(venc, obs_get_video());
  
  obs_encoder* aenc = obs_audio_encoder_create("ffmpeg_aac", "custom aac", nullptr, 0, nullptr);
  obs_encoder_set_audio(aenc, obs_get_audio());
  
  OBSData out_settings = obs_data_create();
  obs_data_set_string(out_settings, "url", "rtmp://127.0.0.1/stream/obs2");
  obs_data_set_string(out_settings, "format_name", "flv");
  obs_data_set_string(out_settings, "format_mime_type", "video/x-flv");
  obs_data_set_int(out_settings, "gop_size", 75);
  obs_data_set_int(out_settings, "video_bitrate", bitrate);
  obs_data_set_int(out_settings, "scale_width", width);
  obs_data_set_int(out_settings, "scale_height", height);
  obs_data_set_string(out_settings, "video_encoder_id", "obs_x264");
  obs_data_set_int(out_settings, "audio_bitrate", 256);
  obs_data_set_string(out_settings, "audio_encoder_id", "ffmpeg_aac");
  
  OBSOutput out = obs_output_create("ffmpeg_output", "custom output", out_settings, nullptr);
  obs_output_set_video_encoder(out, venc);
  
  obs_output_set_audio_encoder(out, aenc, 1);
  obs_output_set_media(out, obs_get_video(), obs_get_audio());
  OBSData server_settings = obs_data_create();
  obs_data_set_string(server_settings, "server",
				"rtmp://127.0.0.1/stream");
  obs_data_set_string(server_settings, "key", "obs2");
  
  obs_service_t* service = obs_service_create("rtmp_custom", "rtmp_custom", server_settings, nullptr);
  obs_service_update(service, server_settings);
  
  obs_service_apply_encoder_settings(service, vsettings, nullptr);
  obs_output_set_service(out, service);
  
  bool init_res = obs_output_initialize_encoders(out, 0);
  blog(LOG_INFO, "codec init res: %d", init_res);
  
  blog(LOG_INFO, "before output start");
  bool res = obs_output_start(out);
  blog(LOG_INFO, "start result: %d", res);
  
  const char *error = obs_output_get_last_error(out);
  blog(LOG_INFO, "start error: %s", error);
   
  req->SendOKResponse();
}

void WSRequestHandler::StopCustomOutput(WSRequestHandler* req) {
  obs_output_t* out = obs_get_output_by_name("obs");
  obs_output_stop(out);
  req->SendOKResponse();
}

void WSRequestHandler::HandleRestartOBS(WSRequestHandler* req) {
    raise(15);
}