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
//	//����һ��
//	cout<<"���������ļ�����������"<<endl;
//	sender.sendConfigFile("config.json");
//
//
//	while(true){
//		int restart = config["restart"].asInt();
//		if(restart == 1){
//			cout << "����������"<<endl;
//			config["restart"] = 0;
//			config.save();
//
//			system("tskill main");
//			thread detect_streamer(system,"main");
//			detect_streamer.detach();
//
//			sender.sendConfigFile("config.json");
//
//		}else if(restart == 2){//����Ĺ���2ΪԶ�̹رա�1ΪԶ�̿���
//			cout << "Զ�̹رռ�����"<<endl;
//			config["restart"] = 3;
//			config.save();
//			system("tskill main");
//			sender.sendConfigFile("config.json");
//			
//		}else if(restart == 3){//����Ĺ���2ΪԶ�̹رա�1ΪԶ�̿���
//			cout << "�������ѹرգ�"<<endl;
//			
//			
//		}else{
//			cout << "�������У�"<<endl;
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