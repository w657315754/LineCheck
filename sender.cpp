#include "sender.h"


using namespace std;

string Sender::getTime(bool withform)
{
    time_t timep;
    time (&timep);
    char tmp[64];
    if(withform){
        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    }else{
        strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S",localtime(&timep) );
    }

    return tmp;
}
string Sender::executeCMD(const char * cmd)  
{  
	char pRetMsg[128] = { 0 };
	int msg_len = sizeof(pRetMsg);

    FILE * fp;  
    char * p = NULL;  
    int res = -1;  
    if (cmd == NULL || pRetMsg == NULL || msg_len < 0)  
    {  
        printf("Param Error!\n");  
        return "-1";  
    }  
    if ((fp = _popen(cmd, "r")) == NULL)  
    {  
        printf("Popen Error!\n");  
        return "-2";  
    }  
    else  
    {  
        memset(pRetMsg, 0, msg_len);  
        //get lastest result    
        while (fgets(pRetMsg, msg_len, fp) != NULL)  
        {  
            printf("Msg:%s", pRetMsg); //print all info    
        }  
  
        if ((res = _pclose(fp)) == -1)  
        {  
            printf("close popenerror!\n");  
            return "-3";  
        }  
        pRetMsg[strlen(pRetMsg) - 1] = '\0';  
        return pRetMsg;  
    }  
}  

vector<string> Sender::split(const string &s, const string &seperator){
	
        // cout <<"split:"<<s<<endl;
        vector<string> result;

        typedef std::string::size_type string_size;
        string_size i = 0;
        while(i != s.size()){
        //找到字符串中首个不等于分隔符的字母；
        int flag = 0;
            while(i != s.size() && flag == 0){
            flag = 1;
            for(string_size x = 0; x < seperator.size(); ++x)
                if(s[i] == seperator[x]){
                    ++i;
                    flag = 0;
                    break;
                }
        }
    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
        for(string_size x = 0; x < seperator.size(); ++x)
            if(s[j] == seperator[x]){
                flag = 1;
                break;
            }
        if(flag == 0) 
            ++j;
        }
        if(i != j){
            result.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return result;
}
string Sender::getSocket(string url){
    
	std::vector<std::string> v = split(url, "/");
    for(vector<string>::size_type i = 0; i != v.size(); ++i)
    {

        if(v[i]=="CURLRecvPOST")
            return v[i-1];
    }
    return "";
}
string Sender::getpwd(){
    return executeCMD("cd");
}

string Sender::getVideoSocket(string socket,string videoPort){
    vector<string> v = split(socket, ":");
    if(v.size() > 1){
        return v[0]+":"+videoPort;
    }
    return "";
}
bool Sender::sendfile(const char* filename){
    char cmd[1024]={0};

    sprintf(cmd, "curl --form conf=\"%s!%s!%s!%d!%d!%d!%d!%d!%s!%s\" --form \"imageName=%s\" --form \"exceptionTime=%s\" --form \"file=@%s\" %s",mac.c_str(),cameraInfo.c_str(),cameraIP.c_str(),0,0,0,0,0,getpwd().c_str(),url.c_str(),filename,getTime(true).c_str(),filename,url.c_str());
    
    printf("%s\n", cmd);
    return system(cmd)==0; 
	//return 0;
}
bool Sender::sendConfigFile(const char* configFilePath){
    char cmd[1024]={0};

	//sprintf(cmd, "curl --form conf=\"%s!%s!%s!%d!%d!%d!%d!%d!%s!%s\" --form \"imageName=%s\" --form \"exceptionTime=%s\" --form \"file=@%s\" %s",mac.c_str(),cameraInfo.c_str(),cameraIP.c_str(),0,0,0,0,0,getpwd().c_str(),url.c_str(),filename,getTime(true).c_str(),filename,url.c_str());
    sprintf(cmd, "curl --form conf=\"%s!%s!%s!%d!%d!%d!%d!%d!%s!%s\" --form \"exceptionTime=%s\" --form \"configfile=@%s\" %s",mac.c_str(),cameraInfo.c_str(),cameraIP.c_str(),_TH,rect_left,rect_top,rect_right,rect_bottom,getpwd().c_str(),url.c_str(),getTime(true).c_str(), configFilePath,url.c_str());

    printf("%s\n", cmd);
    return system(cmd)==0; 
	//return 0;
}
Sender::Sender(){
	init();

}
void Sender::init(){
	mac = "00:0e:c4:d1:f1:2f";
	ip = "192.168.8.88";
	cameraInfo = "test";
	cameraIP = "rtsp://192.168.8.220:8554/h264";
	url = "http://114.80.141.78:57772/CURLRecvPOST/PostRecvServlet?method=upload";

}
void Sender::init(std::string mac,std::string cameraInfo,std::string cameraIP,std::string url){
	//init();
	this->mac = mac;
	this->cameraInfo = cameraInfo;
	this->cameraIP = cameraIP;
	this->url = url;

}
