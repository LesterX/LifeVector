#include "RawGPSPoint.h"

RawGPSPoint::RawGPSPoint(long recordedTime, double latCoordinate, double longCoordinate)
{
    timestamp = recordedTime;
    latitude = latCoordinate;
    longitude = longCoordinate;
}

long RawGPSPoint::getTimeStamp()
{
    return timestamp;
}

double RawGPSPoint::getLatitude()
{
    return latitude;
}

double RawGPSPoint::getLongitude()
{
    return longitude;
}