#include "googleAPI.h"
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {

   int example = 0;


    googleAPI g("43.0094907", "-81.2702514");
    vector<string> container = g.getTypesArray(example);

    //this returns a string


    cout << "Formatted Location: " << g.getFormattedLocation() << endl;

    cout << "Name: " << g.getName() << endl;

    cout << "Latitude: " << g.getLat() << endl;

    cout << "Longitude: " << g.getLng() << endl;

    cout << "North East Latitude: " << g.getNorthEastLat() << endl;

    cout << "North East Longitude: " << g.getNorthEastLng() << endl;

    cout << "South West Latitude: " << g.getSouthWestLat() << endl;

    cout << "South West Longitude: " << g.getSouthWestLng() << endl;

    cout << "Types: " << g.getTypes(example) << endl;

    if(g.checkTypes(example)){
        cout << "TRUE" << endl;
    }else {
        cout << "FALSE" << endl;
    }

    cout << "Valid place: " << g.getValidPlace() << endl;



	return 0;
}

