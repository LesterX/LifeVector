#include <iostream>
#include <sstream>
#include <algorithm>
#include "UserLibrary.h"
using namespace std;
using json = nlohmann::json;

int main()
{
    
	json j1 = {
		{"key1_1","value1_1"},
		{"key1_2","value1_2"}
	};
    
    stringstream ss;
    ss << "password" << "Test_Salt01";
    string saltedPwd = ss.str();
    //Remove new line and space 
    saltedPwd.erase(remove(saltedPwd.begin(), saltedPwd.end(), '\n'), saltedPwd.end());
    saltedPwd.erase(remove(saltedPwd.begin(), saltedPwd.end(), ' '), saltedPwd.end());
    hash<string> h;
    ss.str("");
    ss << h(saltedPwd);
    string hash1 = ss.str();
    
    //cout << saltedPwd << endl << hash1 << endl;

	User u1("user1","01", hash1, "Test_Salt01", j1, 1001, 1002);

	UserLibrary userlib;
    
	//userlib.deleteUserFromDB("user1","01");
    //userlib.createUserInDB(u1);
    //userlib.printAllUsers();
    //userlib.printAllUsers();
    
    /*
    User user = userlib.retrieveUser("user1","01");
    cout << user.getUsername() << "  " << user.getDeviceID() <<
    "  " << user.getHash() << "  " << user.getSalt() << endl <<
    user.getReport() << endl << user.getSyncTime() << "  " <<
    user.getReportTime() << endl;
     */
    
    //userlib.updateUserSyncTime(u1,2000);
    
    /*
    json j2 = {
        {"key1_1","updated value 1"},
        {"key1_2","updated value 2"}
    };
    userlib.updateReport(u1,j2);
    */
    
    cout << userlib.compareUserHash("user1","01","password") << endl;
    
	return 0;
}
