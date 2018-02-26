#include "vlc/vlc.h"
//#include "unistd.h"
#include "stdio.h"
//#include "memory.h"
#include "vector"
#include "mutex"
#include "string"
#include "iostream"
//
#include "windows.h"
#include <memory>
#include <thread>
#include "opencv2/opencv.hpp"

using namespace std;

static const int    _RAW_CHANNELS   = 4;
static const int    _IMG_CHANNELS   = 3;
static const int    _BUFFER_SIZE    = 3840 * 2160 * 4;
static const float  _BG_COLOR       = 255.0;

typedef struct Vpixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Vpixel;

typedef struct Vimage {
    int cols;
    int rows;
    int channels;
    vector<vector<Vpixel>> data;
} Vimage;

class Vclient {
    public:
        static mutex frame_mutex;
		
		cv::Mat cvMat;
		unsigned char raw[_BUFFER_SIZE];
		cv::Mat frame();

        string mrl;
        int width;
        int height;
        int argc;
        char** argv;
        bool playing;
		unsigned char buffer[_BUFFER_SIZE];

        libvlc_instance_t* instance;
        libvlc_media_player_t* player;
        libvlc_media_t* media;

		Vclient();
        Vclient(const string& mrl, int width, int height, int argc = 0, char* argv[] = nullptr);
        ~Vclient();

        static void* lock(void* opaque, void** planes);
        static void  unlock(void* opaque, void* picture, void* const* planes);
        static void  display(void* opaque, void* picture);

        void init();
        void play();
        void stop();
        void release();

        cv::Mat capture();
};
