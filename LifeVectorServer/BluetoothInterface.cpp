#include "NetworkInterface.h"
using namespace std;

/*Constructor requires a file name corresponding to it's interface name*/
NetworkInterface::NetworkInterface(string ifaceName){
    identifyMACAddress(ifaceName);
    interfaceName = ifaceName;
}

string NetworkInterface::getMACAddress() const{
    return MACAddress;
}
string NetworkInterface::getInterfaceName() const{
    return interfaceName;
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

