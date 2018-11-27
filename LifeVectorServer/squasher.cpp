#include "squasher.h" 
#include <vector>
#include "./ArchiveClasses/CoordinateInformation.h"
#include "./ArchiveClasses/ArchivedLocation.h"
#include "googleAPI.h"
#include "UserVisitInfo.h"

/* Squash raw data from RawDataRespository
 * Check if in the library first
 * if not, add it into the libarary
*/
void squasher::squash() {
	std::vector<long> timeStamps = rawData.getTimeStamps();
	std::map<long,int> log;
	std::std::vector<long>::iterator itr = timeStamps.begin();
	UserVisitInfo uvi();

	for (itr; itr != timeStamps.end(); ++itr) {
		double *coord;
		rawData.getCoordinates(coord,*itr);

		std::map<int, CoordinateInformation> *matchedLocations;
		int locationID = library.matchNearestLocation(matchedLocations,*coord,*(coord+1));

		//If id = 0, location is not found in library
		//Otherwise, it is a new location which need to be searched in Google API
		if (locationID != 0) {
			log.emplace(*itr,locationID);
		}else{
			//Build googleAPI object
			double lat = *coord;
			double lng = *(corrd+1);
			googleAPI gAPI(lat,lng);
			int id = gAPI.getID();
			std::string name = gAPI.getName();
			std::string address = gAPI.getFormattedLocation();
			std::string description = gAPI.getTypes();
			double eastbound = atof(gAPI.getNorthEastLat);
			double northbound = atof(gAPI.getNorthEastLng);
			double westbound = atof(gAPI.getSouthWestLat);
			double southbound = atof(gAPI.getSouthWestLng);

			//Create new archived location
			ArchivedLocation al = constructLocation(id,address,description,
			lat,lng,northbound,southbound,eastbound,westbound);
			library.saveLocationToDatabase(al);
			log.emplace(*itr,locationID);
		}
	}

	//Another loop to squash the points
	double lastTime = 0;
	double timeSpent = 0;
	int lastID = 0;
	itr = timeStamps.begin();
	for (itr; itr != timeStamps.end(); ++itr) {
		int locID = log.find(*itr);
		//Setting up for the first location
		if (itr == timeStamps.begin()) {
			lastTime = *itr;
			lastID = locID;
		}else {
			//If found a different location, add it to the user visit location
			if (locID != lastID) {
				uvi.addSingleLog(lastTime, (int) timeSpent);
				lastTime = *itr;
				lastID = locID;
				timeSpent = 0;
			}else {
				//If found a same location, increment spent time and update lastTime
				timeSpent = timeSpent + (*itr - lastTime);
				lastTime = *itr;
			}
		}
	}

	//Raw data is now squashed into the user visit info object
	uvi.printLog();
}