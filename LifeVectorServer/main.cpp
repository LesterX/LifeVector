/*
to instal cURL on debian run :
sudo apt-get install libcurl4-openssl-dev

to compile as "main" executable run:
g++ main.cpp -L/usr/include/curl/lib -lcurl

to run:
./main

*/

/*queries google api and returns json formatted text*/

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include "json.hpp"
#include <fstream>

using namespace std;

class CURLplusplus
{
private:
    CURL* curl;
    std::stringstream ss;
    long http_code;
public:
    CURLplusplus()
            : curl(curl_easy_init())
    , http_code(0)
    {

    }
    ~CURLplusplus()
    {
        if (curl) curl_easy_cleanup(curl);
    }
    std::string Get(const std::string& url)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        ss.str("");
        http_code = 0;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            throw std::runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        return ss.str();
    }
    long GetHttpCode()
    {
        return http_code;
    }
private:
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
    }
    size_t Write(void *buffer, size_t size, size_t nmemb)
    {
        ss.write((const char*)buffer,size*nmemb);
        return size*nmemb;
    }
};


int main(int argc, char** argv) {

	CURLplusplus client;

	string lat = "40.714224";
	string lng = "-73.961452";
	string latlng = lat + "," + lng;
	string key = "&key=AIzaSyDhWjQTwKez6FFd4V6WOC8RCgNUUvIf22Y";

	string url = "https://maps.googleapis.com/maps/api/geocode/json?latlng=" +  latlng + key;

	string x = client.Get(url);

	nlohmann::json doc = nlohmann::json::parse(x);

//	doc.dump(4);

	ofstream o("output.json");

	o << doc << endl;

	cout << doc.at("results")[0].at("formatted_address") << endl;

//	cout << "------------------------------" << endl;

//	std:: cout << x << endl;

	return 0;
}
