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

	/*
	RawDataRepository rdr;
	//rdr.addTestData(1543431701, 43.027977, -81.279781);
	// rdr.addTestData(1543432241, 43.026073, -81.278351);
	// rdr.addTestData(1543432841, 43.024957, -81.279056);
	rdr.addTestData(1543433441, 43.024958, -81.279057);
	rdr.addTestData(1543434041, 43.024958, -81.279057);
	rdr.addTestData(1543434641, 43.025259, -81.278031);
	rdr.addTestData(1543435241, 43.023145, -81.281424);
	rdr.addTestData(1543435841, 43.021007, -81.278847);
	rdr.addTestData(1543436441, 43.021006, -81.278846);
	rdr.addTestData(1543437041, 43.006235, -81.274763);
	rdr.addTestData(1543437641, 43.005756, -81.276297);
	rdr.addTestData(1543438241, 43.001538, -81.255043);
	squasher sq(rdr,&db);
	//sq.squashForTest();
	sq.squash();
	//sq.test();
	*/

	string command = "INSERT INTO Test VALUES(1.123456,1.123456);";

    if (db.exeSQL(command))
    {
		cout << "Success" << endl;
	}


	return 0;
}

