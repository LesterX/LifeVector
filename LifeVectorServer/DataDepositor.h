/* 
 * This Class is a method used to save the raw, unprocessed GPS coordinate
 * data received from the mobile device to the database. The raw data is
 * the parsed json stored in C++ objects already. The database pointer
 * received is already initialized, with connection SQL server already
 * established. This is saved according to the user, so deviceID is used
 * to identify the user this data being stored is assoiated with.
 */
#ifndef DATA_DEPOSITOR_H
#define DATA_DEPOSITOR_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "RawDataRepository.h"
#include "Database.h"

class DataDepositor
{
  private:
    Database *db_link;
    std::string concatRawQuery(long timestamp, double latitude, double longitude, std::string user, std::string device);

  public:
    DataDepositor(Database *db_pointer);
    bool depositRaw(std::string username, std::string deviceID, RawDataRepository dataset);

    ~DataDepositor();
};

#endif
