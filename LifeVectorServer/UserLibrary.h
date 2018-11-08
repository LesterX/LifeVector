#ifndef USERLIBRARY_H
#define USERLIBRARY_H

#include "user.h"
#include "Database.h"
#include "json.hpp"
#include <mysql/mysql.h> //https://dev.mysql.com/downloads/connector/c/

class UserLibrary{

public:

	UserLibrary();
    bool createUserTable();
    bool printAllUsers();
	bool createUserInDB(User user);
	bool deleteUserFromDB(User user);
    bool deleteUserFromDB(string username,string deviceID); //Overload
    User retrieveUser(std::string username, std::string devID);
	bool compareUserHash(std::string devID);
	bool updateUserSyncTime(User user, int syncTime);
	bool updateReport(User user, nlohmann::json report); 

private:

	Database db;

};

#endif
