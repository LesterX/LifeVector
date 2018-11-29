#ifndef ARCHIVE_LIBRARY_H
#define ARCHIVE_LIBRARY_H

#include <map>
#include <set>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

#include "Database.h"
#include "ArchivedLocation.h"
#include "VisitLog.h"
#include "UserVisitInfo.h"

#include "StringParser.h"

class ArchiveLibrary
{
private:
  Database *connected_db;
  
  std::string composeID(std::string username, std::string deviceID);

  /* Helpers: */
  void userLogDBtoObj(std::map<int, UserVisitInfo> *userLog, std::string result);
  void locationLogDBtoOBJ(VisitLog *record, std::string result);

public:
  /* Constructor */
  ArchiveLibrary(Database *db_pointer);

  /* Destructor */
  ~ArchiveLibrary();

  /* Location Functions: */
  ArchivedLocation constructLocation(int id, std::string name, std::string address, std::string description,
                                     double latitude, double longitude,
                                     double northBound, double southBound, double eastBound, double westBound);

  ArchivedLocation *getLocationFromDatabase(int id);
  bool saveLocationToDatabase(ArchivedLocation location);
  // bool deleteLocationFromDatabase(int locationID);

  bool getAdjacentLocations(std::map<int, CoordinateInformation> &matchedLocations, double latitude, double longitude);
  int matchNearestLocation(std::map<int, CoordinateInformation> &matchedLocations, double latitude, double longitude);

  /* Location Visit Records Functions: */
  bool archiveUserLog(int locationID, std::string user, std::string device, UserVisitInfo userVisitLog);

  std::map<int, UserVisitInfo> *getUserLogFromDatabase(std::string user, std::string device);
  std::map<int, UserVisitInfo> *getUserLogBetween(std::string user, std::string device, long start, long fin);

  VisitLog *getLocationRecordFromDatabase(int locationID);
  VisitLog *getLocationRecordFBetween(int locationID, long start, long fin);

  int getVisitCount(int locationID);
  int getVisitCount(int locationID, std::string user, std::string device);
  int getCountBetween(int locationID, long start, long fin);
  int getCountBetween(int locationID, std::string user, std::string device, long start, long fin);

  int getDurationAtLocation(int locationID);
  int getDurationAtLocation(int locationID, std::string user, std::string device);
  int getDurationBetween(int locationID, long start, long fin);
  int getDurationBetween(int locationID, std::string user, std::string device, long start, long fin);

  /* Checks */
  bool isKnown(int locationID);
  bool isRegistered(std::string user, std::string device);
  // bool
};

#endif
