#ifndef USERLIBRARY_H
#define USERLIBRARY_H

#include <mysql/mysql.h> //https://dev.mysql.com/downloads/connector/c/
#include "json.hpp"

#include "Database.h"
#include "user.h"
#include "DataDepositor.h"

class UserLibrary
{

  public:
	// Constructor
	UserLibrary(std::string userName, std::string password); //userName and Password are for logging into and connecting with SQL server

	// Creater
	bool createUserInDB(User user);

	// Removers
	bool deleteUserFromDB(string username, string deviceID);

	// Getters
	User retrieveUserFromDB(std::string username, std::string deviceID);

	// Updater & Uploaders
	bool updateUserSyncTime(User user, int syncTime);
	bool updateReport(User user, nlohmann::json report);
	bool uploadRawGPSData(std::string deviceID, RawDataRepository rawDataSet);

	// Helpers
	bool isRegistered(std::string username, std::string deviceID);
	
	// Printer
	bool printAllUsers();

  private:
	Database db;

	// Helpers
	bool isPresent(std::string deviceID);
};

#endif
