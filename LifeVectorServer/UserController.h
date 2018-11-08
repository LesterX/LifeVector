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


class UserController  {
 
	public:
		
		bool createUser(std:: username, std::string devID, int password);
        bool deleteUser(std::string devID);
        bool synchronizeUser(std::spec, json data);
        json retrieveUser(std::string devID);
       
		
	private:

        UserLibrary userlibrary;

};

#endif
