/**
 * header file for googleAPI class
 */
#ifndef GOOGLEAPI_H
#define GOOGLEAPI_H

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



class googleAPI{

	private:

	    std::string lat;
	    std::string lng;
	    nlohmann::json doc;
	    std::string name;
        std::string location;
        long time;
    
	public:

		googleAPI(std::string latitude, std::string longitude, long t){
			//constructor
			
			lat = latitude;
        	lng = longitude;
            time = t;

			CURLplusplus client;
	    
	        std::string latlng = lat + "," + lng;
	        std::string key = "&key=AIzaSyDhWjQTwKez6FFd4V6WOC8RCgNUUvIf22Y";

	        std::string url = "https://maps.googleapis.com/maps/api/geocode/json?latlng=" +  latlng + key;

	        std::string x = client.Get(url);

	        doc = nlohmann::json::parse(x);

	        std::ofstream o("output.json");

        	o << doc << std::endl;
		}

		~googleAPI(){
			//destructor
		}
	    
	    void setlatlng(std::string latitude, std::string longitude);

	    std::string getFormattedLocation();

	    std::string getNorthEastLat();
	    std::string getNorthEastLng();
	    std::string getSouthWestLat();
	    std::string getSouthWestLng();
	    std::string getTypes();
	    std::string getName();
        long getTime();
	    void splitstr(const std::string& str, std::vector<std::string>& container, char delim);


};

#endif

