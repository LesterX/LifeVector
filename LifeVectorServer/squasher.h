/**
 * @file squasher.h
 * @brief Squasher to process raw data
 * 
 * Used for processing raw data from front end, which recording
 * the time stamps, latitude, and longitude. Adding unfound location 
 * into archived library and squash continuous points at same 
 * location together
 */

#ifndef SQUASHER_H
#define SQUASHER_H

#include "RawDataRepository.h"
#include "ArchiveLibrary.h"
#include "Database.h"


class squasher{

private:

	int currentID;
	RawDataRepository rawData;
	ArchiveLibrary library;

	/**
	 * @brief Increment static ID
	 */
	void incrementID() {
		currentID++;
	}

public:

	/**
	 * @brief Construct a new squasher object
	 * 
	 * @param data 
	 * @param db_pointer 
	 * 
	 */
	squasher(RawDataRepository data, Database *db_pointer) : library(db_pointer){
		rawData = data;	
		currentID = library.getLastLocationID() + 1;
	}

	/**
	 * @brief Squash unprocessed data
	 * 
	 * Recoding the time spent in each location
	 * Save the result into ArchiveLibrary
	 */
	void squash();
};

#endif
