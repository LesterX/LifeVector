#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#ifndef BluetoothInterface_H
#define BluetoothInterface_H

/* This class was developed to gather the individual network interface based
 * on the file name within the network interface folder /sys/class/net*/

class BluetoothInterface {
    public:
        BluetoothInterface();
	    std::string read() const;
	    std::string write() const;
	    std::string listen() const;
	    std::string stopListening() const
	    std::string getInterfaceName() const;
	    bool confirmUniqueID(std::string uID) const;
	private:
            struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
	    char buf[1024] = { 0 };
	    int s, client, bytes_read;
            socklen_t opt = sizeof(rem_addr);
	    char address[18] = "XX:XX:XX:XX:XX:XX";
            std::string uniqueId;
	    const std::string FILENAME = std::string("/home/uniqueID");
	    int getUniqueID ();
};


#endif
