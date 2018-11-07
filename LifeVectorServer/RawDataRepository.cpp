#include "RawDataRepository.h"

/* Constructor */
RawDataRepository::RawDataRepository(std::string sourceFile, std::string fileSpecification)
{
    RawDataRepository::initJSON(sourceFile);

    RawDataRepository::buildRepository(fileSpecification);
}

RawDataRepository::~RawDataRepository()
{
    //dtor
}

/* Helpers */

void RawDataRepository::initJSON(std::string source)
{
    std::ifstream iFile(source);
    jsonFile = nlohmann::json::parse(iFile);
}

void RawDataRepository::buildRepository(std::string fileSpecification)
{

    nlohmann::json gpsEntry;                                                      // json object to extract the individual coordinte logs
    std::string tLabel = "time_stamp", xLabel = "latitude", yLabel = "longitude"; // labels in json file identifying the information to be parsed
    int counter = 0;                                                              // iteration counter for traversing json object

    // initialize first entry and iterate through the gps log file
    gpsEntry = jsonFile.at(fileSpecification).at(counter);
    while (!gpsEntry.is_null())
    {
        // initialize struct for entry and insert the relevant information
        gpsLog newEntry;
        newEntry.time = gpsEntry.at(tLabel).get<long>();
        newEntry.latitude = gpsEntry.at(xLabel).get<double>();
        newEntry.longitude = gpsEntry.at(yLabel).get<double>();

        // insert entry into raw data vector
        rawData.push_back(newEntry);

        // increment counter and grab next entry
        counter++;
        if ((signed int)jsonFile.at(fileSpecification).size() > counter)
            gpsEntry = jsonFile.at(fileSpecification).at(counter);
        else
            break;
    }
}

std::vector<RawDataRepository::gpsLog>::const_iterator RawDataRepository::getIterator()
{
    return rawData.begin();
}

void RawDataRepository::dumpData()
{
    std::vector<RawDataRepository::gpsLog>::const_iterator dataIterator;
    std::cout << "Entries:" << std::endl;
    for (dataIterator = rawData.begin(); dataIterator != rawData.end(); ++dataIterator)
    {
        gpsLog entry = *dataIterator;
        std::cout << entry.time << " - "
                  << "(" << entry.latitude << ", " << entry.longitude << ")" << std::endl;
    }
}