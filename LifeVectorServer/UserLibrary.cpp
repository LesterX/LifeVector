#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>
#include "UserLibrary.h"
#include "User.h"
using namespace std;
using json = nlohmann::json;

/*
 User Table Creating Query
 CREATE TABLE User(
 username CHAR(10) NOT NULL,
 deviceID CHAR(10) NOT NULL,
 hash CHAR(128),
 salt CHAR(128),
 report JSON,
 syncTime BIGINT,
 reportTime BIGINT,
 PRIMARY KEY (username,deviceID)
 );
 */

//Building connection to LifeVector database
UserLibrary :: UserLibrary(){
	db.initDB("localhost", "root", "623062", "LifeVector"); //Remember to change password
}

//Create User table (might cause error if the table already exists)
bool UserLibrary :: createUserTable(){
    stringstream ss;
    ss << "CREATE TABLE USER(username CHAR(10) NOT NULL," <<
    "deviceID CHAR(10) NOT NULL," <<
    "hash CHAR(128)," <<
    "salt CHAR(128)," <<
    "report JSON," <<
    "syncTime BIGINT," <<
    "reportTime BIGINT," <<
    "PRIMARY KEY (username,deviceID));";
    
    string sql = ss.str();
    if (db.exeSQL(sql)) {
        cout << "User Table created" << endl;
        return true;
    }
    else {
        cout << "Failed to create Table" << endl;
        return false;
    }
}

//Print all user information from database
bool UserLibrary :: printAllUsers() {
    string sql = "SELECT * FROM User;";
    cout << sql << endl;
    
    if (db.exeSQL(sql)) {
        return true;
    }
    else {
        cout << "Failed to display user" << endl;
        return false;
    }
}

//Store the user information into database
bool UserLibrary :: createUserInDB(User user) {
    string username = user.getUsername();
    string deviceID = user.getDeviceID();
	string hash = user.getHash();
	string salt = user.getSalt();
	json report = user.getReport();
	int syncTime = user.getSyncTime();
	int reportTime = user.getReportTime();

	stringstream ss;
	ss <<  "INSERT INTO User VALUES ('" << username << "','" << deviceID <<
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

//Delete user information from database
bool UserLibrary :: deleteUserFromDB(User user) {
	
	stringstream ss; 
	ss << "DELETE FROM User WHERE deviceID = '" << user.getDeviceID() <<
    "' AND username = '" << user.getUsername() << "';";
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

//Delete user information from database, based on username and deviceID to search
bool UserLibrary :: deleteUserFromDB(string username, string deviceID) {
    
    stringstream ss;
    ss << "DELETE FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
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

//Get user object from database based on username and deviceID
User UserLibrary::retrieveUser(std::string username, std::string deviceID) {
    
    stringstream ss;
    
    ss << "SELECT * FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    string sql = ss.str();
    
    string result = db.getSQLResult(sql);
    
    //Check if user exists
    if (result.length() < 3){
        cout << "Cannot find user" << endl;
    }
    else
    {
        cout << result << endl;
    }
    
    ss.str("");
    ss << "SELECT salt FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    sql = ss.str();
    string salt = db.getSQLResult(sql);
    
    ss.str("");
    ss << "SELECT report FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    sql = ss.str();
    json report;
    ss.str("");
    ss << db.getSQLResult(sql);
    ss >> report;
     
    
    ss.str("");
    ss << "SELECT syncTime FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    sql = ss.str();
    long syncTime = atol(db.getSQLResult(sql).c_str());
    
    ss.str("");
    ss << "SELECT reportTime FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    sql = ss.str();
    long reportTime = atol(db.getSQLResult(sql).c_str());
    
    User user(username,deviceID);
    user.setSalt(salt);
    user.setReport(report);
    user.setSyncTime(syncTime);
    user.setReportTime(reportTime);
    
    return user;
}

//Get the hash value user's input password and stored salt, and compare it with the stored hash, return true if matches
bool UserLibrary :: compareUserHash(std::string username, std::string deviceID, std::string password) {

    stringstream ss;
    
    ss << "SELECT * FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    string sql = ss.str();
    
    string result = db.getSQLResult(sql);
    
    //Check if user exists
    if (result.length() < 3){
        cout << "Cannot find user" << endl;
    }
    
    ss.str("");
    ss << "SELECT salt FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    sql = ss.str();
    string salt = db.getSQLResult(sql);
    
    ss.str("");
    ss << "password" << "Test_Salt01";
    
    //convert hash value from size_t to string
    string saltedPwd = ss.str();
    saltedPwd.erase(remove(saltedPwd.begin(), saltedPwd.end(), '\n'), saltedPwd.end()); // cout << saltedPwd << endl;
    saltedPwd.erase(remove(saltedPwd.begin(), saltedPwd.end(), '\n'), saltedPwd.end());
    hash<string> h;
    ss.str("");
    ss << h(saltedPwd);
    string hashToCompare = ss.str();
    //cout << hashToCompare << endl;
    
    ss.str("");
    ss << "SELECT hash FROM User WHERE deviceID = '" << deviceID <<
    "' AND username = '" << username << "';";
    sql = ss.str();
    string hash = db.getSQLResult(sql);
    
    cout << hash << hashToCompare << endl;
    
    cout << hash.compare(hashToCompare) << endl;
    
    if (hash.compare(hashToCompare))
        return false;
    else
        return true;
}

//Update user's last synchronization time
bool UserLibrary :: updateUserSyncTime(User user, int syncTime) {

	stringstream ss;
	ss << "UPDATE User SET syncTime = " << syncTime <<
		" WHERE deviceID = '" << user.getDeviceID() <<
    "' AND username = '" + user.getUsername() + "';";

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

//Update the user's report content
bool UserLibrary :: updateReport(User user, json report) {
	stringstream ss;
	ss << "UPDATE User SET report = '" << report <<
    "' WHERE deviceID = '" << user.getDeviceID() <<
    "' AND username = '" << user.getUsername() << "';";
    
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
