#include "ArchivedLocation.h"

/*
 * Initializer. 
 * Initializes all attributes and sets all values to 0 and 
 * all string to an empty string and creates empty 
 * VisitationInformation object
 */
void ArchivedLocation::init()
{
    locationName = description = address = "";
    northBound = southBound = westBound = eastBound = 0.0;
    longitudeRef = latitudeRef = 0;
    locationID = 0;
    visitations = VisitationInformation();
}

/* Constructors */
ArchivedLocation::ArchivedLocation(std::string lName, double locationLatitude, double locationLongitude)
{
    init();
    setName(lName);
    setReferencePoint(locationLatitude, locationLongitude);
}

ArchivedLocation::ArchivedLocation(int locID, double locationLatitude, double locationLongitude)
{
    init();
    setID(locID);
    setReferencePoint(locationLatitude, locationLongitude);
}

ArchivedLocation::ArchivedLocation(std::string locName, double latMin, double latMax, double longMin, double longMax)
{
    init();
    setName(locName);
    northBound = latMax;
    southBound = latMin;
    westBound = longMin;
    eastBound = longMax;
}

/* Destructor */
ArchivedLocation::~ArchivedLocation() {}

/* Setters: */
void ArchivedLocation::setID(int id)
{
    locationID = id;
}

void ArchivedLocation::setName(std::string name)
{
    locationName = name;
}

void ArchivedLocation::setAddress(std::string locAddress)
{
    address = locAddress;
}

void ArchivedLocation::setDescription(std::string location_description)
{
    description = location_description;
}

void ArchivedLocation::setBounds(double north, double south, double east, double west)
{
    setLatitudeBounds(south, north);
    setLongitudeBounds(west, east);
}

void ArchivedLocation::setReferencePoint(double latitude, double longitude)
{
    latitudeRef = latitude;
    longitudeRef = longitude;
}

void ArchivedLocation::setLatitudeBounds(double min, double max)
{
    northBound = max;
    southBound = min;
}

void ArchivedLocation::setLongitudeBounds(double min, double max)
{
    eastBound = max;
    westBound = min;
}

/* Getters: */
double ArchivedLocation::getNorthBound()
{
    return northBound;
}

double ArchivedLocation::getSouthBound()
{
    return southBound;
}

double ArchivedLocation::getWestBound()
{
    return westBound;
}

double ArchivedLocation::getEastBound()
{
    return eastBound;
}

int ArchivedLocation::getID()
{
    return locationID;
}

std::string ArchivedLocation::getName()
{
    return locationName;
}

std::string ArchivedLocation::getAddress()
{
    return address;
}

std::string ArchivedLocation::getDescription()
{
    return description;
}

double *ArchivedLocation::getReferencePoint()
{
    double gps[2] = {latitudeRef, longitudeRef};
    return gps;
}

/* Visitation Manipulation */
void ArchivedLocation::newVisitInstance(long timestamp, int duration)
{
    VisitTime newInstance(timestamp, duration);
    visitations.addInstance(newInstance);
}

VisitTime ArchivedLocation::getFirstVisitTime()
{
    return visitations.getFirst();
}

VisitTime ArchivedLocation::getLastVisitTime()
{
    return visitations.getMostRecent();
}

std::map<long, int> ArchivedLocation::getTimesFrom(long start, long fin)
{
    return visitations.getVisitsFrom(start, fin);
}

std::map<long, int> ArchivedLocation::getAllVisitations()
{
    return visitations.getFullVisitList();
}

long ArchivedLocation::getTotalVisitTime()
{
    return visitations.getTotalTime();
}

int ArchivedLocation::getVisitFrequency()
{
    return visitations.getFrequency();
}

long ArchivedLocation::getTimeSpent(long start, long fin)
{
    std::map<long, int> queryRange = getTimesFrom(start, fin);
    long time_period = 0;
    std::map<long, int>::const_iterator it;

    for (it = queryRange.begin(); it != queryRange.end(); ++it)
    {
        time_period += it->second;
    }

    return time_period;
}