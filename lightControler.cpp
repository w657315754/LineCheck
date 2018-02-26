//#include "vclient.h"
//#include "config.h"
//#include <thread>
//#include <queue>
//
//using namespace std;
//using namespace cv;
//
//std::unique_ptr<Vclient> r(new Vclient());
//int rtsp_w = 1920, rtsp_h = 1080;
//
//
//queue<double> lights;
//int lights_max_size = 100;
//double sum_light = 0;
//double change_mode_light = 30;
//int night_mode = 1;//
//
//double get_avg_gray(IplImage *img)  
//{  
//    IplImage *gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);  
//    cvCvtColor(img,gray,CV_RGB2GRAY);  
//    CvScalar scalar = cvAvg(gray);  
//    cvReleaseImage(&gray);  
//    return scalar.val[0];  
//}  
//int main(){
//	Config config = Config("config.json");
//	string video_src = config["video_src"].asString();
//	r->mrl = video_src;
//
//	rtsp_w = config["width"].asInt();
//	rtsp_h = config["height"].asInt();
//
//	change_mode_light = config["change_mode_light"].asDouble();
//
//	r->width = rtsp_w;
//	r->height = rtsp_h;
//
//	r->init();
//	r->play();
//	Sleep(1000);
//	//namedWindow("show", WINDOW_NORMAL);
//	
//
//	thread detect_night_streamer(system,"main_night");
//	detect_night_streamer.detach();
//
//	int index = 0;
//
//	Mat I;
//	while(true){
//		
//		
//		I = r->capture();
//		
//		
//		if(!I.empty()){
//			//resizeWindow("show",640,480);
//			//imshow("show", I);
//			IplImage* img = &IplImage(I);  
//			double light = get_avg_gray(img);
//			
//			lights.push(light);
//			sum_light += light;
//
//			if(lights.size()>lights_max_size){
//				double old_light = lights.front();
//				lights.pop();
//				
//				sum_light -= old_light;
//
//			}
//
//
//			if(index % (lights_max_size*10) ==0){
//				cout<<"get_avg_gray:"<<light<<endl;
//				double avg_light = sum_light/lights.size();
//				cout<<"avg_light:"<<avg_light<<endl;
//				if(avg_light > change_mode_light){
//					cout<<"daytime mode"<<endl;
//					if(night_mode == 1){
//						cout<<"kill daytime mode!!!"<<endl;
//						system("tskill main_night");
//						thread detect_daytime_streamer(system,"main_daytime");
//						detect_daytime_streamer.detach();
//					}
//					night_mode = 0;
//				}else{
//					cout<<"night mode"<<endl;
//					if(night_mode == 0){
//						cout<<"kill night mode!!!"<<endl;
//						system("tskill main_daytime");
//						thread detect_night_streamer(system,"main_night");
//						detect_night_streamer.detach();
//					}
//					night_mode = 1;
//				}
//				
//			}
//
//			
//			index++;
//			
//		}
//		int key = waitKey(50);
//		if(key == 27)break;
//	}
//
//	system("pause");
//
//	return 0;
//}