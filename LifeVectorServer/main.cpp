#include "googleAPI.h"
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {

    googleAPI g("43.0094907", "-81.2702514",201811271411);

    //this returns a string


    cout << "Formatted Location: " << g.getFormattedLocation() << endl;

    cout << "Name: " << g.getName() << endl;

    cout << "North East Latitude: " << g.getNorthEastLat() << endl;

    cout << "North East Longitude: " << g.getNorthEastLng() << endl;

    cout << "South West Latitude: " << g.getSouthWestLat() << endl;

    cout << "South West Longitude: " << g.getSouthWestLng() << endl;

    cout << "Types: " << g.getTypes() << endl;

	return 0;
}

