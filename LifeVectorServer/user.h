/**
 * header file for user class which has a constructor to initialize variables
 */
#ifndef USER_H
#define USER_H

#include <iostream>
#include <unistd.h>
#include <string>
//json parser for c++
#include "json.hpp"
using json = nlohmann::json;

class User  
{
 
	public:

		//Full constructor
        User(std::string username, std::string deviceID, std::string hash, std::string salt, json report, int syncTime, int reportTime);
		//Registration constructor
		User(std::string username, std::string deviceID, std::string hash, std::string salt);
        //Barebone constructor
        User(std::string username,std::string deviceID);

		//destructor
		~User();

        std::string getUsername();
		std::string getDeviceID();
		std::string getHash();
	    std::string getSalt();
	    json getReport();
	    long getSyncTime();
	    long getReportTime();

        void setUsername(std::string username);
	    void setDeviceID(std::string devID);
		void setHash(std::string hash);
	    void setSalt(std::string salt);
	    void setReport(json report);
	    void setSyncTime(long syncTime);
	    void setReportTime(long reportTime);

	private:

        std::string self_username;
		std::string self_deviceID;
		std::string self_hash;
		std::string self_salt;
		json self_report;
		long self_syncTime;
		long self_reportTime;
		
};

#endif
