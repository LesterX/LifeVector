#include "squasher.h"
#include <vector>
#include "./ArchiveClasses/CoordinateInformation.h"
#include "./ArchiveClasses/ArchivedLocation.h"
#include "googleAPI.h"

/* Squash raw data from RawDataRespository
 * Check if in the library first
 * if not, add it into the libarary
*/
void squasher::squash() {
	std::vector<long> timeStamps = rawData.getTimeStamps();
	std::map<long,int> log;
	std::std::vector<long>::iterator itr = timeStamps.begin();

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
			log.emplace(*itr,locationID);
		}
	}

	
}