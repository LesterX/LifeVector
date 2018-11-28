#ifndef COORDINATION_INFORMATION_H
#define COORDINATION_INFORMATION_H

class CoordinateInformation
{
private:
  double latitude, longitude; // reference coordinate point
  double north, east, south, west; // directional boundaries of the location around reference point

public:
  // Constructors:
  CoordinateInformation(double latitudeReference, double longitudeReference);

  // Destructor:
  ~CoordinateInformation();

  // Setter:
  void setLimits(double northLimit, double southLimit, double eastLimit, double westLimit);

  // Getters:
  double getLatitude();
  double getLongitude();

  double getNorthLimit();
  double getSouthLimit();
  double getEastLimit();
  double getWestLimit();
};

#endif