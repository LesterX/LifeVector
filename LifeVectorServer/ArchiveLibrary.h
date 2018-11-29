/**
 * @file ArchiveLibrary.h
 * @author Rukun Wang (rwang264@uwo.ca)
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef ARCHIVE_LIBRARY_H
#define ARCHIVE_LIBRARY_H

#include <map>
#include <set>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip> 

#include "Database.h"
#include "ArchivedLocation.h"
#include "VisitLog.h"
#include "UserVisitInfo.h"

#include "StringParser.h"

class ArchiveLibrary
{
private:
  Database *connected_db; // Pointer to a database link to mySQL

  /**
   * @brief Composes the userID for internal querying within the class
   *        Combines the username and the deviceID to userID with a '/'
   * 
   * @param username string - user's username identifier
   * @param deviceID string - device's identifier
   * @return std::string a combo userID string
   */
  std::string composeID(std::string username, std::string deviceID);

  /* Helpers: */
  /**
   * @brief Helper method to take retrieved data related to user logs
   * and insert them into C++ containers and object. 
   * 
   * @param userLog map<int, UserVisitInfo> * - the pointer pointing 
   * to the map that contains all the user visitation information, 
   * identified by the ID of location it is associated with  
   * @param result string - the input to function. It represents 
   * all the entries returned from the SQL query.
   */
  void userLogDBtoObj(std::map<int, UserVisitInfo> *userLog, std::string result);

  /**
   * @brief Helper method to take retrieved data related to location 
   * based logs and insert them into C++ containers and object
   * 
   * @param record VisitLog - the container for visit information at
   * a single speicified location for all users that have visited 
   * @param result string - the input to the function. It represents 
   * all the entries returned from the SQL query.
   */
  void locationLogDBtoOBJ(VisitLog *record, std::string result);

public:
  /**
   * @brief Construct a new Archive Library object
   * 
   * @param db_pointer Database* - points to a database client 
   * controller, handles all queries to the SQL database
   */
  ArchiveLibrary(Database *db_pointer);

  /**
   * @brief Destroy the Archive Library object
   * 
   */
  ~ArchiveLibrary();

  /* Location Functions: */

  /**
   * @brief Constructs a fully identified and defined Archive Location.
   * 
   * @param id int - location identifier
   * @param name string - name of the location
   * @param address string - physical address to the location
   * @param description - qualitative descriptors related to the location
   * @param latitude double - reference GPS latitude point of location
   * @param longitude double - reference GPS longitude point of location
   * @param northBound double - the northern boundary of the location
   * @param southBound double - the southern boundary of the location 
   * @param eastBound double - the eastern boundary of the location
   * @param westBound double - the western boundary of the location
   * @return ArchivedLocation object holding all the information related
   * to a location
   */
  ArchivedLocation constructLocation(int id, std::string name, std::string address, std::string description,
                                     double latitude, double longitude,
                                     double northBound, double southBound, double eastBound, double westBound);

  /**
   * @brief Get the Location From Database
   * 
   * @param id int - the ID of the location of interest
   * @return ArchivedLocation* point to the location of the given ID
   * found in the database. Returns a NULL pointer if location is not
   * known (not found in database)
   */
  ArchivedLocation *getLocationFromDatabase(int id);

  /**
   * @brief Saves a location object to the database
   * 
   * @param location ArchivedLocation - the object of the location to be
   * saved into the database.
   * @return true - location saved to database successfully
   * @return false - location failed to save to database
   */
  bool saveLocationToDatabase(ArchivedLocation location);

  /**
   * @brief Get the Adjacent Locations - Finds all the matching adjacent 
   * locations to the GPS point provided.
   * 
   * @param matchedLocations map<int, CoordinateInformation>& - container
   * holding all the adjacent matching locations. Container content is
   * only the relevant coordinate information, identified by the 
   * location's id
   * @param latitude double - the input x-coordinate
   * @param longitude double - the input y-coordinate
   * @return true if query to databse is success and the map is 
   * successfully created and stored.
   * @return false if not matching locations are found in the 
   * database
   */
  bool getAdjacentLocations(std::map<int, CoordinateInformation> &matchedLocations, double latitude, double longitude);

  /**
   * @brief Gets the ID of a matched location with the closest 
   * reference point to the inputed GPS Coordinate
   * 
   * @param matchedLocations map<int, CoordinateInformation>& - container
   * holding all the adjacent matching locations. Container content is
   * only the relevant coordinate information, identified by the 
   * location's id
   * @param latitude double - the input x-coordinate
   * @param longitude double - the input y-coordinate
   * @return int the location ID of the closest known matched location
   */
  int matchNearestLocation(std::map<int, CoordinateInformation> &matchedLocations, double latitude, double longitude);

  /* Location Visit Records Functions: */

  /**
   * @brief Archives a squashed GPS log of coordinate data in the database.
   * This log is identified by the associated location (with ID) and the 
   * user who generated the information
   * 
   * @param locationID int - location identifier
   * @param user - string username of the user who generated the log
   * @param device - sting deviceID of the user
   * @param userVisitLog - the User specific tracking log of squashed
   * information
   * @return true if log data has been successfully archived into
   * the database 
   * @return false if log data failed to save into the database
   */
  bool archiveUserLog(int locationID, std::string user, std::string device, UserVisitInfo userVisitLog);

  std::map<int, UserVisitInfo> *getUserLogFromDatabase(std::string user, std::string device);
  std::map<int, UserVisitInfo> *getUserLogBetween(std::string user, std::string device, long start, long fin);

  VisitLog *getLocationRecordFromDatabase(int locationID);
  VisitLog *getLocationRecordFBetween(int locationID, long start, long fin);

  int getVisitCount(int locationID);
  int getVisitCount(int locationID, std::string user, std::string device);
  int getCountBetween(int locationID, long start, long fin);
  int getCountBetween(int locationID, std::string user, std::string device, long start, long fin);
  int getTotalVisitCount();
  int getTotalCountBetween(long start, long fin);

  int getDurationAtLocation(int locationID);
  int getDurationAtLocation(int locationID, std::string user, std::string device);
  int getDurationBetween(int locationID, long start, long fin);
  int getDurationBetween(int locationID, std::string user, std::string device, long start, long fin);
  int getTotalDuration();
  int getTotalDurationBetween(long start, long fin);

  /* Checks */
  bool isKnown(int locationID);
  bool isRegistered(std::string user, std::string device);
  // bool
};

#endif
