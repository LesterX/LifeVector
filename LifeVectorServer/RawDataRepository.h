/*
 * This class is responsible for the reading and parsing of the raw GPS data
 * file received from mobile device for processing. It parses the .json file
 * into a vector container, holding the timestamp and coordinate data. It is 
 * also capable of storing the raw data into the server database, if needed.
 */
#ifndef RAW_DATA_REPOSITORY_H
#define RAW_DATA_REPOSITORY_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>

#include "json.hpp"

class RawDataRepository
{
private:
  /* gpsLog is a structure holding the raw gps coordinate data
     * "time" is the time stamp of the log, saved in UNIX time format
     * "latitude" and "longitude" are the coordinates, in decimal degrees.
     * They range from -90 (S) to 90 (N) and -180 (W) to 180 (E), respectively.
     */
  struct gpsLog
  {
    long time;
    double latitude, longitude;
  };

  nlohmann::json jsonFile;        // the object holding the imported .json file
  std::map<long, gpsLog> rawData; // map holding the raw gps coordinates
  std::vector<long> logTimes;     // vector of times with logged gps data

  void initJSON(std::string source);          // function to import the .json file
  void buildRepository(std::string fileSpec); // function used to parse the json object to extract the timestamp and coordinate data to be stored in the vector
  void mapEntry(long time, gpsLog data);      // helper function to insert a single gps entry into the rawData map

public:
  // Constructor & Destructor
  RawDataRepository(std::string sourceFile, std::string fileSpecification);
  ~RawDataRepository();

  // Fetching coordinates
  std::vector<long> getTimeStamps();
  void getCoordinates(double *coordinates, long timestamp);
  void dumpData();
};

#endif