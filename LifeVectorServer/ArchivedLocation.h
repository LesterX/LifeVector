#ifndef ARCHIVED_LOCATION_H
#define ARCHIVED_LOCATION_H

#include <string>
// #include <vector>
#include <map>

#include "VisitationInformation.h"
#include "VisitTime.h"

class ArchivedLocation
{
  private:
    double latitudeRef, longitudeRef;                    // reference coordinate point
    double northBound, southBound, westBound, eastBound; // MinMax ranges for the gps points
    std::string locationName, description, address;      // qualitative identifiers
    int locationID;                                      // shorthand location identifier

    VisitationInformation visitations;

    void init(); //initializer

  public:
    // Constructors:
    ArchivedLocation(std::string lName, double locationLatitude, double locationLongitude);
    ArchivedLocation(int locID, double locationLatitude, double locationLongitude);
    ArchivedLocation(std::string locName, double latMin, double latMax, double longMin, double longMax);

    // Destructor
    ~ArchivedLocation();

    // Setters:
    void setID(int id);
    void setName(std::string name);
    void setAddress(std::string locAddress);
    void setDescription(std::string location_description);
    void setReferencePoint(double latitude, double longitude);
    void setLatitudeBounds(double min, double max);
    void setLongitudeBounds(double min, double max);

    // Visitation Manipulation
    void newVisitInstance(long timestamp, int duration);
    VisitTime getFirstVisitTime();
    VisitTime getLastVisitTime();
    std::map<long, int> getTimesFrom(long start, long fin);
    std::map<long, int> getAllVisitations();
    long getTotalVisitTime();
    long getTimeSpent(long start, long fin);
    int getVisitFrequency();

    //Location Info Getters:
    double getNorthBound();
    double getSouthBound();
    double getWestBound();
    double getEastBound();
    double *getReferencePoint();
    int getID();
    std::string getName();
    std::string getAddress();
    std::string getDescription();
};

#endif
