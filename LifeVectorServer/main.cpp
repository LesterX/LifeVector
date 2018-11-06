/*#include <nlohmann/json.hpp> //"https://github.com/nlohmann/json"
*/
#include<iostream>
#include "Database.h"
using namespace std;

int main()
{
	Database db;
	//Hostname, Username, Password, Database name
	db.initDB("localhost", "root", "623062", "LifeVector");
	db.exeSQL("INSERT INTO User VALUES ('02','Arthur Morgan');");
	db.exeSQL("SELECT * FROM User;");
	return 0;
}