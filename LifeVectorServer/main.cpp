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

	User u1("01", "Test_Hash01", "Test_Salt01", j1, 1001, 1002);

	UserLibrary userlib;
	userlib.createUserInDB(u1);
	return 0;
}