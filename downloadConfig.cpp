//#include "config.h"
//#include "sender.h"
//#include <Windows.h>
//int main(){
//
//	Config config = Config("config.json");
//	Sender sender;
//	string path = "http://114.80.141.78:57772/CURLRecvPOST/upload/00:0e:c4:d1:f1:2f!config.json";
//	
//	char cmd[1024]={0};
//
//	string serverSocket = sender.getSocket(config["server"].asString());
//	string mac = config["mac"].asString();
//	
//	sprintf(cmd,"curl -o temp.json http://%s/CURLRecvPOST/upload1/%s!config.json",serverSocket.c_str(),mac.c_str());
//	printf(cmd);
//	
//	
//	while(true){
//		system(cmd);
//		Config temp = Config("temp.json");
//		if(temp["mac"].asString()==config["mac"].asString()){
//			//表示获取的文件为确实配置文件
//			cout<<"更新下载的配置文件！"<<endl;
//			temp.path = config.path;
//			temp.save();
//
//		}
//		Sleep(5000);
//	}
//	
//	
//	
//
//	system("pause");
//	return 0;
//}