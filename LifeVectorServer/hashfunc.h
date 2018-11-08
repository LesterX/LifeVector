/**
 * header file for salt class
 */
#ifndef HASHFUNC_H
#define HASHFUNC_H

#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <stdlib.h> 
#include <linux/random.h>

#include "CkCrypt2.h"

class hashfunc  {
 
	public:
		
		void hashUser(std::string password);
        std::string getSalt();
        std::string getHash();
		//need to implement
        std::string getHash(std::string password, std::string salt);


	private:

        std::string salt;
        std::string hash;
		std::string password;

};

#endif
