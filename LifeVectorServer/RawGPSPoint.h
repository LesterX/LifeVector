/*
* This class holds raw GPS coordinate data extracted from the .json file
* received from the mobile device.
*/

#ifndef GPSPOINT_H
#define GPSPOINT_H

class RawGPSPoint
{
public:
  //constructor
  RawGPSPoint(long recordedTime, double latCoordinate, double longCoordinate);

  //destructor
  ~RawGPSPoint();

  //Getters
  double getLatitude();
  double getLongitude();
  long getTimeStamp();

private:
  double latitude, longitude; //coordinate values in decimal degrees format
  long timestamp;             // time of recording in UNIX time format
};

#endif