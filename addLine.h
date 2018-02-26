#include "opencv2/opencv.hpp"
#include <fstream>  
#include "iostream"

void on_mouse(int EVENT, int x, int y, int flags, void* userdata);

class AddLine{
public:
	void drawPoint(int x,int y,cv::Mat &I);
	int readPoint(int *pointX,int *pointY);

	void addLine(int *pointX,int *pointY);
	void addLine(int *pointX,int *pointY,std::string path);
};