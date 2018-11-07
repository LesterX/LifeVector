#include "BluetoothInterface.h"
using namespace std;


BluetoothInterface::BluetoothInterface(){
    uniqueID = getUniqueID(FILENAME);
    listen();

}

int BluetoothInterface::listen(){
    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    str2ba( address, &loc_addr.rc_bdaddr);
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));
    // put socket into listening mode
    listen(s, 1);
    return s;
}

string BluetoothInterface::connectAndRead(){
    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);
    
    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));
    
    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }
    close(client);
    string s(buf)
    return s;
}

int BluetoothInterface::stopListening(){
    // close connection
    close(s);
    return 0;
      
}

/* Open the address file corresponding the network interface and extract the MAC Address*/
int NetworkInterface::identifyMACAddress (string ifaceName){
    string ifaceFileLine;
    ifstream file;
    file.open(FILENAME + ifaceName + "/address");
    while (getline(file, ifaceFileLine)){
        MACAddress += ifaceFileLine;
    }
}


ostream& operator<<(ostream& os, const NetworkInterface& networkInterface){
    os << "Network Interface Name: ";
    os << networkInterface.getInterfaceName();
    os << "\n"; 
    os << "Interface MAC Address: ";
    os << networkInterface.getMACAddress();
    os << "\n";
    return os;
}

BluetoothInterface();
	    std::string read() const;
	    	    std::string write() const;
		    	    std::string listen() const;
			    	    std::string stopListening() const
				    	    std::string getInterfaceName() const;
					    	    bool confirmUniqueID(std::string uID) const;
						    	private:
							            std::string uniqueId;
								    	    const std::string FILENAME = std::string("/home/uniqueID");
									    	    int getUniqueID ();


#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char **argv)
{
}
