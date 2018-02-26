//#include "iostream"
//#include "opencv2/opencv.hpp"
//#include "detLine.h"
//#include <fstream>  
//#include "sender.h"
//#include <thread>
////#include "vlcreader.h"
//#include "vclient.h"
//#include "config.h"
//
//using namespace std;
//using namespace cv;
//string video_src = "rtsp://127.0.0.1:8554/h264";
//
////VLCReader r("rtsp://127.0.0.1:8554/h264");
//std::unique_ptr<Vclient> r(new Vclient());
////VLCReader r("rtsp://192.168.8.218:8554/h264");
//    int rtsp_w = 1920, rtsp_h = 1080;
//	//int rtsp_w = 1280, rtsp_h = 534;
//Sender sender;
//
//int draw_value = 1;
//	//是否显示画面
//
//int mth_value = 1;
////用于求取平均位置的连续帧数
//
//
//int d1_value = 30,d2_value = 20;
////监测区域限定 拟合线到下方白色虚线的距离，拟合线到上方白色虚线的距离
//
//int dx_value = 50,dy_value = 50,d_value = 20;
////dx,dy: 划定检测所有电力线的区域     d: 每条电线的检测区域
//
//int flag_med_value = 1;
////是否中值判定 （一般白天为0）
//
//double alpha_value = 0.2;
//
//queue<int> status;
//int max_status_size = 100;
//int sum_exception = 0;
//double sender_rate = 0.9;//当异常几率大于等于sender_rate发送异常图片
//int detect_size = 20;
//
//string cameraInfo = "default";
//
//int send_to_server = 0;
//
//void drawPoint(int x,int y,cv::Mat &I){
//
//	circle(I, Point(x,y),3,Scalar(255,255,255),-1);
//}
//int pointCount(int *pointX,int *pointY){
//	int count = 0; 
//	for(int i=0;i<100;i++){
//		if((pointX[count]>0&&pointY[count]>0)&&(pointX[count]<10000&&pointY[count]<10000))
//			count++;
//	}
//	return count;
//}
//
//mwArray cvtCvimgToMWArray(cv::Mat src)
//{
//	
//	Mat gray;
//	
//	cv::cvtColor(src.clone(), gray, cv::COLOR_BGR2GRAY); 
//	//行列转置
//	transpose(gray, gray);
//	
//	auto dst = mwArray(src.rows, src.cols, mxUINT8_CLASS);
//
//	UINT8 * data = (UINT8*)gray.data;
//
//
//	dst.SetData(data,src.rows*src.cols);
//
//	return dst;
//}
//Mat mat_h_merge(const Mat& img_left, const Mat& img_right)
//{
//    auto size   = Size(img_left.cols + img_right.cols, MAX(img_left.rows, img_right.rows));
//    auto merge  = Mat(size, CV_MAKETYPE(img_left.depth(), 3));
//
//    auto left = merge(Rect(0, 0, img_left.cols, img_left.rows));
//    img_left.copyTo(left);
//
//    auto right = merge(cvRect(img_left.cols, 0, img_right.cols, img_right.rows));
//    img_right.copyTo(right);
//
//    return merge;
//}   
//
//
//int readPoint(int *pointX,int *pointY){
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
//			cout<<pointX[count]<<" "<<pointY[count]<<endl;
//			count++;  
//		}	
//		else
//			break;
//    }  
//    if(infile.eof())  
//        cout<<"End Of File!!"<<endl;  
//    cout<<"Count: "<<count<<endl;  
//    
//	
//
//    infile.close();  
//	return count;
//}
//
//
//void videoTest(string path,int lines,int *pointX,int *pointY){
//	//auto path = "C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\detect_demo\\DetectDemo\\x64\\Release\\night_test.mp4";
//	/*VideoCapture video;
//	if(path == "0")
//		video = cv::VideoCapture(0);
//	else
//		video = cv::VideoCapture(path);*/
//	cv::Mat first;
//	cv::Mat current;
//
//	
//
//	//video >> first;
//	first = imread("first.jpg");
//	/*first = r->capture();
//	while(first.empty())
//		first = r->capture().clone();
//	*/
//	// matlab handle init
//	cout<<"开始初始化:"<<sender.getTime(true)<<endl;
//	detLineInitialize();
//	cout<<"动态链接库连接完毕:"<<sender.getTime(true)<<endl;
//
//	mwArray tmp_img0, xLimit, yLimit;
//	mwArray rS, rN, rX, rY;
//
//	auto img0 = cvtCvimgToMWArray(first);
//	auto draw = mwArray(1, 1, mxINT32_CLASS);
//	auto mth = mwArray(1, 1, mxSINGLE_CLASS);
//	auto pos = mwArray(lines*3, 2, mxINT32_CLASS);
//	auto flag_med = mwArray(1, 1, mxINT32_CLASS);
//	draw(1, 1) = draw_value;
//	mth(1, 1) = mth_value;
//	flag_med(1, 1) = flag_med_value;
//
//	for(int i=0;i<lines*3;i++){
//		pos(i + 1, 1) = pointX[i];
//		pos(i + 1, 2) = pointY[i];
//	}
//	cout<<"线位置:"<<endl
//		<<pos<<endl;
//	cout<<"线数量："<<lines<<endl;
//	
//	auto NumLine = mwArray(1, 1, mxINT32_CLASS);
//	auto d1 = mwArray(1, 1, mxDOUBLE_CLASS);
//	auto d2 = mwArray(1, 1, mxDOUBLE_CLASS);
//	auto dx = mwArray(1, 1, mxDOUBLE_CLASS);
//	auto dy = mwArray(1, 1, mxDOUBLE_CLASS);
//	auto d = mwArray(1, 1, mxDOUBLE_CLASS);
//	auto alpha = mwArray(1, 1, mxDOUBLE_CLASS);
//	NumLine(1, 1) = lines;
//	d1(1, 1) = d1_value;
//	d2(1, 1) = d2_value;
//	
//	dx(1, 1) = dx_value;
//	dy(1, 1) = dy_value;
//	d(1, 1) = d_value;
//	alpha(1,1)=alpha_value;
//
//	cout<<"参数初始化完毕:"<<sender.getTime(true)<<endl;
//	cout<<"flag_med:"<<flag_med_value<<endl;
//
//	//[tmp_img0, xLimit, yLimit] =GetBorder(PosLine,NumLine,img,d1,d2);
//	cout<<"调用border:"<<sender.getTime(true)<<endl;
//	GetBorder(3,tmp_img0, xLimit, yLimit,pos,NumLine,img0,d1,d2);
//	//int lines = 3;
//	int count = 0;
//	while (true) {
//		//video >> current;
//
//		current = r->capture().clone();
//		while(current.empty())
//			current = r->capture().clone();
//		//if (count++ % 10 != 0) continue;
//
//		if (current.empty()) {
//			break;
//		}
//
//		auto img = cvtCvimgToMWArray(current);
//
//		
//		//cout<<"调用detLine:"<<sender.getTime(true)<<endl;
//		//detLine(img, NumLine, PosLine, number, mAveX, mAveY, Draw, tmp_img0, xLimit, mTh, img0,dx,dy,d);
//		detLine(4, rS, rN, rX, rY, img,NumLine,pos, draw,tmp_img0, xLimit, mth, img0,dx,dy,d,flag_med,alpha);
//
//		//cout<<"调用完成:"<<sender.getTime(true)<<endl;
//		for (int i = 0; i < lines; i++) {
//			//cout << "vs LINE" << i << " " << rS(i + 1) << endl;
//			if(rS(i + 1)!="Normal!"){//非正常
//			//if(rS(i + 1)=="Line drops!"){//线掉落
//				
//				status.push(1);
//				sum_exception +=1;
//
//				break;
//			}
//			if(i == lines - 1){//到最后一根线还没break，说明都正常
//				status.push(0);//正常状态为0，异常状态为1
//			}
//		}
//		if(status.size()>max_status_size){
//			int old_status = status.front();
//            status.pop();
//			sum_exception -=old_status;
//		}
//		double exception_rate = sum_exception*1.0/status.size();
//		//连续max_status_size次检测到异常概率
//		/*cout<<"exception_rate:"<<exception_rate<<endl;
//		cout<<"sum_exception:"<<sum_exception<<endl;
//		cout<<"status.size():"<<status.size()<<endl;*/
//
//		if(exception_rate>=sender_rate&&status.size()%detect_size==0){
//			cout<<"send exception!"<<endl;
//			if(send_to_server == 1){
//				Mat sendMat = mat_h_merge(first,current);
//				//换名字
//		
//				char image_name[64]={0};
//
//				sprintf(image_name, "%s%s.jpg",cameraInfo,sender.getTime(false));
// 
//				imwrite(image_name,sendMat);
//
//			
//				if(sender.sendfile(image_name)){
//						cout <<sender.getTime(true) << "send file "<<image_name <<" success!" << endl;
//                    
//				}
//				remove(image_name);
//
//				//发完异常重新记录
//				sum_exception = 0;
//				while (!status.empty()){
//					status.pop();
//				}
//			}
//			
//
//		}
//
//	}
//}
//
//void showVideo(string path,int *pointX,int *pointY){
//	
//	
//	Mat I;
//	namedWindow("show", WINDOW_NORMAL);
//	int width = rtsp_w,height = rtsp_h;
//	while(width>1000){
//		width = width * 4/5;
//		height = height * 4/5;
//	}
//		
//
//	resizeWindow("show",width,height);
//	
//	//auto path = "t3.mp4";
//	/*VideoCapture video;
//	if(path == "0")
//		video = cv::VideoCapture(0);
//	else
//		video = cv::VideoCapture(path);*/
//	int count = 0;
//	while(true){
//		
//		
//		//video >> I;
//		I = r->capture();
//		if(!I.empty()){
//			
//					//绘制点
//			int point_count = pointCount(pointX,pointY);
//			for(int i=0;i<point_count;i++){
//				//cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
//				drawPoint(pointX[i],pointY[i],I);
//			}
//
//			imshow("show", I);
//			//Sleep(100);
//			int key = waitKey(50);
//			//Sleep(100);
//			if(key == 27)break;
//			if(key >= 0){
//				while(!r->capture().empty()){
//					cout<<"save first.jpg!"<<endl;
//					imwrite("first.jpg",r->capture().clone());
//					
//					break;
//				}
//				
//			}
//				
//			count++;
//		}
//		
//	}
//}
//
//void init_config(){
//	Config config = Config("config.json");
//	video_src = config["video_src"].asString();
//
//	char* c;  
//	const int len = video_src.length();  
//	c = new char[len+1];  
//	strcpy(c,video_src.c_str());
//
//	//r.rtspAddress = c;
//	r->mrl = video_src;
//
//	rtsp_w = config["width"].asInt();
//	rtsp_h = config["height"].asInt();
//	cout<<"rtsp_w:"<<rtsp_w<<"  "
//		<<"rtsp_h:"<<rtsp_h<<"  "
//		<<video_src<<endl;
//
//
//
//	draw_value = config["draw"].asInt();
//	//是否显示画面
//
//	mth_value = config["mth"].asInt();
//	//用于求取平均位置的连续帧数
//
//
//	d1_value = config["d1"].asInt();
//	d2_value = config["d2"].asInt();
//	//监测区域限定 拟合线到下方白色虚线的距离，拟合线到上方白色虚线的距离
//
//	dx_value = config["dx"].asInt();
//	dy_value = config["dy"].asInt();
//	d_value = config["d"].asInt();
//	//线细的时候 d小点 20  线粗 50
//	//dx,dy: 划定检测所有电力线的区域     d: 每条电线的检测区域
//
//	flag_med_value = config["flag_med"].asInt();
//	//是否中值判定 （一般白天为0）
//	cameraInfo = config["cameraInfo"].asString();
//	sender.init(config["mac"].asString(),cameraInfo,video_src,config["server"].asString());
//
//
//	max_status_size = config["max_status_size"].asInt();//与连续发送异常间隔和检测异常噪音相关（越大，间隔越长，噪音越低）
//	detect_size = config["detect_size"].asInt();//c++部分 每隔多少次检测，统计一次平均异常概率，再决定是否发送异常（排除噪音）
//	sender_rate = config["sender_rate"].asDouble();//当异常几率大于等于sender_rate发送异常图片
//
//	send_to_server = config["send_to_server"].asInt();//为1则发送异常到服务器，否则不发送
//
//	alpha_value = config["alpha_value"].asDouble();//用于消除背景中线状物体的干扰
//}
//
//
//
//int main(int argc ,char *argv[])
//{
//	init_config();
//	//auto path = "C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\detect_demo\\DetectDemo\\x64\\Release\\t1.mp4";
//	
//	//r.start(rtsp_w, rtsp_h);
//    r->width = rtsp_w;
//	r->height = rtsp_h;
//
//	r->init();
//	r->play();
//	Sleep(1000);
//
//    
//	auto path = "night_test.mp4";
//	//auto path = "0";
//
//	//auto path = "rtsp://192.168.8.218:8554/h264";
//	
//
//
//
//	//auto video = cv::VideoCapture(path);
//	//cv::Mat tmp;
//	//video >> tmp;
//	//cv::imwrite("test.jpg",tmp);
//	
//
//	//读取端点和顶点
//	int pointX[100],pointY[100];  
//
//	//addLine(pointX,pointY);
//	
//	int lines = readPoint(pointX,pointY)/3;
//	if(argc>1||argv[1]=="-catch"){
//		cout<<"按任意键保存正常状态图像入first.jpg"<<endl;
//		thread show_streamer(showVideo,path,pointX,pointY);
//		show_streamer.detach();
//		//showVideo(path,pointX,pointY);
//	}else{
//		cout<<"检测模式！"<<endl;
//		videoTest(path,lines,pointX,pointY);	
//	}
//	
//	
//	//thread detect_streamer(videoTest2,path,lines,pointX,pointY);
//	//detect_streamer.detach();
//	//detectMat(lines,pointX,pointY);
//	
//	//thread detect_streamer(detectMat,lines,pointX,pointY);
//	//detect_streamer.detach();
//	//Sender sender;
//	//sender.sendfile("test.jpg");
//	
//
//	system("pause");
//	return 0;
//}