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
#include <sys/random.h>

#include "CkCrypt2.h"

class hashfunc  {
 
	public:
		
		void hashUser(std::string user_name);
		std::size_t getSalt();
		std::size_t getHash();
		std::string getUserName();


	private:

		std::size_t *salt;
		std::size_t hash;
		std::string user_name;

};

#endif