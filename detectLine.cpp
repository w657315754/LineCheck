//#include "detectLine.h"
//#include "vclient.h"
//#include "sender.h"
//#include "license.h"
//using namespace cv;
//
//std::unique_ptr<Vclient> r(new Vclient());
//string video_src = "rtsp://127.0.0.1:8554/h264";
//int rtsp_w = 1920, rtsp_h = 1080;
//Mat I;
//ofstream outfile;
//int pointX[100],pointY[100]; 
//
//int max_status_size = 100;
//vector<queue<int>> lines_status;//�����ߵ�״̬
//vector<int> lines_sum_exception;//ÿ�����쳣�ܺ�
//double sender_rate = 0.9;//���쳣���ʴ��ڵ���sender_rate�����쳣ͼƬ
//int detect_size = 20;
//int send_to_server = 0;
//int showResult = 1;
//string cameraInfo = "default";
//
//int medianBlur_ksize = 5;
//
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
////��ȡ2��������߶���ԭͼ���±�
//vector<Point> getLineIndex(int x1,int y1,int x2,int y2){
//	vector<Point> lineIndex;
//	for(int x = min(x1,x2);x<=max(x1,x2);x++)
//		for(int y = min(y1,y2);y<=max(y1,y2);y++)
//			if((y-y2)/(y1-y2)==(x-x2)/(x1-x2)){
//				lineIndex.push_back(Point(x,y));
//			}
//	return lineIndex;
//}
//void readPoint(int *pointX,int *pointY){
//	ifstream infile;  
//    infile.open("lines.txt");  
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
//}
//int pointCount(int *pointX,int *pointY){
//	int count = 0; 
//	for(int i=0;i<100;i++){
//		if((pointX[count]>0&&pointY[count]>0)&&(pointX[count]<10000&&pointY[count]<10000))
//			count++;
//	}
//	return count;
//}
//void drawPoint(int x,int y,cv::Mat &I){
//
//	circle(I, Point(x,y),3,Scalar(255,255,255),-1);
//}
//void drawLine(int x1,int y1,int x2,int y2,cv::Mat &I){
//
//	line(I, Point(x1,y1),Point(x2,y2),Scalar(255,255,255),3);
//}
//void drawLine(int x1,int y1,int x2,int y2,cv::Mat &I,Scalar scalar){
//
//	line(I, Point(x1,y1),Point(x2,y2),scalar,3);
//}
//
////����ӵ㣬�Ҽ�����
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
//                cout<<"uchar :"<<(int)I.at<uchar>(p.y,p.x)<<endl;
//                circle(hh, p,3,Scalar(255,255,255),-1);
//				outfile.open("lines.txt",ios::app);
//				outfile<<p.x<<endl;
//				outfile<<p.y<<endl;
//				int count = pointCount(pointX,pointY);
//				pointX[count] = p.x;
//				pointY[count] = p.y;
//
//				outfile.close();
//				imshow("show", I);
//            }
//            break;
//			case EVENT_RBUTTONDOWN:
//            {
//
//				outfile.open("lines.txt",ios::out);
//				
//				outfile.close();
//
//				for(int i=0;i<100;i++){
//					pointX[i] =-1;
//					pointY[i] =-1;
//				}
//				lines_sum_exception.clear();
//				lines_status.clear();
//				imshow("show", I);
//            }
//            break;
//        }
//
//    }
//void stretch(IplImage* src,IplImage* dst,int nMin,int nMax)  
//{  
//    int low_value=nMin;    //��������ص���Сֵ   
//    int high_value=nMax;   //��������ص����ֵ  
//  
//    float rate=0;          //ͼ���������  
//  
//    float stretch_p[256],stretch_p1[256],stretch_num[256];  
//    //�����������,��ʼ���������Ԫ��Ϊ0  
//    memset(stretch_p,0,sizeof(stretch_p));  
//    memset(stretch_p1,0,sizeof(stretch_p1));  
//    memset(stretch_num,0,sizeof(stretch_num));  
//    //ͳ��ͼ������Ҷȼ����ֵĴ���  
//    uchar* srcData=(uchar*)src->imageData;  
//    uchar* dstData=(uchar*)dst->imageData;  
//    int nHeight=src->height;  
//    int nWidth=src->width;  
//    int i,j;  
//    uchar nVal=0;  
//    for (i=0;i<nHeight;i++)  
//    {  
//        for (j=0;j<nWidth;j++)  
//        {  
//            nVal=srcData[i*nWidth+j];  
//            stretch_num[nVal]++;  
//        }  
//    }  
//    //ͳ�Ƹ����Ҷȼ����ֵĸ���  
//    for (i=0;i<256;i++)  
//    {  
//        stretch_p[i]=stretch_num[i]/(nHeight*nWidth);  
//    }  
//    //ͳ�Ƹ����Ҷȼ��ĸ��ʺ�  
//    for (i=0;i<256;i++)  
//    {  
//        for (j=0;j<=i;j++)  
//        {  
//            stretch_p1[i]+=stretch_p[j];  
//        }  
//    }  
//    //����������ֵ���ֵ  
//    for (i=0;i<256;i++)  
//    {  
//        if (stretch_p1[i]<0.1)     //low_valueȡֵ�ӽ���10%�������صĻҶ�ֵ  
//        {  
//            low_value=i;  
//        }  
//        if (stretch_p1[i]>0.9)     //high_valueȡֵ�ӽ���90%�������صĻҶ�ֵ  
//        {  
//            high_value=i;  
//            break;  
//        }  
//    }  
//    rate=(float)255/(high_value-low_value+1);  
//    //���лҶ�����  
//    for (i=0;i<nHeight;i++)  
//    {  
//        for (j=0;j<nWidth;j++)  
//        {  
//            nVal=srcData[i*nWidth+j];  
//            if (nVal<low_value)  
//            {  
//                dstData[i*nWidth+j]=0;  
//            }  
//            else if (nVal>high_value)  
//            {  
//                dstData[i*nWidth+j]=255;  
//            }  
//            else  
//            {  
//                dstData[i*nWidth+j]=(uchar)((nVal-low_value)*rate+0.5);  
//                if (dstData[i*nWidth+j]>255)  
//                {  
//                    dstData[i*nWidth+j]=255;  
//                }  
//            }  
//        }  
//    }  
//}
//int main(){
//	readPoint(pointX,pointY);
//	Config config = Config("config.json");
//
//	License license;
//	
//	if(license.isLegal(config["lic"].asString())){
//		cout<<"֤��Ϸ�"<<endl;	
//	}else{
//		cout<<"֤�鲻�Ϸ�"<<endl;
//		exit(0);
//	}
//	//init config
//	string video_src = config["video_src"].asString();
//	max_status_size = 2*config["max_status_size"].asInt();//�����������쳣����ͼ���쳣������أ�Խ�󣬼��Խ��������Խ�ͣ�
//	detect_size = 2*config["detect_size"].asInt();//c++���� ÿ�����ٴμ�⣬ͳ��һ��ƽ���쳣���ʣ��پ����Ƿ����쳣���ų�������
//	sender_rate = config["sender_rate"].asDouble();//���쳣���ʴ��ڵ���sender_rate�����쳣ͼƬ
//	send_to_server = config["send_to_server"].asInt();//Ϊ1�����쳣�������������򲻷���
//
//	medianBlur_ksize = config["medianBlur_ksize"].asInt();//��ֵ�˲� ksize���� ����5������3
//
//	showResult = config["showResult"].asInt();//�Ƿ���ʾ�����Ļ���
//
//
//	Sender sender;
//	cameraInfo = config["cameraInfo"].asString();
//	sender.init(config["mac"].asString(),cameraInfo,video_src,config["server"].asString());
//
//	r->mrl = video_src;
//
//
//	VideoCapture video;
//	if(video_src == "0")
//		video = cv::VideoCapture(0);
//	else
//		video = cv::VideoCapture(video_src);
//	//video = cv::VideoCapture("cloud.mp4");
//
//	video>>I;
//
//	
//	
//	config["width"]=I.cols;
//	config["height"] = I.rows;
//
//	config.save();
//
//	r->width = I.cols;
//	r->height = I.rows;
//
//	r->init();
//	r->play();
//	Sleep(1000);
//
//
//	namedWindow("show", WINDOW_NORMAL);
//	resizeWindow("show",640,480);
//	Mat first;
//	first = r->capture();
//	while(first.empty()){
//		first = r->capture();
//	}
//	cout<<"save first.jpg!"<<endl;
//	imwrite("first.jpg",first);	
//	
//	while(true){
//		
//		//video >> I;
//		I = r->capture();
//		
//
//		if(!I.empty()){
//			//cout<<"width:"<<I.cols<<"height:"<<I.rows<<endl;
//
//			cvtColor(I,I, COLOR_BGR2GRAY);
//			
//
//			//����˲�
//			//double h[25]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};//
//			Mat h = (Mat_<int>(5,5)<<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1);
//			filter2D( I, I, I.depth(),h);  //��ο���Ϊ�˵�����
//
//			
//
//			
//			//IplImage img = I;
//			//IplImage *input = cvCloneImage(&img);
//			//stretch(input,input,30,40);
//			//stretch(input,input,1,200);
//			
//			//I = input;
//
//			// ��ֵ�˲����� medianBlur_ksize ����ȡ3������ȡ5
//			medianBlur(I, I, medianBlur_ksize);
//			//medianBlur(I, I, 5);
//			
//			//��Ե���
//			Canny(I,I,60,120,3); 
//
//			//�����븯ʴ
//			cv::dilate(I, I, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
//
//
//			cv::setMouseCallback("show",on_mouse,&I);
//			int count = pointCount(pointX,pointY);
//		
//
//			vector<vector<Point>> linesIndex;
//			for(int i=0;i<count/2;i++){
//
//				//��Ҫ��ȡ2��������߶���ԭͼ���±�
//				vector<Point> lineIndex;
//				lineIndex = getLineIndex(pointX[2*i],pointY[2*i],pointX[2*i+1],pointY[2*i+1]);
//				linesIndex.push_back(lineIndex);
//			}
//
//			vector<int> lines_cross;
//			for(int i = 0;i < linesIndex.size();i++){
//				
//				int cross = 0;
//				vector<Point> lineIndex = linesIndex[i];
//				for(int j=0;j<lineIndex.size();j++){
//					//if((int)I.at<uchar>(lineIndex[j].x,lineIndex[j].y)!=0){
//					if((int)I.at<uchar>(lineIndex[j].y,lineIndex[j].x)!=0){
//						cross++;
//					}
//				}
//				cout<<"line"<<i+1<<" cross:"<<cross<<endl;
//				lines_cross.push_back(cross);
//			}
//
//
//			//�ߵ�ƽ��״̬��ʼ�����ı�
//			for (int i = 0; i < lines_cross.size(); i++) {
//				queue<int> line_status;//һ��������״̬
//				int line_sum_exception = 0;
//
//				if(lines_status.size()==i){
//					//��ʼ��lines_status��lines_sum_exception
//					lines_status.push_back(line_status);
//					lines_sum_exception.push_back(line_sum_exception);
//				}
//				//
//
//				if(lines_cross[i]==0){//������
//				//if(rS(i + 1)=="Line drops!"){//�ߵ���
//				
//					lines_status[i].push(1);
//					lines_sum_exception[i] +=1;
//
//					//break;
//				}
//				if((i == lines_cross.size() - 1)&&lines_cross[i]!=0){//�����һ���߻�ûbreak��˵��������
//					lines_status[i].push(0);//����״̬Ϊ0���쳣״̬Ϊ1
//				}
//
//
//				if(lines_status[i].size()>max_status_size){
//					int old_status = lines_status[i].front();
//					lines_status[i].pop();
//					lines_sum_exception[i] -=old_status;
//				}
//
//
//
//			}
//			int exception_line = -1;
//			//�ж��Ƿ����쳣
//			for (int i = 0; i < lines_cross.size(); i++) {
//				double exception_rate = lines_sum_exception[i]*1.0/lines_status[i].size();
//				if(exception_rate>=sender_rate&&lines_status[i].size()%detect_size==0){
//					cout<<"�����쳣! ��"<<i+1<<"��"<<endl;
//					exception_line = i;
//					cout<<"exception_rate:"<<exception_rate<<endl;
//					cout<<"sum_exception:"<<lines_sum_exception[i]<<endl;
//					cout<<"status.size():"<<lines_status[i].size()<<endl;
//
//					if(send_to_server == 1){
//						Mat current = r->capture();
//						while(current.empty()){
//							current = r->capture();
//						}
//						Mat sendMat = mat_h_merge(first,current);
//						//������
//		
//						char image_name[64]={0};
//
//						sprintf(image_name, "%s%s.jpg",cameraInfo,sender.getTime(false));
// 
//						imwrite(image_name,sendMat);
//
//			
//						if(sender.sendfile(image_name)){
//								cout <<sender.getTime(true) << "send file "<<image_name <<" success!" << endl;
//                    
//						}
//						remove(image_name);
//
//				
//					}
//
//
//
//					//�����쳣���¼�¼
//					lines_sum_exception.clear();
//					lines_status.clear();
//
//					break;
//				}
//			}
//			
//			//����max_status_size�μ�⵽�쳣����
//			/*cout<<"exception_rate:"<<exception_rate<<endl;
//			cout<<"sum_exception:"<<sum_exception<<endl;
//			cout<<"status.size():"<<status.size()<<endl;*/
//
//			if(showResult==0){
//				I = r->capture();
//				while(I.empty()){
//					I = r->capture();
//				}
//			}else{
//				 cvtColor(I,I,CV_GRAY2BGR);
//			}
//
//			//���Ƶ�
//			for(int i=0;i<count;i++){
//				//cout<<"x:"<<pointX[i]<<"y:"<<pointY[i]<<endl;
//				drawPoint(pointX[i],pointY[i],I);
//			}
//			
//			for(int i=0;i<count/2;i++){
//				//������
//				if(exception_line!=-1)
//					drawLine(pointX[2*i],pointY[2*i],pointX[2*i+1],pointY[2*i+1],I,Scalar(0,0,255));
//				else
//					drawLine(pointX[2*i],pointY[2*i],pointX[2*i+1],pointY[2*i+1],I,Scalar(0,255,0));
//			}
//			imshow("show", I);
//
//			
//			  
//			//����ͼƬ���߶������±�
//
//
//			int key = waitKey(50);
//			if(key == 27)break;
//			if(key >= 0){
//				while(!r->capture().empty()){
//					cout<<"save first.jpg!"<<endl;
//					imwrite("first.jpg",r->capture().clone());	
//					first = imread("first.jpg");
//					break;
//				}
//				
//			}
//		}
//		
//	}
//
//
//	DetectLine DetectLine;
//	system("pause");
//	return 0;
//}
//
