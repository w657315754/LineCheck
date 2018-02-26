//#include "config.h"
//#include "sender.h"
//
//int main(){
//
//	Sender sender;
//	Config config = Config("config.json");
//	string video_src = config["video_src"].asString();
//	string server = config["server"].asString();
//	string videoPort = "10554";
//	
//	string videoSocket = sender.getVideoSocket(sender.getSocket(server),videoPort);
//	// ffmpeg -i rtsp://192.168.8.218:8554/h264 -vcodec copy -acodec copy  -rtsp_transport tcp -f rtsp rtsp://114.80.141.78:10554/cameraIP=rtsp://192.168.8.218:8554/h264
//	
//	
//	char cmd[1024]={0};
//	sprintf(cmd,"ffmpeg -i %s -vcodec copy -acodec copy  -rtsp_transport tcp -f rtsp rtsp://%s/cameraIP=%s",video_src.c_str(),videoSocket.c_str(),video_src.c_str());
//	printf("%s\n",cmd);
//
//	system(cmd);
//
//	system("pause");
//	return 0;
//}