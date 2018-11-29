/**
 * @file TestSquash.cpp
 * 
 * @brief Testing class for squasher
 * 
 * Mannually input raw data repository into squasher
 * Connecting to Archive Library
 */

#include "googleAPI.h"
#include "squasher.h"
#include <iomanip>
#include "RawDataRepository.h"
#include "Database.h"

using namespace std;

int main(int argc, char** argv) {

	/*
    googleAPI g("43.026073", "-81.278351");

    //this returns a string


    cout << "Formatted Location: " << g.getFormattedLocation() << endl;

    cout << "Name: " << g.getName() << endl;

    cout << "North East Latitude: " << g.getNorthEastLat() << endl;

    cout << "North East Longitude: " << g.getNorthEastLng() << endl;

    cout << "South West Latitude: " << g.getSouthWestLat() << endl;

    cout << "South West Longitude: " << g.getSouthWestLng() << endl;

    cout << "Types: " << g.getTypes() << endl;
	*/

	/* Testing for squasher */
	
	Database db;
	db.initDB("localhost","server","LifeVector123","LifeVector");

	
	RawDataRepository rdr;
	rdr.addTestData(1543500000, 43.005874, -81.274616);
	rdr.addTestData(1543501800, 43.008604, -81.275284);
	rdr.addTestData(1543503600, 43.008604, -81.275284);
	rdr.addTestData(1543505400, 43.008792, -81.276411);
	rdr.addTestData(1543507200, 43.009768, -81.270752);

	squasher sq(rdr, &db);
	sq.squash();

	return 0;
}

