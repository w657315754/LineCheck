#include <iostream>
#include <opencv2/core/core.hpp>    
#include "opencv2/opencv.hpp" 
#include <opencv2/highgui/highgui.hpp>    
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/imgproc/imgproc_c.h"
#include <fstream>  
#include "math.h"  
#include <vector>


using namespace cv;  
using namespace std; 
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
