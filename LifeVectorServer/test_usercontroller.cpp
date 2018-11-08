#include "UserController.h"



int main(){

	string username = "John Smith";
	string devID = "nexus5";
	int password = "1234";

	UserController uc;

	if(uc.createUser(username, devID, password)){
		printf("User %s created", username);
	}
	else{
		printf("Unable to create user %s", username);
	}


	return 0;
}