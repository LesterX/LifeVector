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
        std::string unwantedTypes = "administrative_area_level_1, administrative_area_level_2, administrative_area_level_3, administrative_area_level_4, administrative_area_level_5, country, intersection, locality, neighborhood, political, post_box, postal_code, postal_code_prefix, postal_code_suffix, postal_town, premise, route, street_address, street_number, sublocality, sublocality_level_4, sublocality_level_5, sublocality_level_3, sublocality_level_2, sublocality_level_1, subpremise";

	public:

		googleAPI(std::string latitude, std::string longitude){
			//constructor
			
			lat = latitude;
        	lng = longitude;

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
	    std::string getName();

        std::string getLat();
        std::string getLng();
	    std::string getNorthEastLat();
	    std::string getNorthEastLng();
	    std::string getSouthWestLat();
	    std::string getSouthWestLng();
	    std::string getTypes(int j);
	    std::vector<std::string> getTypesArray(int j);
	    std::string getPlaceID(int j);
	    std::string getValidPlace();
	    bool checkTypes(int j);
	    void splitstr(const std::string& str, std::vector<std::string>& container, char delim);


};

#endif

