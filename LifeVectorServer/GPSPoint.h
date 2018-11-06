#ifndef GPSPOINT_H
#define GPSPOINT_H

#include "VisitTime.h"

class GPSPoint
{
  public:
    // constructor
    GPSPoint(long timestamp, double GPSLat, double GPSLong);

    // destructor
    ~GPSPoint();

    // Setters
    void setDuration(int newDuration);
    void modifyDuration(int extendDuration);

    // Getters
    double getLatitude();
    double getLongitude();
    long getTimestamp();
    int getDuration();

  private:
    double latitude, longitude;
    VisitTime visitTime;

    void init(long t, double gps1, double gps2);
};

#endif