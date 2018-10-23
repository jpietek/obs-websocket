#pragma once
#include <string.h>

namespace {

bool is_filename_sane(const char* fn) {
    return (strstr(fn, "/data/") == fn) && (strstr(fn, "/..") == NULL);
}

bool is_url_sane(const char* url) {
    if (strstr(url, "http://") == url) return true;
    if (strstr(url, "https://") == url) return true;
    if (strstr(url, "rtmp://") == url) return true;
    if (strstr(url, "rtmps://") == url) return true;
    return false;
}

}
