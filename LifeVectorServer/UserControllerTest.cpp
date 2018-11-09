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
        cout << "User " << username << "created";
	}
	else{
        cout << "Unable to create user" << username << endl;
	}

    if(uc.deleteUser(username, devID)){
        cout << "User " << username << " deleted" << endl;
    }
    else{
        cout << "Unable to delete user " << username << endl;
    }
    
    if (uc.updateReport(username,devID,report)){
        cout << "Report updated for " << username << endl;
    }
    
    nlohmann::json *reportFromDB;
    ;
    if (uc.fetchReport(reportFromDB,username,devID)){
        cout << "Report: " << endl << *reportFromDB << endl;
    }
    
    if (uc.compareUserHash(username,devID,password)){
        cout << "Hash matched" << endl;
    }else
        cout << "Hash not matched" << endl;
    

	return 0;
}
