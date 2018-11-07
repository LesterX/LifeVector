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

		//constructor
		User(std::string deviceID, std::string hash, std::string salt, json report, int syncTime, int reportTime);

		//destructor
		//~User();

		std::string getDeviceID();
		std::string getHash();
	    std::string getSalt();
	    json getReport();
	    int getSyncTime();
	    int getReportTime();

	    void setDeviceID(std::string devID);
		void setHash(std::string hash);
	    void setSalt(std::string salt);
	    void setReport(json report);
	    void setSyncTime(int syncTime);
	    void setReportTime(int reportTime);

	private:

		std::string self_deviceID;
		std::string self_hash;
		std::string self_salt;
		json self_report;
		int self_syncTime;
		int self_reportTime;
		
};

#endif