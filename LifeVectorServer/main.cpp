#include <iostream>
#include "UserLibrary.h"
using namespace std;
using json = nlohmann::json;

int main()
{
    
	json j1 = {
		{"key1_1","value1_1"},
		{"key1_2","value1_2"}
	};

	User u1("user1","01", "Test_Hash01", "Test_Salt01", j1, 1001, 1002);

	UserLibrary userlib;
	
    //userlib.createUserInDB(u1);
    //userlib.printAllUsers();
    //userlib.deleteUserFromDB("user1","01");
    //userlib.printAllUsers();
    
    User user = userlib.retrieveUser("user1","01");
    cout << user.getUsername() << "  " << user.getDeviceID() <<
    "  " << user.getHash() << "  " << user.getSalt() << endl <<
    user.getReport() << endl << user.getSyncTime() << "  " <<
    user.getReportTime() << endl;
     
    //userlib.updateUserSyncTime(u1,2000);
    
    /*
    json j2 = {
        {"key1_1","updated value 1"},
        {"key1_2","updated value 2"}
    };
    userlib.updateReport(u1,j2);
    */
    
	return 0;
}
