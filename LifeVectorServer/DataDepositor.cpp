#include "DataDepositor.h"

DataDepositor::DataDepositor(Database *db_pointer)
{
    db_link = db_pointer;
}

bool DataDepositor::depositRaw(std::string deviceID, RawDataRepository dataset)
{
    // fetch time log of all the GPS points
    std::vector<long> timeLog = dataset.getTimeStamps();

    // initialize bool checker
    bool isUploaded = false;

    // initialize iterator for time log and insert each entry into database
    std::vector<long>::const_iterator i;
    for (i = timeLog.begin(); i != timeLog.end(); ++i)
    {
        // set up SQL command to insert entry
        double gpsXY[2];
        long timeUNIX = *i;
        dataset.getCoordinates(gpsXY, timeUNIX);
        std::string insertCommand = concatRawQuery(timeUNIX, gpsXY[0], gpsXY[1], deviceID);

        // insert into database
        if ((*db_link).exeSQL(insertCommand))
        {
            isUploaded = true;
        }
        else
        {
            isUploaded = false;
            break;
        }
    }

    // Print Closing Message & return
    if (isUploaded)
        std::cout << "Raw GPS Data Successfully Uploaded to Database." << std::endl;
    else
        std::cout << "Raw GPS Data Upload Failed." << std::endl;

    return isUploaded;
}

std::string DataDepositor::concatRawQuery(long timestamp, double latitude, double longitude, std::string device)
{
    std::string output, tValue, xValue, yValue;
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