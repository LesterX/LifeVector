#include "googleAPI.h"
#include "squasher.h"
#include <iomanip>
#include "RawDataRepository.h"

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
	RawDataRepository rdr;
	//rdr.addTestData(2100, 43.027977, -81.279781);
	//rdr.addTestData(2110, 43.026073, -81.278351);
	rdr.addTestData(2120, 43.024957, -81.279056);
	rdr.addTestData(2130, 43.024958, -81.279057);
	rdr.addTestData(2140, 43.024956, -81.279055);
	rdr.addTestData(2150, 43.024958, -81.279057);
	//rdr.addTestData(2140, 43.025259, -81.278031);
	//rdr.addTestData(2150, 43.023145, -81.281424);
	//rdr.addTestData(2200, 43.021007, -81.278847);
	//rdr.addTestData(2210, 43.021006, -81.278846);
	//rdr.addTestData(2220, 43.100000, -81.300000);
	//rdr.addTestData(2230, 43.100000, -81.300000);
	//rdr.addTestData(2240, 43.200000, -81.100000);

	squasher sq(rdr);
	sq.squashForTest();

	return 0;
}

