#include "license.h"

License::License(){
	key[0] = 4;
	key[1] = 9;
	key[2] = 6;
	key[3] = 2;
	key[4] = 8;
	key[5] = 7;
	key[6] = 3;
}
std::string License::getTime(bool withform){
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
void License::encode(string& c, int a[]){ 

    for(int i = 0, j = 0; c[j];j++, i = (i + 1) % 7){
        
        c[j]+=a[i];
        
        if(c[j] > 122) c[j] -= 90;
    }
}
void License::decode(string& c,int a[]){ 

    for(int i = 0, j = 0; c[j];j++, i = (i + 1) % 7){
        
        c[j]-=a[i];
        
        if(c[j] < 32) c[j] += 90;
    }
}
bool License::isLegal(string lic){
	decode(lic, key);
	long long now;
	istringstream is1(getTime(false));  
	is1>>now;

	long long lic_value;
	istringstream is2(lic);  
	is2>>lic_value;


	if(lic_value<20180213000000||lic_value>21180213000000){//2118年完全失效
		return false;
	}
	if(now<=lic_value&&now>20180213000000){
		return true;
	}
	else{
		return false;
	}
	
}
int lic_main(){
//int main(){
	int key[] = {4, 9, 6, 2, 8, 7, 3};
	License license;
	//string time = license.getTime(false);
	//cout << "加密前:" << time.c_str() << endl;
	//long long time_i;
	//istringstream is(time);  
	//is>>time_i;
	//cout << "加密前:" << time_i << endl;


 //   //cout << "加密前:" << p << endl;
	//
 //   license.encode(time, key);//加密
 //   
	//cout << "加密后:" << time << endl;
 //   license.decode(time, key);//解密
 //   
	//cout << "解密后:" << time << endl;
	string time_i2 = "20180426000000";
	cout<<"输入过期时间（如 20180426000000）："<<endl;
	cin>>time_i2;

	license.encode(time_i2,key);
	cout << "加密后:" << time_i2 << endl;
	cout<<"证书合法： "<<license.isLegal(time_i2)<<endl;

    int c;
    cin >> c;

	return 0;
}