/**
 * cpp file for user class which contains getters and setters
 */

#include "user.h"


using namespace std;

	string user :: getDeviceID(){
		return self_deviceID;
	}
	string user :: getHash(){
		return self_hash;
	}
    string user :: getSalt(){
    	return self_salt;
    }
    json user:: getReport(){
    	return self_report;
    }
    int user :: getSyncTime(){
    	return self_syncTime;
    }
    int user :: getReportTime(){
    	return self_reportTime;
    }

    string user :: setDeviceID(string deviceID){
    	self_deviceID = deviceID;
    }
	string user :: setHash(string hash){
		self_hash = hash;
	}
    string user :: setSalt(string salt){
    	self_salt = salt;
    }
    json user:: setReport(json report){
    	self_report = report;
    }
    int user :: setSyncTime(int syncTime){
    	self_syncTime = syncTime;
    }
    int user :: setReportTime(int reportTime){
    	self_reportTime = reportTime;
    }