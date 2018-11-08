#include "UserController.h"

using namespace std;

// Constructor
UserController::UserController(std::string dbUsername, std::string dbPassword)
{
	userLibrary = UserLibrary(dbUsername, dbPassword);
}

// Destructor
UserController::~UserController() {}

/* User Functions */
bool UserController::createUser(string username, string devID, string password)
{
	// Test if User already in database
	if (compareUserHash(username, devID, password))
	{
		//the user is found in database
		cout << "Error: User Creation Failed: User is already registered in Database" << endl;
		return false;
	}

	// hash and salt password
	hashfunc hf;
	hf.hashString(password);
	string hash = hf.getHash();
	string salt = hf.getSalt();

	// create user object
	User newUser = User(username, devID, hash, salt);

	// save user to DB
	return userLibrary.createUserInDB(newUser);
}

User UserController::retrieveUser(std::string username, std::string devID)
{
	return userLibrary.retrieveUserFromDB(username, devID);
}

bool UserController::deleteUser(std::string username, std::string devID)
{
	return userLibrary.deleteUserFromDB(username, devID);
}

/* User Information Editors */
bool UserController::updateReport(string username, string deviceID, json newReport)
{
	User target = retrieveUser(username, deviceID);

	return userLibrary.updateReport(target, newReport);
}

json UserController::fetchReport(string username, string deviceID)
{
	User target = retrieveUser(username, deviceID);

	json dbReport = target.getReport();
	if (dbReport.empty())
	{
		cout << "Error: No reports stored in Database" << endl;
	}

	return dbReport;
}

//Get the hash value user's input password and stored salt, and compare it with the stored hash, return true if matches
bool UserController::compareUserHash(std::string username, std::string deviceID, std::string password)
{
	// fetch user from DB
	User target = retrieveUser(username, deviceID);

	// store hash from DB
	string dbHash = target.getHash();

	// initialize hash function for password parameter
	hashfunc hf;
	string inputHash = hf.getHash(password, target.getSalt());

	// Remove the ******* white space and \n from hash strings
	dbHash.erase(std::remove(dbHash.begin(), dbHash.end(), ' '), dbHash.end());
	dbHash.erase(std::remove(dbHash.begin(), dbHash.end(), '\n'), dbHash.end());

	inputHash.erase(std::remove(inputHash.begin(), inputHash.end(), ' '), inputHash.end());
	inputHash.erase(std::remove(inputHash.begin(), inputHash.end(), '\n'), inputHash.end());

	// Print input hash and database hash - check
	cout << dbHash << endl
		 << inputHash << endl;

	// Compare and return result
	if (dbHash.compare(inputHash) == 0)
		return true;
	else
		return false;
}
