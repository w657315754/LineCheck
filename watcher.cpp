//#include "config.h"
//#include <Windows.h>
//#include <thread>
//#include "sender.h"
//
//int main(){
//	Sender sender;
//	Config config = Config("config.json");
//	
//	thread detect_streamer(system,"main");
//	detect_streamer.detach();
//
//	sender.init(config["mac"].asString(),config["cameraInfo"].asString(),config["video_src"].asString(),config["server"].asString());
//
//	//发送一份
//	cout<<"发送配置文件到服务器！"<<endl;
//	sender.sendConfigFile("config.json");
//
//
//	while(true){
//		int restart = config["restart"].asInt();
//		if(restart == 1){
//			cout << "重启检测程序！"<<endl;
//			config["restart"] = 0;
//			config.save();
//
//			system("tskill main");
//			thread detect_streamer(system,"main");
//			detect_streamer.detach();
//
//			sender.sendConfigFile("config.json");
//
//		}else if(restart == 2){//额外的功能2为远程关闭、1为远程开启
//			cout << "远程关闭检测程序！"<<endl;
//			config["restart"] = 3;
//			config.save();
//			system("tskill main");
//			sender.sendConfigFile("config.json");
//			
//		}else if(restart == 3){//额外的功能2为远程关闭、1为远程开启
//			cout << "检测程序已关闭！"<<endl;
//			
//			
//		}else{
//			cout << "正常运行！"<<endl;
//		}
//
//		Sleep(5000);
//
//		
//		
//		config = Config("config.json");
//	}
//	
//	
//	
//
//	return 0;
//}