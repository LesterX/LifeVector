
/* Class used for processing raw data from front end, which recording
 * the time stamps, latitude, and longitude. Adding unfound location 
 * into archived library and squash continuous points with same 
 * location together
*/

#ifndef SQUASHER_H
#define SQUASHER_H

#include "RawDataRepository.h"
//#include "./ArchiveClasses/ArchiveLibrary.h"
#include "Database.h"


class squasher{

private:

	static int currentID;
	RawDataRepository rawData;
	//ArchiveLibrary library;

	/* Struct place class only for testing purpose
	 * Using this instead of the archive library class
	 */
	struct TestPlace {
		int id;
		double eastbound;
		double westbound;
		double southbound;
		double northbound;

		TestPlace(int num, double e, double w, double s, double n) {
			id = num;
			eastbound = e;
			westbound = w;
			southbound = s;
			northbound = n;
		}

		bool inside(double lat, double lng) {
			if (lat < northbound && lat > southbound &&
				lng < eastbound && lng > westbound)
				return true;
			else return false;
		}
	};

	/* Helping method to determine if a point is inside a place */
	bool insidePlace(double lat, double lng, TestPlace place) {
		return place.inside(lat, lng);
	}


public:

	/* Constructor
	 * @param data: Raw data of unprocessed data points
	 * @param db_pointer: Pointer to the archived library
	 */
	/*
	squasher(RawDataRepository data, Database *db_pointer) {
		rawData = data;
		library = new ArchiveLibrary(db_pointer);
	}
	*/
	/* Constructor
	 * Helping constructor used only for testing purpose
	 * Removing the use of archive library
	 */
	squasher(RawDataRepository data) {
		rawData = data;
	}

	/* Void method used to squash the unprocessed data */
	//void squash();
	
	/* Void method used to test squash function without 
	 * the use of archive library
	 */
	void squashForTest();

	/* Increment the static id variable */
	void incrementID();
};

#endif
