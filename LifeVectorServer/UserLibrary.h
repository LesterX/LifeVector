#ifndef USERLIBRARY_H
#define USERLIBRARY_H

#include "user.h"
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
	bool updateUserSyncTime(int syncTime);
	bool updateReport(nlohmann::json report); 

private:
	MYSQL *connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
};

#endif
