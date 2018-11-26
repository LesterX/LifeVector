#include "StringParser.h"

#include "../Database.h"
// #include "../UserController.h"

// All Archive Classes
#include "UserVisitInfo.h"
#include "VisitLog.h"
#include "LocationInformation.h"
#include "CoordinateInformation.h"
#include "ArchivedLocation.h"
// #include "ArchiveLibrary.h"

#include <string>
#include <iostream>
#include <sstream>

/* void add_user()
{
    // add user
    UserController uc("server", "LifeVector123");
    uc.createUser("usr1", "nx5", "LV123");
    uc.~UserController();
} */

Database add_database_entries()
{
    // init local db and add test entries
    Database db;
    db.initDB("localhost", "server", "LifeVector123", "LifeVector");

    db.exeSQL("DELETE FROM VisitLog WHERE locationID = 114;");

    db.exeSQL("INSERT INTO VisitLog (visitTime, locationID, duration, username, deviceID) VALUES (1543183200, 114, 900, 'usr1', 'nx5');");

    db.exeSQL("INSERT INTO VisitLog (visitTime, locationID, duration, username, deviceID) VALUES (1540519559, 114, 1800, 'usr1', 'nx5');");

    db.exeSQL("INSERT INTO VisitLog (visitTime, locationID, duration, username, deviceID) VALUES (1542337559, 114, 3000, 'usr1', 'nx5');");

    std::cout << "VisitLog Insert Successful" << std::endl;

    return db;
}

/* void location_db_insertion_test(Database db);
{
    // Insert Location
    std::stringstream query;
    query << "SELECT * FROM ArchivedLocations WHERE locationID = " << 114 << ";";

    std::string result = db.getSQLResult(query.str());

    std::cout << result << std::endl;

    std::vector<std::string> splitted = std::vector<std::string>();

    split(result, splitted, '\t');

    std::cout << "Location Split Print:" << std::endl;

    std::vector<std::string>::iterator it;

    int i = 0;

    for (it = splitted.begin(); it != splitted.end(); ++it)
    {
        std::cout << i++ << ".\t" << (*it) << std::endl;
    }

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

/* ArchivedLocation test(atoi(splitted[0].c_str()), atof(splitted[3].c_str()), atof(splitted[4].c_str()), atof(splitted[5].c_str()), atof(splitted[6].c_str()), atof(splitted[7].c_str()), atof(splitted[8].c_str()));

    test.setLocationInformation(splitted[1], splitted[2], splitted[9]);

    test.printInformation();

    std::stringstream q1;
    q1 << "SELECT locationID FROM ArchivedLocations WHERE locationID=200;";

    result = db.getSQLResult(q1.str());

    std::cout << "|" << result << "|" << std::endl;
} */

void log_output_test(Database db)
{
    // for visitlog
    std::stringstream query;
    query << "SELECT * FROM VisitLog WHERE locationID = " << 114 << ";";

    std::string result = db.getSQLResult(query.str());

    std::cout << result << std::endl;

    std::vector<std::string> splitted;

    std::cout << "Result for all VL entries\n"
              << result << "\n---------" << std::endl;

    splitted = std::vector<std::string>();
    split(result, splitted, '\n');

    std::cout << "VisitLog Split Print:" << std::endl;
    std::vector<std::string>::iterator it;

    int i = 0;
    for (it = splitted.begin(); it != splitted.end(); ++it)
    {
        std::cout << i++ << ". " << (*it) << std::endl;
    }
}

std::string composeID(std::string username, std::string deviceID)
{
    std::string combinationSymbol = "/", userID;
    userID.append(username);
    userID.append(combinationSymbol);
    userID.append(deviceID);

    return userID;
}

int main()
{
    using namespace std;

    // Location Archiver Tests

    LocationInformation l(200);
    l.setName("Thompson Arena");
    l.setAddress("Western University, Lambton Drive, Stoneybrook Gardens, London, Middlesex County, Ontario, N6G 5K8, Canada");
    l.setDescription("sports centre");

    cout << "LocInfo: \n"
         << l.getID() << " - has been created.\n"
         << l.getAddress() << "\n"
         << l.getName() << "\n"
         << l.getDescription() 
         << endl;
    
    double x = 43.00307, y = -81.27547;
    double n = 43.00341, w = -81.27605, s = 43.00268, e = -81.27488;
    CoordinateInformation c(x, y);
    c.setLimits(n, s, e, w);

    cout << "Coordinate Object created" << endl;

    ArchivedLocation archL(l.getID(), x, y, n, s, e, w);
    archL.setLocationInformation(l.getName(), l.getAddress(), l.getDescription());

    cout << "ArchivedLocation object created: archL : " << endl;
    archL.printInformation();

    // Log class tests

    UserVisitInfo uvi;
    uvi.addSingleLog(1543183200, 900);
    uvi.addSingleLog(1540519559, 3000);
    uvi.addSingleLog(1542337559, 6000);

    cout << "UserVisitInfo object created : uvi" << endl;
    uvi.printLog();
    
    VisitLog vl;
    bool check = false;

    string uID;
    uID = composeID("usr1","nx5");

    if (vl.userFound(uID))
    {
        check = vl.addNewLog(uID, uvi);
    }
    else
    {
        if(vl.addNewUser(uID))
        {
            check = vl.addNewLog(uID, uvi);
        }
    }


    cout << "VisitLog vl is populated with uvi - " << check << endl;

    UserVisitInfo uvi2;

    uvi2.updateLog(uvi);
}