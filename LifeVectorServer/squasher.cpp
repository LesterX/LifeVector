#include "squasher.h" 
#include <vector>
#include <sstream>
#include "CoordinateInformation.h"
#include "ArchivedLocation.h"
#include "googleAPI.h"
#include "UserVisitInfo.h"

/* Initializing auto-increment location id */
int squasher::currentID = 0;


/* Void method used to squash the unprocessed data
 * Squash raw data from RawDataRespository
 * Check if in the library first
 * if not, add it into the libarary
 */

void squasher::squash() {
	std::vector<long> timeStamps = rawData.getTimeStamps();
	std::map<long, int> log;
	std::vector<long>::iterator itr = timeStamps.begin();
	UserVisitInfo uvi;

	for (itr; itr != timeStamps.end(); ++itr) {
		double *coord = (double*) malloc(sizeof(double) * 2);

		rawData.getCoordinates(coord, *itr);
		double lat = *coord;
		double lng = *(coord + 1);

		cout << lat << "  " << lng << endl;

		//Search nearest location in the library, get 0 if not found
		std::map<int, CoordinateInformation> matchedLocations = std::map<int, CoordinateInformation>();
		int locationID = library.matchNearestLocation(matchedLocations,lat,lng);
		if (locationID != 0){
			cout << "Used Location" << endl;
			log.emplace(*itr,locationID);
		}
		else {
			cout << "New Location Found" << endl;
			//Build googleAPI object
			locationID = currentID;
			cout << "Input ID : " << locationID << endl;
			std::ostringstream lat_str, lng_str; // Converting from double to string
			lat_str << lat;
			lng_str << lng;
			googleAPI gAPI(lat_str.str(), lng_str.str());
			int id = currentID;
			std::string name = gAPI.getName();
			std::string address = gAPI.getFormattedLocation();
			std::string description = gAPI.getTypes(0);
			double eastbound = std::stod(gAPI.getNorthEastLng());
			double northbound = std::stod(gAPI.getNorthEastLat());
			double westbound = std::stod(gAPI.getSouthWestLng());
			double southbound = std::stod(gAPI.getSouthWestLat());

			ArchivedLocation location = library.constructLocation(id,name,address,description,lat,lng,
			northbound,southbound,eastbound,westbound);
			library.saveLocationToDatabase(location);

			log.emplace(*itr, locationID);
			incrementID();
		}

		free(coord);
	}

	//Another loop to squash the points
	double lastTime = 0;
	double timeSpent = 0;
	int lastID = 0;
	itr = timeStamps.begin();
	for (itr; itr != timeStamps.end(); ++itr) {
		int locID = log[*itr];
		//Setting up for the first location
		if (itr == timeStamps.begin()) {
			lastTime = *itr;
			lastID = locID;
		}
		else {
			//If found a different location, 
			//add the last location to the user visit info
			if (locID != lastID) {
				cout << "LocationID: " << lastID << ", Time Spent: " << timeSpent << endl;
				uvi.addSingleLog(lastTime, (int)timeSpent);
				lastTime = *itr;
				lastID = locID;
				timeSpent = 0;
			}
			else {
				//If found a same location, increment spent time and update lastTime
				timeSpent = timeSpent + (*itr - lastTime);
				lastTime = *itr;
			}
		}

		//If it's the last location, also add it to the user visit info
		if ((itr+1) == timeStamps.end()){
			cout << "LocationID: " << locID <<  ", Time Spent: " << (int) timeSpent << endl;
				uvi.addSingleLog(lastTime, (int) timeSpent);
				timeSpent = 0;
		}
	}
	//Raw data is now squashed into the user visit info object
	cout << "----User Visit Info Log----" << endl;
	uvi.printLog();
}

/* Void method used to test squash function without
 * the use of archive library
 */
void squasher::squashForTest() {
	std::vector<long> timeStamps = rawData.getTimeStamps();
	std::map<long, int> log;
	std::vector<long>::iterator itr = timeStamps.begin();
	UserVisitInfo uvi;

	std::vector<TestPlace> places;

	for (itr; itr != timeStamps.end(); ++itr) {
		double *coord;
		rawData.getCoordinates(coord, *itr);

		int locationID = currentID;
		cout << locationID << endl;

		//Build googleAPI object
		double lat = *coord;
		double lng = *(coord + 1);
		std::ostringstream lat_str, lng_str; // Converting from double to string
		lat_str << lat;
		lng_str << lng;
		googleAPI gAPI(lat_str.str(), lng_str.str());
		int id = currentID;
		std::string name = gAPI.getName();
		std::string address = gAPI.getFormattedLocation();
		std::string description = gAPI.getTypes(0);
		double eastbound = std::stod(gAPI.getNorthEastLng());
		double northbound = std::stod(gAPI.getNorthEastLat());
		double westbound = std::stod(gAPI.getSouthWestLng());
		double southbound = std::stod(gAPI.getSouthWestLat());

		bool duplicate = false;
		for (int i = 0; i < places.size(); i++) {
			TestPlace p = places[i];
			if (p.inside(lat, lng)) {
				duplicate = true;
				id = p.id;
				break;
			}
		}
		TestPlace place(id, eastbound, westbound, southbound, northbound);
		if (!duplicate || itr == timeStamps.begin()){
			ArchivedLocation location = library.constructLocation(id,name,address,description,lat,lng,
			northbound,southbound,eastbound,westbound);
			incrementID();
		}

		places.push_back(place);
		cout << "aaa" << endl;

		log.emplace(*itr, locationID);	
	}

	//Another loop to squash the points
	double lastTime = 0;
	double timeSpent = 0;
	int lastID = 0;
	itr = timeStamps.begin();
	for (itr; itr != timeStamps.end(); ++itr) {
		int locID = log[*itr];
		//Setting up for the first location
		if (itr == timeStamps.begin()) {
			lastTime = *itr;
			lastID = locID;
		}
		else {
			//If found a different location, 
			//add the last location to the user visit info
			if (locID != lastID) {
				cout << "LocationID: " << lastID << ", Time Spent: " << timeSpent << endl;
				uvi.addSingleLog(lastTime, (int)timeSpent);
				lastTime = *itr;
				lastID = locID;
				timeSpent = 0;
			}
			else {
				//If found a same location, increment spent time and update lastTime
				timeSpent = timeSpent + (*itr - lastTime);
				lastTime = *itr;
			}
		}

		//If it's the last location, also add it to the user visit info
		if ((itr+1) == timeStamps.end()){
			cout << "LocationID: " << locID <<  ", Time Spent: " << (int) timeSpent << endl;
				uvi.addSingleLog(lastTime, (int) timeSpent);
				timeSpent = 0;
		}
	}
	//Raw data is now squashed into the user visit info object
	cout << "----User Visit Info Log----" << endl;
	uvi.printLog();
}

/* Used for incrementing the id for locations */
void squasher::incrementID() {
	currentID++;
}