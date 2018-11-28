#ifndef SQUASHER_H
#define SQUASHER_H

#include "RawDataRepository.h"
#include "./ArchiveClasses/ArchiveLibrary.h"
#include "Database.h"
#include "googleAPI.h"


class squasher{

private:

	RawDataRepository rawData;
	ArchiveLibrary library;


public:

	squasher(RawDataRepository data, Database *db_pointer) {
		rawData = data;
		library = new ArchiveLibrary(db_pointer);
	}

	void squash();
	
}

#endif
