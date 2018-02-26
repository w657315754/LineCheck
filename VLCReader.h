#ifndef VLCREADER_H
#define VLCREADER_H

#include <vlc/vlc.h>
#include <opencv2/opencv.hpp>

class VLCReader
{
public:
    VLCReader(char* url=0);
    ~VLCReader();
    void start(int wantW = 640, int wantH=480);
    void pause(bool paused);
    cv::Mat frame(){ return img;}
    int w, h;

    char* rtspAddress;
    libvlc_instance_t *inst;
    libvlc_media_player_t *mp;
    unsigned char *pixel;
    cv::Mat img;

    static void *cb_lock(void *opaque, void **plane);
    static void cb_unlock(void *opaque, void *picture, void * const *plane);
    static void cb_display(void *opaque, void *picture);
    unsigned char * updataSize();
};
#endif // VLCREADER_H