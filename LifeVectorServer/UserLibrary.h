#ifndef USERLIBRARY_H
#define USERLIBRARY_H

#include "user.h"

class UserLibrary{
private:

public:
	UserLibrary();
	bool createUserInDB(User user);
	bool deleteUserFromDB(User user);
	bool retrieveUser(std::string devID);
	bool compareUserHash(std::string devID);
	bool updateUserSyncTime(int syncTime);
	bool updateReport(); //Can't find built-in JSON type
};

#endif
