#include "vclient.h"

//
#include "config.h"
#include "opencv2/opencv.hpp"


std::mutex Vclient::frame_mutex;

Vclient::Vclient(){
	mrl = "0";
	width = 640;
	height = 480;
	playing = false;
	for(int i=0;i<_BUFFER_SIZE;i++)
		buffer[i]=0;
}

Vclient::Vclient(const string& mrl, int width, int height, int argc, char* argv[]) :
    mrl(mrl),
    width(width),
    height(height),
    argc(argc),
    argv(argv),
    playing(false)
//    ,buffer{0}
{
	//
	for(int i=0;i<_BUFFER_SIZE;i++)
		buffer[i]=0;
	

	this->init();
}

Vclient::~Vclient()
{
    this->release();
}

cv::Mat Vclient::frame(){
	return this->cvMat;
}

void* Vclient::lock(void* opaque, void** planes)
{
    frame_mutex.lock();

    if (opaque != nullptr) {
        *planes = (unsigned char*) opaque;
    }

    return 0;
}

void Vclient::unlock(void* opaque, void* picture, void* const* planes)
{
    frame_mutex.unlock();
}

void Vclient::display(void* opaque, void* picture)
{
    /* do nothing */
}

void Vclient::init()
{
    /* load the VLC engine */
    this->instance = libvlc_new(this->argc, this->argv);

    /* create a new item */
    this->media = libvlc_media_new_location(this->instance, this->mrl.c_str());
    //this->media = libvlc_media_new_path(this->instance, this->mrl.c_str());

    /* create a media player playing environement */
    this->player = libvlc_media_player_new_from_media(this->media);

    libvlc_video_set_callbacks(this->player, this->lock, this->unlock, this->display, this->buffer);
    libvlc_video_set_format(this->player, "RGBA", this->width, this->height, this->width * _RAW_CHANNELS);

    /* no need to keep the media now */
    libvlc_media_release(this->media);
}

void Vclient::play()
{
    if (this->playing) return;

    /* play the media_player */
    libvlc_media_player_play(this->player);

    //sleep(1);
	Sleep(1000);

    this->playing = true;
}

void Vclient::stop()
{
    if (! this->playing) return;

    /* stop playing */
    libvlc_media_player_stop(this->player);

    this->playing = false;
}

void Vclient::release()
{
    /* free the player */
    libvlc_media_player_release(this->player);

    /* free the vlc */
    libvlc_release(this->instance);
}

cv::Mat Vclient::capture()
{
	//cout<<"lock!"<<endl;
    frame_mutex.lock();

    /* copy image from buffer */
    size_t size = this->width * this->height * _RAW_CHANNELS;
    //unsigned char raw[size] = {0};
    //unsigned char raw[_BUFFER_SIZE] = {0};
	for(int i=0;i<_BUFFER_SIZE;i++)
		raw[i]=0;

	memmove(raw, this->buffer, size);
	//memcpy(raw, this->buffer, size);

    frame_mutex.unlock();
	//cout<<"unlock!"<<endl;
//    /* init img */
////    auto vimg       = Vimage{};
	//auto vimg       = Vimage();

 //   vimg.cols       = this->width;
 //   vimg.rows       = this->height;
 //   vimg.channels   = _IMG_CHANNELS;
	cv::Mat dst = cv::Mat::zeros(this->width, this->height, CV_8UC3);
	cvMat = dst;
	//cout<<"convert!"<<endl;
    /* convert raw data to rgb */
    for (int y = 0; y < this->height; y++) {
        //auto row = vector<Vpixel>{};
		//auto row = vector<Vpixel>();
		vector<Vpixel> row = vector<Vpixel>(this->width);

        for (int x = 0; x < this->width; x++) {
            //auto point = &raw[y * this->width * _RAW_CHANNELS + x * _RAW_CHANNELS];
			unsigned char * point = &raw[y * this->width * _RAW_CHANNELS + x * _RAW_CHANNELS];
   //         //auto alpha = (float) point[3] / 255.0; 
			float alpha = (float) point[3] / 255.0; 
			dst.at<cv::Vec3b>(x, y)[0] = (int)((float) _BG_COLOR * (1 - alpha) + (float) point[2] * alpha);
            dst.at<cv::Vec3b>(x, y)[1] = (int)((float) _BG_COLOR * (1 - alpha) + (float) point[1] * alpha);
            dst.at<cv::Vec3b>(x, y)[2] = (int)((float) _BG_COLOR * (1 - alpha) + (float) point[0] * alpha);
			//cout<<(int)((float) point[0] * alpha)<<endl;
			/*dst.at<cv::Vec3b>(y, x)[0] = 1;
            dst.at<cv::Vec3b>(y, x)[1] = 255;
            dst.at<cv::Vec3b>(y, x)[2] = 3;*/

   //         /*row.push_back(Vpixel{
   //             (float) _BG_COLOR * (1 - alpha) + (float) point[0] * alpha,
   //             (float) _BG_COLOR * (1 - alpha) + (float) point[1] * alpha,
   //             (float) _BG_COLOR * (1 - alpha) + (float) point[2] * alpha
   //         });*/
			/*Vpixel pix = {
				(float) _BG_COLOR * (1 - alpha) + (float) point[0] * alpha,
                (float) _BG_COLOR * (1 - alpha) + (float) point[1] * alpha,
                (float) _BG_COLOR * (1 - alpha) + (float) point[2] * alpha
			};*/
			
			//cout<<"RGB:"<<(int)pix.r<<" "<<(int)pix.g<<" "<<(int)pix.b<<endl;
			//row.push_back(pix);
			//row[x] = pix;
        }

        //vimg.data.push_back(row);
    }

	
	transpose(cvMat, cvMat);

    return cvMat;

}

//
cv::Mat CvtVimageMat(const Vimage& src)
{
    cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);

    for (int y = 0; y < src.cols; y++) {
        for (int x = 0; x < src.rows; x++) {
            dst.at<cv::Vec3b>(x, y)[0] = src.data[x][y].b;
            dst.at<cv::Vec3b>(x, y)[1] = src.data[x][y].g;
            dst.at<cv::Vec3b>(x, y)[2] = src.data[x][y].r;
        }
    }

    return dst;
}
int vclient_main(){
	Config config = Config("config.json");
	//读取端点和顶点
	string video_src = config["video_src"].asString();
	//定位线 
	char* c;  
	const int len = video_src.length();  
	c = new char[len+1];  
	strcpy(c,video_src.c_str());


	//r.rtspAddress = c;


	cv::VideoCapture video;
	if(video_src == "0")
		video = cv::VideoCapture(0);
	else
		video = cv::VideoCapture(video_src);
	cv::Mat I;
	video>>I;

	
	config["width"]=I.cols;
	config["height"] = I.rows;

	config.save();

	//
	/*std::unique_ptr<Vclient> vclient(new Vclient(
        video_src,
        config["width"].asInt(),
        config["height"].asInt()));*/
	std::unique_ptr<Vclient> vclient(new Vclient(
        video_src,
        config["width"].asInt(),
        config["height"].asInt()));
	cout<<"init!"<<endl;
	vclient->play();
	cout<<"play!"<<endl;
	Sleep(1000);
	

	
	auto show = [&] () {
		cout<<"capture!"<<endl;
		cv::Mat cvimg  = vclient->capture();
		cv::imwrite("catch.jpg",cvimg);

		while(!cvimg.empty()){
			cv::imshow("show",cvimg);
			cvimg  = vclient->capture();
			cv::waitKey(100);
		}
		
	
	};
	
	thread detect_streamer(show);
	detect_streamer.detach();
	

	system("pause");
	return 0;
}