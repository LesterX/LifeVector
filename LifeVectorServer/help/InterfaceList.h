#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include "NetworkInterface.h"

#ifndef INTERFACELIST_H
#define INTERFACELIST_H

/* This class was developed to create a list of network interfaces
 * The list is accessed using the method get ListOfInterfaces*/

class InterfaceList {
    public:
        InterfaceList();
        std::vector<NetworkInterface> getListOfInterfaces() const;
        friend std::ostream& operator<<(std::ostream& os, const InterfaceList& interfaceList);
    private:
        const std::string FILENAME = std::string("/sys/class/net");
        std::vector<std::string> listOfInterfaceNames;
        std::vector<NetworkInterface> listOfInterfaces;
        bool startsWith(const std::string& s, const std::string& prefix);
        int readNetworkDirectory (std::vector<std::string> &fileList);
        void generateNetworkInterfaces(std::vector<std::string> listOfInterfaceNames, std::vector<NetworkInterface> &listOfInterfaces);
};

std::ostream& operator<<(std::ostream& os, const InterfaceList& interfaceList);

#endif
