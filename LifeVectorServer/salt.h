/**
 * header file for salt class
 */
#ifndef SALT_H
#define SALT_H

#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <stdlib.h> 
#include <sys/random.h>

class salt  {
 
	public:
		
		void saltUser(std::string user_name);
		std::size_t getSalt();
		std::size_t getHash();
		std::string getUserName();


	private:

		std::size_t *salt;
		std::size_t hash;
		std::string user_name;

};

#endif