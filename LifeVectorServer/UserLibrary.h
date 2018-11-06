#ifndef USERLIBRARY_H
#define USERLIBRARY_H

#include "user.h"
#include "Database.h"
#include <nlohmann/json.hpp> //"https://github.com/nlohmann/json"
#include <mysql/mysql.h> //https://dev.mysql.com/downloads/connector/c/

class UserLibrary{

public:

	UserLibrary();
	~UserLibrary();
	bool createUserInDB(User user);
	bool deleteUserFromDB(User user);
	bool retrieveUser(std::string devID);
	bool compareUserHash(std::string devID);
	bool updateUserSyncTime(User user, int syncTime);
	bool updateReport(User user, nlohmann::json report); 

private:

	Database db;

};

#endif
