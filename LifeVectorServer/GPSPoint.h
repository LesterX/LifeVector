/*
* This class holds the collated GPS coordinate data.
* After processing of the "RawGPSPoints", it will be collated
* to be stored in this class before being passed to archive
* class for storage
*/
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
};

#endif