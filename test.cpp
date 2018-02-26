#include <opencv2/opencv.hpp>
#include "vlcreader.h"
using namespace cv;

int main()
{
    VLCReader r("rtsp://192.168.8.218:8554/h264");
    int rtsp_w = 640, rtsp_h = 480;
    r.start(rtsp_w, rtsp_h);

    while(1){
        Mat frame = r.frame();
        if(!frame.empty()){
            imshow("test", frame);
            int ch = waitKey(20) & 0xFF;
            if (ch == 113)
                break;
        }
    }
    return 0;
}