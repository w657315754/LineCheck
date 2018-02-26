/*
#include "iostream"

#include "opencv2/opencv.hpp"
#include "detLine.h"
#include <fstream>  

#include "sender.h"

using namespace std;
using namespace cv;

void videoTest2(string path,int lines,int *pointX,int *pointY){
	//auto path = "C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\detect_demo\\DetectDemo\\x64\\Release\\night_test.mp4";
	VideoCapture video;
	if(path == "0")
		video = cv::VideoCapture(0);
	else
		video = cv::VideoCapture(path);
	cv::Mat first;
	cv::Mat current;

	// skip frames
	
	

	//for (int i = 0; i < 1500; i++) {
	//	video.grab();
	//	continue;
	//}

	video >> first;
	
	// matlab handle init
	cout<<"开始初始化:"<<sender.getTime(true)<<endl;
	detLineInitialize();
	cout<<"动态链接库连接完毕:"<<sender.getTime(true)<<endl;

	mwArray tmp_img0, xLimit, yLimit;
	mwArray rS, rN, rX, rY;

	auto img0 = cvtCvimgToMWArray(first);
	auto draw = mwArray(1, 1, mxINT32_CLASS);
	auto mth = mwArray(1, 1, mxSINGLE_CLASS);
	auto pos = mwArray(lines*3, 2, mxINT32_CLASS);
	auto flag_med = mwArray(1, 1, mxINT32_CLASS);
	draw(1, 1) = draw_value;
	mth(1, 1) = mth_value;
	flag_med(1, 1) = flag_med_value;

	for(int i=0;i<lines*3;i++){
		pos(i + 1, 1) = pointX[i];
		pos(i + 1, 2) = pointY[i];
	}
	cout<<"线位置:"<<endl
		<<pos<<endl;
	cout<<"线数量："<<lines<<endl;
	
	auto NumLine = mwArray(1, 1, mxINT32_CLASS);
	auto d1 = mwArray(1, 1, mxDOUBLE_CLASS);
	auto d2 = mwArray(1, 1, mxDOUBLE_CLASS);
	auto dx = mwArray(1, 1, mxDOUBLE_CLASS);
	auto dy = mwArray(1, 1, mxDOUBLE_CLASS);
	auto d = mwArray(1, 1, mxDOUBLE_CLASS);
	NumLine(1, 1) = lines;
	d1(1, 1) = d1_value;
	d2(1, 1) = d2_value;
	
	dx(1, 1) = dx_value;
	dy(1, 1) = dy_value;
	d(1, 1) = d_value;

	cout<<"参数初始化完毕:"<<sender.getTime(true)<<endl;

	//int lines = 3;
	int count = 0;
	while (true) {
		video >> current;

		
		if (count++ % 10 != 0) continue;

		if (current.empty()) {
			break;
		}

		auto img = cvtCvimgToMWArray(current);

		//[tmp_img0, xLimit, yLimit] =GetBorder(PosLine,NumLine,img,d1,d2);
		cout<<"调用border:"<<sender.getTime(true)<<endl;
		GetBorder(3,tmp_img0, xLimit, yLimit,pos,NumLine,img,d1,d2);
		cout<<"调用detLine:"<<sender.getTime(true)<<endl;
		//detLine(img, NumLine, PosLine, number, mAveX, mAveY, Draw, tmp_img0, xLimit, mTh, img0,dx,dy,d);
		detLine(4, rS, rN, rX, rY, img,NumLine,pos, draw,tmp_img0, xLimit, mth, img0,dx,dy,d,flag_med);
		cout<<"调用完成:"<<sender.getTime(true)<<endl;
		for (int i = 0; i < lines; i++) {
			//cout << "vs LINE" << i << " " << rS(i + 1) << endl;
			if(rS(i + 1)!="Normal!"){
				cout<<"send exception!"<<endl;
				Mat sendMat = mat_h_merge(first,current);
				imwrite("sendMat.jpg",sendMat);
				//sender.sendfile("sendMat.jpg");
				break;
			}
		}
	}
}

mwArray cvtCvimgToArray(cv::Mat src)
{
	auto dst = mwArray(src.rows, src.cols, mxUINT8_CLASS);

	cv::cvtColor(src, src, cv::COLOR_BGR2GRAY); 

	for (int x = 0; x < src.cols; x ++) {
		for (int y = 0; y < src.rows; y++) {
			dst(y + 1, x + 1) = src.at<unsigned char>(y, x);
		}
	}

	return dst;
}

    
void videoTest(string path,int lines,int *pointX,int *pointY){
	//auto path = "C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\detect_demo\\DetectDemo\\x64\\Release\\night_test.mp4";
	auto video = cv::VideoCapture(path);
	
	cv::Mat first;
	cv::Mat current;

	// skip frames

	//for (int i = 0; i < 1500; i++) {
	//	video.grab();
	//	continue;
	//}
	video >> first;

	// matlab handle init
	detLineInitialize();

	mwArray rS, rN, rX, rY;

	auto img0 = cvtCvimgToArray(first);
	auto draw = mwArray(1, 1, mxINT32_CLASS);
	auto mth = mwArray(1, 1, mxSINGLE_CLASS);
	auto pos = mwArray(lines*3, 2, mxINT32_CLASS);

	draw(1, 1) = 1;
	mth(1, 1) = 1;


	//int list[] = {
	//	545,	574,
	//	971,	644,
	//	1429,	498,
	//	543,	712,
	//	979,	780,
	//	1447,	614,
	//	531,	862,
	//	987,	846,
	//	1483,	778
	//};
	//for (int i = 0; i < 18; i += 2) {
	//	int y = i / 2;
	//	pos(y + 1, 1) = list[i];
	//	pos(y + 1, 2) = list[i + 1];
	//}
	

	for(int i=0;i<lines*3;i++){
		pos(i + 1, 1) = pointX[i];
		pos(i + 1, 2) = pointY[i];
	}
	cout<<"pos:"<<pos<<endl;
	cout<<lines<<endl;
	
	//int lines = 3;
	int count = 0;
	while (true) {
		video >> current;

		if (count++ % 10 != 0) continue;

		if (current.empty()) {
			break;
		}

		auto img = cvtCvimgToArray(current);
		detLine(4, rS, rN, rX, rY, img, pos, draw, mth, img0);

		for (int i = 0; i < lines; i++) {
			cout << "LINE" << i << " " << rS(i + 1) << endl;
		}
	}
}


string window_name1 = "show1";
Mat I;
ofstream outfile;

//左键加点，右键重置
void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
    {
        Mat hh;
        hh = *(Mat*)userdata;
        Point p(x, y);
		

        switch (EVENT)
        {
            case EVENT_LBUTTONDOWN:
            {
				cout << "click x:"<<p.x<<" y:"<<p.y<<endl;
                
                circle(hh, p,3,Scalar(255,255,255),-1);
				outfile.open("test.txt",ios::app);
				outfile<<p.x<<endl;
				outfile<<p.y<<endl;

				outfile.close();
				imshow(window_name1, I);
            }
            break;
			case EVENT_RBUTTONDOWN:
            {
				I = imread("test.jpg");
				outfile.open("test.txt",ios::out);
				
				outfile.close();
				imshow(window_name1, I);
            }
            break;
        }

    }

void drawPoint(int x,int y){

	circle(I, Point(x,y),3,Scalar(255,255,255),-1);
}

//void main()
	void m()
{  
	
	//Mat pointX = (Mat_<int>(3,1)<<267,532,751); 

	//Mat pointY = (Mat_<int>(3,1)<<270,308,225);
	
	ifstream infile;  
    infile.open("test.txt");  
    if(!infile.is_open())  
    {  
        cout<<"Could Not Open File!!!";  
        exit(EXIT_FAILURE);  
    }  
    
	//读取端点和顶点
	int pointX[100],pointY[100];  
    int count = 0;  

    while(infile.good())  
    {  
		if(count==100)
			break;
        
        infile >> pointX[count];
		infile >> pointY[count]; 
		if(pointX[count]>0&&pointY[count]>0)
			count++;  
		else
			break;
    }  
    if(infile.eof())  
        cout<<"End Of File!!"<<endl;  
    cout<<"Count: "<<count<<endl;  
    
	

    infile.close();  
	



    I = imread("test.jpg");
	namedWindow(window_name1, 0);

	//绘制点
	for(int i=0;i<count;i++){
		cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
		drawPoint(pointX[i],pointY[i]);
	}

	setMouseCallback(window_name1,on_mouse,&I);
	//Point p(300, 300);
	//circle(I, p,100,Scalar(0,0,255),-1);
	imshow(window_name1, I);
	//imshow("tmp", tmp);

	waitKey();
	
}  
int readPoint(int *pointX,int *pointY){
	ifstream infile;  
    infile.open("test.txt");  
    if(!infile.is_open())  
    {  
        cout<<"Could Not Open File!!!";  
        exit(EXIT_FAILURE);  
    }  
    
	int count = 0;  

    while(infile.good())  
    {  
		if(count==100)
			break;
        
        infile >> pointX[count];
		infile >> pointY[count]; 
		if((pointX[count]>0&&pointY[count]>0)&&(pointX[count]<10000&&pointY[count]<10000)){
			cout<<pointX[count]<<" "<<pointY[count]<<endl;
			count++;  
		}	
		else
			break;
    }  
    if(infile.eof())  
        cout<<"End Of File!!"<<endl;  
    cout<<"Count: "<<count<<endl;  
    
	

    infile.close();  
	return count;
}
void addLine(int *pointX,int *pointY){
	ifstream infile;  
    infile.open("test.txt");  
    if(!infile.is_open())  
    {  
        cout<<"Could Not Open File!!!";  
        exit(EXIT_FAILURE);  
    }  
    
	int count = 0;  

    while(infile.good())  
    {  
		if(count==100)
			break;
        
        infile >> pointX[count];
		infile >> pointY[count]; 
		
		if((pointX[count]>0&&pointY[count]>0)&&(pointX[count]<10000&&pointY[count]<10000)){
			cout<<pointX[count]<<" "<<pointY[count]<<endl;
			count++;  
		}	
		else
			break;
    }  
    if(infile.eof())  
        cout<<"End Of File!!"<<endl;  
    cout<<"Count: "<<count<<endl;  
    
	

    infile.close();  
	



    I = imread("test.jpg");
	namedWindow(window_name1, 0);

	//绘制点
	for(int i=0;i<count;i++){
		cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
		drawPoint(pointX[i],pointY[i]);
	}

	setMouseCallback(window_name1,on_mouse,&I);
	//Point p(300, 300);
	//circle(I, p,100,Scalar(0,0,255),-1);
	imshow(window_name1, I);
	//imshow("tmp", tmp);
	int key = waitKey();
	cout<<"waitkey"<<key<<endl;
	auto path = "t3.mp4";
	auto video = cv::VideoCapture(path);
	while(key == 32){
		

		video >> I;
		cv::imwrite("test.jpg",I);
		for (int i = 0; i < 100; i++) {
			video.grab();
			continue;
		}
		//绘制点
		for(int i=0;i<count;i++){
			cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
			drawPoint(pointX[i],pointY[i]);
		}
		imshow(window_name1, I);
		key = waitKey();
	}


}

int d0_main()
{
	//auto path = "C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\detect_demo\\DetectDemo\\x64\\Release\\t1.mp4";
	
	auto path = "t3.mp4";
	//auto path = "rtsp://192.168.8.218:8554/h264";
	
	auto video = cv::VideoCapture(path);
	
	cv::Mat tmp;
	video >> tmp;
	cv::imwrite("test.jpg",tmp);
	

	//读取端点和顶点
	int pointX[100],pointY[100];  

	addLine(pointX,pointY);
	
	//int lines = readPoint(pointX,pointY)/3;
	//videoTest(path,lines,pointX,pointY);
	//Sender sender;
	//sender.sendfile("test.jpg");

	system("pause");
	return 0;
}
*/