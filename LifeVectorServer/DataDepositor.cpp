#include "DataDepositor.h"

DataDepositor::DataDepositor(Database *db, std::string deviceID, RawDataRepository dataset)
{
    // fetch time log of all the GPS points
    std::vector<long> timeLog = dataset.getTimeStamps();

    // initialize iterator for time log and insert each entry into database
    std::vector<long>::const_iterator i;
    for(i = timeLog.begin(); i != timeLog.end(); ++i)
    {
        // set up SQL command to insert entry
        double gpsXY[2];
        long timeUNIX = *i;
        dataset.getCoordinates(gpsXY, timeUNIX);
        std::string insertCommand = concatQuery(timeUNIX, gpsXY[0], gpsXY[2], device);

        // insert into database
        (*db).exeSQL(insertCommand);
    }
}

std::string DataDepositor::concatQuery(long timestamp, double latitude, double longitude, std::string device)
{
    std::string output tValue, xValue, yValue;
    tValue = std::to_string(timestamp);
    xValue = std::to_string(latitude);
    yValue = std::to_string(longitude);

    output = "INSERT INTO GPSUnprocessed (timeStamp, latitude, longitude, devID) VALUES (" +
             tValue + ", " + xValue + ", " + yValue + ", '" + device + "');";
    
    return output;
}

DataDepositor::~DataDepositor()
{
    //Destroy
}