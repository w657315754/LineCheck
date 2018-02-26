#include "time.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string> 
#include <vector>
#include <iostream>

#include "math.h"
#include "iostream"
#include <queue>

class Sender{
public:
	Sender();
	std::string mac;
	std::string ip;
	std::string cameraInfo,cameraIP,url;
	int _TH,rect_left,rect_top,rect_right,rect_bottom;
	void init();
	void init(std::string mac,std::string cameraInfo,std::string cameraIP,std::string url);
	std::string getTime(bool withform);
	std::string executeCMD(const char * cmd);
	std::vector<std::string> split(const std::string &s, const std::string &seperator);
	std::string getMac();//
	std::string getSocket(std::string url);
	std::string getpwd();
	std::string getVideoSocket(std::string socket,std::string videoPort);
	bool sendfile(const char* filename);
	bool sendConfigFile(const char* configFilePath);

	
};
