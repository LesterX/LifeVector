/**
 * cpp file for user class which contains getters and setters
 */

#include "User.h"


using namespace std;

	User::User(std::string deviceID, std::string hash, std::string salt, json report, int syncTime, int reportTime) {
		self_deviceID = deviceID;
		self_hash = hash;
		self_salt = salt;
		self_report = report;
		self_syncTime = syncTime;
		self_reportTime = reportTime;
	}

	string User :: getDeviceID(){
		return self_deviceID;
	}
	string User :: getHash(){
		return self_hash;
	}
    string User :: getSalt(){
    	return self_salt;
    }
    json User:: getReport(){
    	return self_report;
    }
    int User :: getSyncTime(){
    	return self_syncTime;
    }
    int User :: getReportTime(){
    	return self_reportTime;
    }

    string User :: setDeviceID(string deviceID){
    	self_deviceID = deviceID;
    }
	string User :: setHash(string hash){
		self_hash = hash;
	}
    string User :: setSalt(string salt){
    	self_salt = salt;
    }
    json User:: setReport(json report){
    	self_report = report;
    }
    int User :: setSyncTime(int syncTime){
    	self_syncTime = syncTime;
    }
    int User :: setReportTime(int reportTime){
    	self_reportTime = reportTime;
    }