/**
 *@brief creates and fetches the report to send to the front end
 */

#include "fetchReport.h"

using namespace std;

/**
 *@brief constructor
 */
fetchReport::fetchReport(){

}   
/**
 *@brief destructor
 */
fetchReport::~fetchReport(){

}

/**
 *@brief writes to an external report json file with location information for the user
 *@param visitL pointer to the visit log to get time spent and visits
 *@param db_connect a point to the database
 *@param loc_id
 */
void fetchReport::process(VisitLog *visitL, Database *db_connect, int loc_id){

    connect_db = db_connect;

    string result = visitL->beautify();

    vector<string> fields;
    vector<string> visits;
    //parse string
    StringParser::custom_parse(result, fields, ' :');

    //get the other information from the database
    stringstream addressQuery;
    addressQuery << "SELECT address FROM ArchivedLocations WHERE locationID = " << loc_id << ";";
    string address = connect_db->getSQLResult(addressQuery.str());

    stringstream query;
    
    query << "SELECT locationName FROM ArchivedLocations WHERE locationID = " << loc_id << ";";
    string locName = connect_db->getSQLResult(query.str());
    report[address]["name"] = locName;

    query << "SELECT description FROM ArchivedLocations WHERE locationID = " << loc_id << ";";
    string desc = connect_db->getSQLResult(query.str());

    //check if description is empty
    if (desc.find("Reseult Query Error:") != std::string::npos || desc.find("Result Query Error:") != std::string::npos) {
        report[address]["desciption"] = "";
    }
    else{
        report[address]["desciption"] = desc;
    }

    

    //further parsing need to get rid of some trailing chars
    StringParser::custom_parse(fields[4], visits, '\n');
    report[address]["totalTimeSpent"] = visits[0];
    report[address]["totalVisits"] = fields[5];

    //write to output json file
    std::ofstream o("sendtofront.json");

    o << report << std::endl;
}

/**
 *@brief get the report if needed
 *@return returns the json report
 */
nlohmann::json fetchReport::getReport(){

    return report;
}


