/**
 * header file for user class which has a constructor to initialize variables
 */
#ifndef USER_H
#define USER_H

#include <iostream>
#include <unistd.h>
#include <string>
//json parser for c++
#include <nlohmann/json.hpp>
 

class user  
{
 
	public:
		
		std::string getDeviceID();
		std::string getHash();
	    std::string getSalt();
	    std::json getReport();
	    std::int getSyncTime();
	    std::int getReportTime();

	    std::string setDeviceID();
		std::string setHash();
	    std::string setSalt();
	    std::json setReport();
	    std::int setSyncTime();
	    std::int setReportTime();

	private:

		std::string self_deviceID;
		std::string self_hash;
		std::string self_salt;
		std::json self_report;
		std::int self_syncTime;
		std::int self_reportTime;
		//constructor
		user(std::string deviceID, std::string hash, std::string salt, std::json report, std::int syncTime, std::int reportTime;){

			self_deviceID = deviceID;
			self_hash = hash;
			self_salt = salt;
			self_report = report;
			self_syncTime = syncTime;
			self_reportTime = reportTime;
		};

		//destructor
		~user();
    
};

#endif