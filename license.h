#include "iostream"
//#include "time.h"
#include <ctime>
#include <sstream>
using namespace std;

//int key[] = {4, 9, 6, 2, 8, 7, 3};
class License{
public:
	int key[7];
	License();
	std::string getTime(bool withform);
	void encode(string& c, int a[]);
	void decode(string& c,int a[]);
	bool isLegal(string lic);
};
