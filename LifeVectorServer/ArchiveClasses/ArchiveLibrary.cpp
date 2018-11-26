#include "ArchiveLibrary.h"

/* Initialize Archive Library. Done through a connected DB pointed */
ArchiveLibrary::ArchiveLibrary(Database *db_pointer)
{
    connected_db = db_pointer;
}

// Static set declaration
std::map<int, CoordinateInformation> ArchiveLibrary::locationIndex = std::map<int, CoordinateInformation>();

/* Destructor: */
ArchiveLibrary::~ArchiveLibrary() {}

/* Helpers: */
std::string ArchiveLibrary::composeID(std::string username, std::string deviceID)
{
    std::string combinationSymbol = "/", userID;
    userID.append(username);
    userID.append(combinationSymbol);
    userID.append(deviceID);

    return userID;
}

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
        std::cout << "Location could not save to Database" << std::endl;
        return false;
    }
}

bool ArchiveLibrary::getLocationFromDatabase(ArchivedLocation *location, int id)
{
    if (isKnown(id))
    {
        std::stringstream query;
        std::string result;

        // Fetch Full Location Entry
        query << "SELECT * FROM ArchivedLocations WHERE locationID = " << id << ";";
        result = connected_db->getSQLResult(query.str());

        // Parse result into vector
        std::vector<std::string> fields;
        split(result, fields, '\t');

        /* Field Legend : 
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

/* Location Visit Records Functions: */
bool ArchiveLibrary::archiveUserLog(int locationID, std::string user, std::string device, UserVisitInfo userVisitLog)
{
    // check for presence of location
    if (!isKnown(locationID))
    {
        std::cout << "Could not archive user log: Location not known" << std::endl;
        return false;
    }

    // extract iterator of user's time log
    std::map<long, int>::iterator record_iter;

    // iterate through log and enter each entry into DB
    for (record_iter = userVisitLog.getTimeLog().begin(); record_iter != userVisitLog.getTimeLog().end(); ++record_iter)
    {
        /* Fields Legend : VisitLog
        `visitTime` bigint(20) NOT NULL,
        `locationID` int(11) NOT NULL,
        `duration` int(11) NOT NULL,
        `username` varchar(10) NOT NULL,
        `deviceID` varchar(10) NOT NULL,
        */

        std::stringstream entry;
        entry << "INSERT INTO VisitLog"
              << "(visitTime, locationID, duration, username, deviceID) VALUES ("
              << record_iter->first << ", "
              << locationID << ", "
              << record_iter->second << ", '"
              << user << "', '"
              << device << "');";

        if (connected_db->exeSQL(entry.str()))
        {
            std::cout << "User Record at LocID, " << locationID << ", has been added to Database" << std::endl;
            return true;
        }
        else
        {
            std::cout << "User Record could not save to Database" << std::endl;
            return false;
        }
    }
}

bool ArchiveLibrary::getUserLogFromDatabase(std::map<int, UserVisitInfo> *userLog, std::string user, std::string device)
{
    userLog = new std::map<int, UserVisitInfo>();

    if (!isRegistered(user, device))
    {
        return false;
    }

    std::stringstream query;
    query << "SELECT * FROM VisitLog WHERE username = '"
          << user << "'AND deviceID = '" << device << "';";

    std::string results = connected_db->getSQLResult(query.str());

    std::vector<std::string> entries, fields;

    // separate each entry to interate through
    split(results, entries, '\n');
    std::vector<std::string>::iterator row = entries.begin();
    for (row; row != entries.end(); ++row)
    {
        // split entry to individual fields
        split(*row, fields, '\t');

        // check if location is in userLog already
        std::map<int, UserVisitInfo>::iterator target;
        target = userLog->find(atoi(fields[1].c_str()));

        if (target != userLog->end()) // location already in userLog
        {
            UserVisitInfo *visits = &(target->second);
            visits->addSingleLog(atof(fields[0].c_str()), atoi(fields[2].c_str()));
        }
        else // create new UserVisitInfo for entry and add to userLog
        {
            UserVisitInfo newVisits;
            newVisits.addSingleLog(atof(fields[0].c_str()), atoi(fields[2].c_str()));

            userLog->emplace(atoi(fields[1].c_str()), newVisits);
        }
    }

    return true;
}

bool ArchiveLibrary::getLocationRecordFromDatabase(VisitLog *record, int locationID)
{
    // Variable Declaration
    std::stringstream query;
    std::vector<std::string> entries, fields;

    // VisitLog initialization
    record = new VisitLog();

    if (!isKnown(locationID))
    {
        return false;
    }

    // Query database for entires related to locations
    query << "SELECT * FROM VisitLog WHERE locationID = " << locationID << ";";
    std::string results = connected_db->getSQLResult(query.str());

    // Split into entries (rows)
    split(results, entries, '\n');
    std::vector<std::string>::iterator row = entries.begin();

    for (row; row != entries.end(); ++row)
    {
        // Split into indiviual fields
        split(*row, fields, '\t');
        std::string uID = composeID(fields[3], fields[4]);

        // check for user in record
        if (record->userFound(uID))
        {
            // add entry
            record->addSingleEntry(uID, atof(fields[0].c_str()), atoi(fields[2].c_str()));
        }
        else
        {
            // insert new user and log into record
            record->addNewUser(uID);
            record->addSingleEntry(uID, atof(fields[0].c_str()), atoi(fields[2].c_str()));
        }
    }

    return true;
}

/* Checks & Helpers */
bool ArchiveLibrary::isKnown(int locationID)
{
    std::stringstream query;
    query << "SELECT locationID FROM ArchivedLocations WHERE locationID = " << locationID << ";";
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

bool ArchiveLibrary::isRegistered(std::string user, std::string device)
{
    std::stringstream query;
    query << "SELECT locationID FROM ArchivedLocations WHERE username = '" << user
          << "' AND deviceID = '" << device << "';";
    std::string result = connected_db->getSQLResult(query.str());

    //Check if location exists
    if (result.length() < 2)
    {
        std::cout << "User is not in Database" << std::endl;
        return false;
    }
    else
    {
        std::cout << "User is in Database" << std::endl;
        return true;
    }
}