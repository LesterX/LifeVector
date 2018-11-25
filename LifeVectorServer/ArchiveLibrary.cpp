#include "ArchiveLibrary.h"

/* Initialize Archive Library. Done through a connected DB pointed */
ArchiveLibrary::ArchiveLibrary(Database *db_pointer)
{
    connected_db = db_pointer;
}

// Static set declaration
std::set<int> ArchiveLibrary::locationIndex = std::set<int>();

/* Destructor: */
ArchiveLibrary::~ArchiveLibrary() {}

/* Location Functions: */
ArchivedLocation ArchiveLibrary::constructLocation(int id, std::string name, std::string address, std::string description, double latitude, double longitude, double northBound, double southBound, double eastBound, double westBound)
{
    ArchivedLocation location(id, latitude, longitude, northBound, southBound, eastBound, westBound);

    location.setLocationInformation(name, address, description);

    return location;
}

bool ArchiveLibrary::saveLocationToDatabase(ArchivedLocation location)
{
    if (isKnown(location.getID()))
    {
        std::cout << "Save to Database Failed: Location already in Database." << std::endl;
        return false;
    }

    std::stringstream command;
    double *gps = location.getLocationReference();

    command << "INSERT INTO ArchivedLocations "
            << "(locationID, locationName, address, latitudePosition, longitudePosition, northBound, southBound, eastBound, westBound, description) VALUES ("
            << location.getID() << ", '"
            << location.getLocationDetails().getName() << "', '"
            << location.getLocationDetails().getAddress() << "', "
            << *gps << ", " << *(gps + 1) << ", "
            << location.getCoordinateData().getNorthLimit() << ", "
            << location.getCoordinateData().getSouthLimit() << ", "
            << location.getCoordinateData().getEastLimit() << ", "
            << location.getCoordinateData().getWestLimit() << ", '"
            << location.getLocationDetails().getDescription() << "');";

    if (connected_db->exeSQL(command.str()))
    {
        std::cout << "New Location, " << location.getLocationDetails().getName() << ", has been added to Database" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Location Save Error: Could not save to Database" << std::endl;
        return false;
    }
}

bool ArchiveLibrary::getLocationFromDatabase(ArchivedLocation *location, int id)
{
    if (isKnown(id))
    {
        // "SELECT field FROM ArchivedLocations WHERE locationID = " << id << ";"
        std::stringstream query;
        std::string result;

        // Fetch Full Location Entry
        query << "SELECT * FROM ArchivedLocations WHERE locationID = " << id << ";";
        result = connected_db->getSQLResult(query.str());

        // Parse result into vector
        std::vector<std::string> fields;
        split(result, fields, '\t');

        /* Field Legend
         * 0. locationID, 
         * 1. locationName, 
         * 2. address, 
         * 3. latitudePosition, 
         * 4. longitudePosition, 
         * 5. northBound, 
         * 6. southBound, 
         * 7. eastBound, 
         * 8. westBound, 
         * 9. description
         */

        // Create Archive Location
        ArchivedLocation forArchive = constructLocation(atoi(fields[0].c_str()), fields[1], fields[2], fields[9], atof(fields[3].c_str()), atof(fields[4].c_str()), atof(fields[5].c_str()), atof(fields[6].c_str()), atof(fields[7].c_str()), atof(fields[8].c_str()));

        location = &forArchive;

        std::cout << "Location retrieved successfully from Database" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Location retrieval failed" << std::endl;
        return false;
    }
}

bool ArchiveLibrary::isKnown(int locationID)
{
    std::stringstream query;
    query << "SELECT locationID FROM ArchivedLocations WHERE locationID = '" << locationID << ";";
    std::string result = connected_db->getSQLResult(query.str());

    //Check if location exists
    if (result.length() < 2)
    {
        std::cout << "Location is not Known" << std::endl;
        return false;
    }
    else
    {
        std::cout << "Location is Known in Database" << std::endl;
        return true;
    }
}