#ifndef ARCHIVE_LIBRARY_H
#define ARCHIVE_LIBRARY_H

#include <map>
#include <set>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>

#include "Database.h"
#include "ArchivedLocation.h"
#include "VisitLog.h"
#include "UserVisitInfo.h"

#include "StringParser.h"

#include "DataDepositor.h"

class ArchiveLibrary
{
  private:
    Database *connected_db;
    static std::set<int> locationIndex;

  public:
    /* Constructor */
    ArchiveLibrary(Database *db_pointer);

    /* Destructor */
    ~ArchiveLibrary();

    /* Location Functions: */
    ArchivedLocation constructLocation(int id, std::string name, std::string address, std::string description, double latitude, double longitude, double northBound, double southBound, double eastBound, double westBound);

    bool getLocationFromDatabase(ArchivedLocation *location, int id);
    bool saveLocationToDatabase(ArchivedLocation location);

    /* Location Visit Records Functions: */
    


    /* Checks & Helpers */
    bool isKnown(int locationID);
    // bool
};



#endif