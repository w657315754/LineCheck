//#include "iostream"
//#include "opencv2/opencv.hpp"
//
//using namespace std;
//using namespace cv;
//
//
//void showVideo(string path){
//	Mat I;
//	namedWindow("show", WINDOW_NORMAL);
//	resizeWindow("show",640,480);
//	
//	//auto path = "t3.mp4";
//	VideoCapture video;
//	if(path == "0")
//		video = cv::VideoCapture(0);
//	else
//		video = cv::VideoCapture(path);
//	int count = 0;
//	while(true){
//		
//		
//		video >> I;
//		if(count%100 == 0){
//			imwrite("current.jpg",I);
//			cout<<"update current Mat!"<<endl;
//			//count = 0;
//			if(count%1000==0)
//			{
//				cout<<"update first Mat!"<<endl;
//				imwrite("first.jpg",I);
//			}
//		}
//
//
//		imshow("show", I);
//		int key = waitKey(10);
//		if(key == 27)break;
//		count++;
//	}
//}
//
//int main(){
//	auto path = "t3.mp4";
//	showVideo(path);
//	system("pause");
//	return 0;
//
//}