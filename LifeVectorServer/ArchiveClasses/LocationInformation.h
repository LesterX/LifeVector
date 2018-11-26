#ifndef LOCATION_INFORMATION_H
#define LOCATION_INFORMATION_H

#include <string>

class LocationInformation
{
private:
    int id; // shorthand location identifier
    std::string name, address, description;

public:
    // Constructor
    LocationInformation(int locationID);

    // Destructor
    ~LocationInformation();

    // Detail Setters:
    void setName(std::string location_name);
    void setAddress(std::string location_address);
    void setDescription(std::string location_description);

    // Getters:
    int getID();
    std::string getName();
    std::string getAddress();
    std::string getDescription();
};

#endif