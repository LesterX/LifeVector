#include <iostream>
#include "UserLibrary.h"
#include "User.h"
using namespace std;
//using json = nlohmann::json

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

	string sql = "INSERT INTO User VALUES ('" + deviceID +
		"','" + hash + "','" + salt + "'," + report + "," +
		syncTime + "," + reportTime;

	if (db.exeSQL(sql)) {
		cout << "User created" << endl;
		return true;
	}
	else {
		cout << "Failed to create user" << endl;
		return false;
	}
}

bool deleteUserFromDB(User user) {
	
	string sql = "DELETE FROM User WHERE deviceID = '" + user.getDeviceID() + "'";

	if (db.exeSQL(sql)) {
		cout << "User deleted" << endl;
		return true;
	}
	else {
		cout << "Failed to delete user" << endl;
		return false;
	}
}

bool retrieveUser(std::string devID);
bool compareUserHash(std::string devID);

bool updateUserSyncTime(User user, int syncTime) {

	string sql = "UPDATE User SET (syncTime = " + syncTime + 
		") WHERE deviceID = '" + user.getDeviceID() + "'";

	if (db.exeSQL(sql)) {
		cout << "SyncTime updated" << endl;
		return true;
	}
	else {
		cout << "Failed to update syncTime" << endl;
		return false;
	}
}
bool updateReport(User user, json report) {
	string sql = "UPDATE User SET (report = " + report +
		") WHERE deviceID = '" + user.getDeviceID() + "'";

	if (db.exeSQL(sql)) {
		cout << "Report updated" << endl;
		return true;
	}
	else {
		cout << "Failed to update report" << endl;
		return false;
	}
}