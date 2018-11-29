/**
 * @file squasher.cpp
 * @brief Squasher to process raw data
 * 
 * Used for processing raw data from front end, which recording
 * the time stamps, latitude, and longitude. Adding unfound location 
 * into archived library and squash continuous points at same 
 * location together
 */

#include "squasher.h" 
#include <vector>
#include <sstream>
#include "CoordinateInformation.h"
#include "ArchivedLocation.h"
#include "googleAPI.h"
#include "UserVisitInfo.h"

/**
 * @brief Squash unprocessed data
 * 
 * Recoding the time spent in each location
 * Save the result into ArchiveLibrary
 */
void squasher::squash() {
	cout << "Last Location ID: " << currentID - 1 << endl;
	std::vector<long> timeStamps = rawData.getTimeStamps();
	std::map<long, int> log;
	std::vector<long>::iterator itr = timeStamps.begin();
	UserVisitInfo uvi;

	//Loop through all the data points
	for (itr; itr != timeStamps.end(); ++itr) {
		double *coord = (double*) malloc(sizeof(double) * 2);

		rawData.getCoordinates(coord, *itr);
		double lat = *coord;
		double lng = *(coord + 1);

		//Search the location in the library based on coordinates, get 0 if not found
		std::map<int, CoordinateInformation> matchedLocations = std::map<int, CoordinateInformation>();
		int locationID = library.matchNearestLocation(matchedLocations,lat,lng);
		if (locationID > 0){
			//Location is found in library
			//Push it into map for later squashing
			log.emplace(*itr,locationID);
		}
		else {
			//Location is not in library
			//Search location from Google Map and Google Place API
			locationID = currentID;
			cout << "Input ID : " << locationID << endl;
			std::ostringstream lat_str, lng_str; // Converting from double to string
			lat_str << lat;
			lng_str << lng;
			googleAPI gAPI(lat_str.str(), lng_str.str());

			//Setting up the location information
			int id = currentID;
			std::string name = gAPI.getName();
			std::string address = gAPI.getFormattedLocation();
			std::string description = gAPI.getTypes(0);
			double eastbound = std::stod(gAPI.getNorthEastLng());
			double northbound = std::stod(gAPI.getNorthEastLat());
			double westbound = std::stod(gAPI.getSouthWestLng());
			double southbound = std::stod(gAPI.getSouthWestLat());

			//Build the ArchiveLocation object and save it into library
			ArchivedLocation location = library.constructLocation(id,name,address,description,lat,lng,
			northbound,southbound,eastbound,westbound);
			library.saveLocationToDatabase(location);

			//Push into map for later squashing
			log.emplace(*itr, locationID);
			incrementID();
		}

		//Free assigned memory to pointer
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
			if ((itr + 1) == timeStamps.end()) //If there's only one point, just push it
				uvi.addSingleLog(*itr, 0);
		}
		else {
			//If found a different location, 
			//add the last location to the user visit info
			if (locID != lastID) {
				timeSpent = timeSpent + (*itr - *(itr - 1));
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

			//If it's the last location, also add it to the user visit info
			if ((itr + 1) == timeStamps.end()) {
				cout << "LocationID: " << locID << ", Time Spent: " << (int)timeSpent << endl;
				uvi.addSingleLog(lastTime, (int)timeSpent);
				timeSpent = 0;
			}
		}
	}

	//Raw data is now squashed into the user visit info object
	uvi.printLog();
}