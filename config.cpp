#include "config.h"

Config::Config(const string& path) :
    path(path),
    cached(false)
{
    this->conf = this->load(false);
}

Config::~Config()
{
    /**/
}

string Config::readFile(const string& path)
{
    ifstream file(path);

    if (! file.is_open()) {
        return "";
    }

    string content(
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>())
    );

    file.close();

    return content;
}

void Config::writeFile(const string& path, const string& contents)
{
    ofstream file(path);

    if (! file.is_open()) {
        return;
    }

    file << contents;

    file.close();
}

Json::Value& Config::load(bool reload)
{
    if (! reload && this->cached) {
        return this->conf;
    }

    Json::Reader reader;
    auto content = this->readFile(this->path); 

    if (! reader.parse(content, this->conf)) {
        cout << "Parse err." << endl;
    }

    this->cached = true;

    return this->conf;
}

void Config::save()
{
    Json::StyledWriter writer;

    string contents = writer.write(this->conf);

    this->writeFile(this->path, contents);
}

Json::Value& Config::operator[](const string& key)
{
    return this->conf[key];
}

