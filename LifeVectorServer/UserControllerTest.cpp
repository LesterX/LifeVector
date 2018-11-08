#include "UserController.h"
#include "json.hpp"


int main(){

	string username = "John Smith";
	string devID = "nexus5";
	string password = "1234";
    nlohmann::json report = {
        {"key1_1","value1_1"},
        {"key1_2","value1_2"}
    };
    
	UserController uc("root","623062");

	if(uc.createUser(username, devID, password)){
		printf("User %s created", username);
	}
	else{
		printf("Unable to create user %s", username);
	}

    if(uc.deleteUser(username, devID)){
        printf("User %s deleted", username);
    }
    else{
        printf("Unable to delete user %s", username);
    }
    
    if (uc.updateReport(username,devID,report)){
        cout << "Report updated for " << username << endl;
    }
    
    nlohmann::json reportFromDB = uc.fetchReport(username,devID);
    if (reportFromDB != NULL){
        cout << reportFromDB << endl;
    }
    
    

	return 0;
}
