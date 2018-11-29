/**
 * @file TestSquash.cpp
 * 
 * @brief Testing class for squasher
 * 
 * Mannually input raw data repository into squasher
 * Connecting to Archive Library
 */

#include "../googleAPI.h"
#include "../squasher.h"
#include <iomanip>
#include "../RawDataRepository.h"
#include "../Database.h"
#include "../UserController.h"

using namespace std;

int main(int argc, char** argv) {

	//Create user in database for testing
	//UserController uc("server","LifeVector123");
	//uc.createUser("Yimin","01","LifeVector123");

	//Create database object and Raw data repository	
	Database db;
	db.initDB("localhost","server","LifeVector123","LifeVector");
	RawDataRepository rdr;

	//Adding coordinates data into raw data reporsitory
	rdr.addTestData(1543500000, 43.005874, -81.274616);
	rdr.addTestData(1543501800, 43.008604, -81.275284);
	rdr.addTestData(1543503600, 43.008604, -81.275284);
	rdr.addTestData(1543505400, 43.008792, -81.276411);
	rdr.addTestData(1543507200, 43.009768, -81.270752);

	//Create squasher
	squasher sq(rdr, &db,"Yimin","01");
	sq.squash();

	return 0;
}

