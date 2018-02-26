//#include "addLine.h"
//#include "config.h"
////#include "vlcreader.h"
//#include "vclient.h"
//using namespace cv;
//using namespace std;
//string video_src = "rtsp://127.0.0.1:8554/h264";
//int rtsp_w = 1920, rtsp_h = 1080;
////VLCReader r("rtsp://127.0.0.1:8554/h264");
//std::unique_ptr<Vclient> r(new Vclient());
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
//
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
//
//void AddLine::addLine(int *pointX,int *pointY,string path){
//	
//	
//
//	namedWindow("addLine", WINDOW_NORMAL);
//	//resizeWindow("addLine",640,480);
//	int count = readPoint(pointX,pointY);
//	//auto path = "t3.mp4";
//
//
//	
//	//video >> I;
//	cout<<"save first.jpg!"<<endl;
//	imwrite("first.jpg",r->capture().clone());
//
//	while(true){
//		
//		//video >> I;
//		I = r->capture();
//	
//		if(!I.empty()){
//			//cout<<"width:"<<I.cols<<"height:"<<I.rows<<endl;
//			count = pointCount(pointX,pointY);
//		
//			//绘制点
//			for(int i=0;i<count;i++){
//				//cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
//				drawPoint(pointX[i],pointY[i],I);
//			}
//
//			cv::setMouseCallback("addLine",on_mouse,&I);
//			imshow("addLine", I);
//			int key = waitKey(50);
//			if(key == 27)break;
//			if(key >= 0){
//				while(!r->capture().empty()){
//					cout<<"save first.jpg!"<<endl;
//					imwrite("first.jpg",r->capture().clone());			
//					break;
//				}
//				
//			}
//		}
//		
//	}
//
//
//}
//
//
//int main(){
//	
//	Config config = Config("config.json");
//	AddLine addLine;
//	//读取端点和顶点
//	string video_src = config["video_src"].asString();
//	//定位线 
//	/*char* c;  
//	const int len = video_src.length();  
//	c = new char[len+1];  
//	strcpy(c,video_src.c_str());
//
//	r.rtspAddress = c;*/
//	r->mrl = video_src;
//
//
//	VideoCapture video;
//	if(video_src == "0")
//		video = cv::VideoCapture(0);
//	else
//		video = cv::VideoCapture(video_src);
//	video>>I;
//
//	
//	config["width"]=I.cols;
//	config["height"] = I.rows;
//
//	config.save();
//
//
//
//
//	//r.start(I.cols, I.rows);
//	r->width = I.cols;
//	r->height = I.rows;
//
//	r->init();
//	r->play();
//	Sleep(1000);
//	/*auto play = [&] () {
//		
//	};
//	
//	thread detect_streamer(play);
//	detect_streamer.detach();*/
//
//	addLine.addLine(pointX,pointY,video_src);
//
//	system("pause");
//	return 0;
//
//}