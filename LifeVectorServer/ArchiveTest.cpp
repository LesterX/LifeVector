#include "Database.h"
#include "StringParser.h"
#include "ArchivedLocation.h"

#include <string>
#include <iostream>
#include <sstream>

int main()
{
    Database db;
    db.initDB("localhost", "server", "LifeVector123", "LifeVector");

    std::stringstream query;
    query << "SELECT * FROM ArchivedLocations WHERE locationID = " << 114 << ";";

    std::string result = db.getSQLResult(query.str());

    std::cout << result << std::endl;

    std::vector<std::string> splitted;

    split(result, splitted, '\t');

    std::cout << "Split Print:" << std::endl;
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

    ArchivedLocation test(atoi(splitted[0].c_str()), atof(splitted[3].c_str()), atof(splitted[4].c_str()), atof(splitted[5].c_str()), atof(splitted[6].c_str()), atof(splitted[7].c_str()), atof(splitted[8].c_str()));
    test.setLocationInformation(splitted[1], splitted[2], splitted[9]);

    test.printInformation();

    std::stringstream q1;
    q1 << "SELECT locationID FROM ArchivedLocations WHERE locationID=200;";

    result = db.getSQLResult(q1.str());

    std::cout << "|" << result << "|" << std::endl;
}