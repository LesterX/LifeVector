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
	UserLibrary(std::string userName, std::string password);

	// Creater
	bool createUserInDB(User user);
    bool createUserInDB(std::string username, std::string devID, std::string password,
                        nlohmann::json report, int syncTime, int reportTime);
    
	bool printAllUsers();

	// Removers
	bool deleteUserFromDB(User user);
	bool deleteUserFromDB(string username, string deviceID); //Overload

	// Getters
	User retrieveUser(std::string username, std::string devID);

	// Comparator
	bool compareUserHash(std::string username, std::string devID, std::string password);

	// Updater & Uploaders
	bool updateUserSyncTime(User user, int syncTime);
	bool updateReport(User user, nlohmann::json report);
	bool uploadRawGPSData(std::string deviceID, RawDataRepository rawDataSet);

	// Helpers
	bool isPresent(std::string deviceID);

  private:
	Database db;

	
};

#endif
