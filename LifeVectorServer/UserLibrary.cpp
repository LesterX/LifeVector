#include <iostream>
#include <sstream>
#include "UserLibrary.h"
#include "User.h"
using namespace std;
using json = nlohmann::json;

UserLibrary::UserLibrary(){
	db.initDB("localhost", "root", "623062", "LifeVector"); //Remember to change password
}

bool UserLibrary::createUserInDB(User user) {
	string deviceID = user.getDeviceID();
	string hash = user.getHash();
	string salt = user.getSalt();
	json report = user.getReport();
	int syncTime = user.getSyncTime();
	int reportTime = user.getReportTime();

	stringstream ss;
	ss <<  "INSERT INTO User VALUES ('" << deviceID <<
		"','" << hash << "','" << salt << "','" << report << "'," <<
		syncTime << "," << reportTime << ");";
	string sql = ss.str();
	cout << sql << endl;

	if (db.exeSQL(sql)) {
		cout << "User created" << endl;
		return true;
	}
	else {
		cout << "Failed to create user" << endl;
		return false;
	}
}

bool UserLibrary::deleteUserFromDB(User user) {
	
	stringstream ss; 
	ss << "DELETE FROM User WHERE deviceID = '" + user.getDeviceID() + "'";
	string sql = ss.str();

	if (db.exeSQL(sql)) {
		cout << "User deleted" << endl;
		return true;
	}
	else {
		cout << "Failed to delete user" << endl;
		return false;
	}
}

bool UserLibrary::retrieveUser(std::string devID) {}
bool UserLibrary::compareUserHash(std::string devID) {}

bool UserLibrary::updateUserSyncTime(User user, int syncTime) {

	stringstream ss;
	ss << "UPDATE User SET (syncTime = " << syncTime << 
		") WHERE deviceID = '" << user.getDeviceID() << "'";

	string sql = ss.str();

	if (db.exeSQL(sql)) {
		cout << "SyncTime updated" << endl;
		return true;
	}
	else {
		cout << "Failed to update syncTime" << endl;
		return false;
	}
}
bool UserLibrary::updateReport(User user, json report) {
	stringstream ss;
	ss << "UPDATE User SET (report = " << report <<
		") WHERE deviceID = '" << user.getDeviceID() << "'";
	
	string sql = ss.str();

	if (db.exeSQL(sql)) {
		cout << "Report updated" << endl;
		return true;
	}
	else {
		cout << "Failed to update report" << endl;
		return false;
	}
}