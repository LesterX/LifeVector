/**
 * header file for placesAPI class
 */
#ifndef PLACESAPI_H
#define PLACESAPI_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include "json.hpp"
#include <fstream>
#include "CURLplusplus.h"
#include <stdio.h>
#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>



class placesAPI{

	private:

	    std::string placeid;
	    nlohmann::json doc;
	    std::string name;
        std::string location;
        long time;

	public:

		placesAPI(std::string place_id){
			//constructor

			placeid = place_id;

			CURLplusplus client;

	        std::string key = "&key=AIzaSyBJ6CP4wYrqVvOVq-ohJw-0aX6yU0mLu5c";

	        std::string url = "https://maps.googleapis.com/maps/api/place/details/json?placeid=" +  placeid + key;

	        std::string x = client.Get(url);

	        doc = nlohmann::json::parse(x);

	        std::ofstream o("placesOutput.json");

        	o << doc << std::endl;
		}

		~placesAPI(){
			//destructor
		}


	    std::string getLocationName();

	    void splitstr(const std::string& str, std::vector<std::string>& container, char delim);


};

#endif

