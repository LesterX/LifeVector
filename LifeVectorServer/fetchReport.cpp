#include "fetchReport.h"

using namespace std;

// Constructor
fetchReport::fetchReport(){

}   
  // Destructor
fetchReport::~fetchReport(){

}

void fetchReport::process(VisitLog *visitL, int d){

    string result = visitL->beautify();

    vector<string> fields;
    StringParser::custom_parse(result, fields, '\t');

    int l_id = stoi(fields[0]);
    string name = fields[1],
                address = fields[2],
                descr = fields[9];
    double lat = stod(fields[3]),
           lng = stod(fields[4]),
           n = stod(fields[5]),
           s = stod(fields[6]),
           e = stod(fields[7]),
           w = stod(fields[8]);

    ArchivedLocation *location = new ArchivedLocation(l_id, lat, lng, n, s, e, w);
    location->setLocationInformation(name, address, descr);


   //report["some loc"]["totalVisits"] = vl.getTotalTimesVisited();
    report[address]["totalTimeSpent"] = d;
    report[address]["name"] = location->getLocationDetails().getName();
    report[address]["desciption"] = location->getLocationDetails().getDescription();

    cout << report << endl;

}

nlohmann::json fetchReport::getReport(){

    return report;
}


