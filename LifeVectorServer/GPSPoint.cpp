#include "GPSPoint.h"

GPSPoint::GPSPoint(long timestamp, double GPSLat, double GPSLong) : visitTime(timestamp)
{
    visitTime = VisitTime(timestamp);
    latitude = GPSLat;
    longitude = GPSLong;
}

void GPSPoint::setDuration(int newDuration)
{
    visitTime.setDuration(newDuration);
}

void GPSPoint::modifyDuration(int extendDuration)
{
    visitTime.extendDuration(extendDuration);
}

long GPSPoint::getTimestamp()
{
    return visitTime.getTimestamp();
}

int GPSPoint::getDuration()
{
    return visitTime.getDuration();
}

double GPSPoint::getLatitude()
{
    return latitude;
}

double GPSPoint::getLongitude()
{
    return longitude;
}