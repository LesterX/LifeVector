/*
 g++ Database.cpp user.cpp UserLibrary.cpp DataDepositor.cpp RawDataRepository.cpp UserLibraryTest.cpp -lmysqlclient -o LibraryTest
*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include "UserLibrary.h"
using namespace std;
using json = nlohmann::json;

int main()
{
    //Connecting to database
    UserLibrary userlib = UserLibrary("pi","pw123");  //Change username and password to your own mysql database info
    
    //Data creating
    //User 1 information
	json j1 = {
		{"key1_1","value1_1"},
		{"key1_2","value1_2"}
	};
	User u1("user1","01", "aaaaa", "Test_Salt01", j1, 1001, 1002);

	
    userlib.deleteUserFromDB("user1","01");
    userlib.createUserInDB(u1);
    
    User user = userlib.retrieveUserFromDB("user1","01");
    cout << user.getUsername() << "  " << user.getDeviceID() <<
    "  " << user.getHash() << "  " << user.getSalt() << endl <<
    user.getReport() << endl << user.getSyncTime() << "  " <<
    user.getReportTime() << endl;
    
    
    userlib.updateUserSyncTime(u1,2000);
    
    
    json j2 = {
        {"key1_1","updated value 1"},
        {"key1_2","updated value 2"}
    };
    userlib.updateReport(u1,j2);
    
    userlib.printAllUsers();
    
	return 0;
}
