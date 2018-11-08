
#include "UserController.h"

using namespace std;


bool UserController :: createUser(string username, string devID, string password){

	compareUserHash(username, devID, password);

	

	//if exists then exit

	//else create the user

	User user = User(username, devID);

	createUserInDB(user);

}
bool UserController :: deleteUser(std::string devID){

	deleteUserFromDB(string username, string deviceID);

}
bool UserController :: synchronizeUser(std::spec, json data){

}
json UserController :: retrieveUser(std::string devID){

}