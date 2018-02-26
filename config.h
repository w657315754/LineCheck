#include "sstream"
#include "fstream"
#include "iostream"
#include "json/json.h"

using namespace std;

class Config {

    public:
        string      path;
        Json::Value conf;
        bool        cached;


        Config(const string& path);
        ~Config();

        string          readFile(const string& path);
        void            writeFile(const string& path, const string& contents);

        Json::Value&    load(bool reload = false);
        void            save();

        Json::Value& operator[](const string& key);

};
