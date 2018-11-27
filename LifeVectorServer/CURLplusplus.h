/**
 * header file for googleAPI class
 */
#ifndef CURLPLUSPLUS_H
#define CURLPLUSPLUS_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include "json.hpp"
#include <fstream>

class CURLplusplus{

	private:
	    CURL* curl;
	    std::stringstream ss;
	    long http_code;

	public:
	    CURLplusplus() : curl(curl_easy_init()) , http_code(0){

	    }
	    ~CURLplusplus(){

	        if (curl) curl_easy_cleanup(curl);
	    }
	    std::string Get(const std::string& url);
	    long GetHttpCode();

	private:
	    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
	    size_t Write(void *buffer, size_t size, size_t nmemb);
};

#endif

