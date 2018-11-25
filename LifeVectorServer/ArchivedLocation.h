#ifndef ARCHIVED_LOCATION_H
#define ARCHIVED_LOCATION_H

#include <string>
#include <iostream>

#include "LocationInformation.h"
#include "CoordinateInformation.h"

class ArchivedLocation
{
private:
  // Attributes:
  LocationInformation details;
  CoordinateInformation coordinates;
  
  void init(); //initializer

public:
  // Constructors:
  ArchivedLocation(int locationID, double locationLatitude, double locationLongitude, double northPoint, double southPoint, double eastPoint, double westPoint);
  ArchivedLocation(int locationID, double locationLatitude, double locationLongitude);

  // Destructor
  ~ArchivedLocation();

  // Setters & Updaters:
  void setLocationInformation(std::string name, std::string locationAddress, std::string locationDescription);
  void setBoundaries(double north, double south, double east, double west);

  void updateName(std::string name);
  void updateAddress(std::string address);
  void updateDescription(std::string description);

  //Location Info Getters:
  LocationInformation getLocationDetails();
  int getID();
  CoordinateInformation getCoordinateData();
  double *getLocationReference();

  // Printer
  void printInformation();
};

#endif
