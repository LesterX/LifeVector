#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#ifndef NetworkInterface_H
#define NetworkInterface_H

/* This class was developed to gather the individual network interface based
 * on the file name within the network interface folder /sys/class/net*/

class NetworkInterface {
    public:
        NetworkInterface(std::string ifaceName);
	    std::string getMACAddress() const;
	    std::string getInterfaceName() const;
	    friend std::ostream& operator<<(std::ostream& os, const NetworkInterface& networkInterface);
	private:
		std::string interfaceName, MACAddress;
		const std::string FILENAME = std::string("/sys/class/net/");
		int identifyMACAddress (std::string ifaceName);
};


std::ostream& operator<<(std::ostream& os, const NetworkInterface& networkInterface);
#endif
