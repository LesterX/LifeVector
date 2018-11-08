
#include "UserController.h"

using namespace std;


bool UserController :: createUser(string username, string devID, string password){

	if(!isPresent(devID)){

		printf("User alread exists");
		exit(0);
	}

	User user = User(username, devID);

	if(!createUserInDB(user)){
		printf("Unable to create user");
		exit(0);
	}

	return true;

}
bool UserController :: deleteUser(std::string devID){

	deleteUserFromDB(string username, string deviceID);

}
bool UserController :: synchronizeUser(std::spec, json data){

}
json UserController :: retrieveUser(std::string devID){

}