//#include "addLine.h"
//#include "config.h"
//using namespace cv;
//using namespace std;
//
//int pointX[100],pointY[100];  
////int count = 0;
//ofstream outfile;
//cv::Mat I;
//int pointCount(int *pointX,int *pointY){
//	int count = 0; 
//	for(int i=0;i<100;i++){
//		if((pointX[count]>0&&pointY[count]>0)&&(pointX[count]<10000&&pointY[count]<10000))
//			count++;
//	}
//	return count;
//}
////左键加点，右键重置
//void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
//    {
//        Mat hh;
//        hh = *(Mat*)userdata;
//        Point p(x, y);
//		
//
//        switch (EVENT)
//        {
//            case EVENT_LBUTTONDOWN:
//            {
//				cout << "click x:"<<p.x<<" y:"<<p.y<<endl;
//                
//                circle(hh, p,3,Scalar(255,255,255),-1);
//				outfile.open("points.txt",ios::app);
//				outfile<<p.x<<endl;
//				outfile<<p.y<<endl;
//				int count = pointCount(pointX,pointY);
//				pointX[count] = p.x;
//				pointY[count] = p.y;
//
//				outfile.close();
//				imshow("addLine", I);
//            }
//            break;
//			case EVENT_RBUTTONDOWN:
//            {
//				I = imread("test.jpg");
//				outfile.open("points.txt",ios::out);
//				
//				outfile.close();
//
//				for(int i=0;i<100;i++){
//					pointX[i] =-1;
//					pointY[i] =-1;
//				}
//				
//				imshow("addLine", I);
//            }
//            break;
//        }
//
//    }
//void AddLine::drawPoint(int x,int y,cv::Mat &I){
//
//	circle(I, Point(x,y),3,Scalar(255,255,255),-1);
//}
//int AddLine::readPoint(int *pointX,int *pointY){
//	ifstream infile;  
//    infile.open("points.txt");  
//    if(!infile.is_open())  
//    {  
//        cout<<"Could Not Open File!!!";  
//        exit(EXIT_FAILURE);  
//    }  
//    
//	int count = 0;  
//
//    while(infile.good())  
//    {  
//		if(count==100)
//			break;
//        
//        infile >> pointX[count];
//		infile >> pointY[count]; 
//		if((pointX[count]>0&&pointY[count]>0)&&(pointX[count]<10000&&pointY[count]<10000)){
//			//cout<<pointX[count]<<" "<<pointY[count]<<endl;
//			count++;  
//		}	
//		else
//			break;
//    }  
//    if(infile.eof())  
//        cout<<"End Of File!!"<<endl;  
//    cout<<"Count: "<<count<<endl;  
//
//    infile.close();  
//	return count;
//}
//
//void AddLine::addLine(int *pointX,int *pointY){
//	
//	int count = readPoint(pointX,pointY);
//
//    I = imread("test.jpg");
//	namedWindow("addLine", WINDOW_NORMAL);
//
//	//绘制点
//	for(int i=0;i<count;i++){
//		cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
//		drawPoint(pointX[i],pointY[i],I);
//	}
//
//	cv::setMouseCallback("addLine",on_mouse,&I);
//
//	imshow("addLine", I);
//
//	int key = waitKey();
//	cout<<"waitkey"<<key<<endl;
//
//}
//void AddLine::addLine(int *pointX,int *pointY,string path){
//	
//	
//
//	namedWindow("addLine", WINDOW_NORMAL);
//	//resizeWindow("addLine",640,480);
//	int count = readPoint(pointX,pointY);
//	//auto path = "t3.mp4";
//
//	VideoCapture video;
//	if(path == "0")
//		video = cv::VideoCapture(0);
//	else
//		video = cv::VideoCapture(path);
//	
//	video >> I;
//	Config config = Config("config.json");
//	
//	config["width"]=I.cols;
//	config["height"] = I.rows;
//
//	config.save();
//	while(true){
//		
//		
//		video >> I;
//		//cout<<"width:"<<I.cols<<"height:"<<I.rows<<endl;
//		count = pointCount(pointX,pointY);
//		
//		//绘制点
//		for(int i=0;i<count;i++){
//			//cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
//			drawPoint(pointX[i],pointY[i],I);
//		}
//
//		cv::setMouseCallback("addLine",on_mouse,&I);
//		imshow("addLine", I);
//		int key = waitKey(50);
//		if(key == 27)break;
//	}
//
//
//}
//
//
//int main(){
//	Config config = Config("config.json");
//	AddLine addLine;
//	//读取端点和顶点
//	string video_src = config["video_src"].asString();
//	//定位线 
//	//addLine.addLine(pointX,pointY,"night_test.mp4");
//	//addLine.addLine(pointX,pointY,"0");
//	//addLine.addLine(pointX,pointY,"rtsp://192.168.8.218:8554/h264");	
//	//addLine.addLine(pointX,pointY,"rtsp://127.0.0.1:8554/h264");
//	addLine.addLine(pointX,pointY,video_src);
//
//	system("pause");
//	return 0;
//
//}