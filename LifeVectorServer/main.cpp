#include "googleAPI.h"
#include "placesAPI.h"
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {

   int example = 0;


    googleAPI g("43.009517", "-81.270260");

    //this returns a string


    cout << "Formatted Location: " << g.getFormattedLocation() << endl;

    cout << "Place name: " << g.getName() << endl;

    cout << "Latitude: " << g.getLat() << endl;

    cout << "Longitude: " << g.getLng() << endl;

    cout << "North East Latitude: " << g.getNorthEastLat() << endl;

    cout << "North East Longitude: " << g.getNorthEastLng() << endl;

    cout << "South West Latitude: " << g.getSouthWestLat() << endl;

    cout << "South West Longitude: " << g.getSouthWestLng() << endl;

    cout << "Types: " << g.getTypes(0) << endl;


	return 0;
}

