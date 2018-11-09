/**
 * header file for UserController class
 */
#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <stdlib.h>

#include "UserLibrary.h"
#include "user.h"
#include "hashfunc.h"

#include "json.hpp"
using json = nlohmann::json;

class UserController
{
public:
  // Constructors
  UserController(std::string dbUsername, std::string dbPassword);

  // Destructor
  ~UserController();

  // User Controls
  bool createUser(std::string username, std::string devID, std::string password);
  bool retrieveUser(User *target, std::string username, std::string devID);
  bool deleteUser(std::string username, std::string devID);

  // Update User Information
  bool updateReport(string username, string deviceID, json newReport);
  bool fetchReport(json* dbReport, string username, string deviceID);

private:
  UserLibrary userLibrary;

  // Comparator
  bool compareUserHash(std::string username, std::string devID, std::string password);
};

#endif
