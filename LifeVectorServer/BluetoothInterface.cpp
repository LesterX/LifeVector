#include "BluetoothInterface.h"
using namespace std;


BluetoothInterface::BluetoothInterface(){
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

    string bufferVal(buf)
    return bufferVal;
}

bool BluetoothInterface::write(string phrase){
    write(client, phrase, )
}

int BluetoothInterface::closeClientConnection(){
    close(client);
    return 0;
}

int BluetoothInterface::stopListening(){
    // close connection
    close(s);
    return 0;

}

/* Open the address file corresponding the network interface and extract the MAC Address*/
bool NetworkInterface::confirmUniqueID (string testID){
    ifstream file;
    string devID;
    file.open("/home/deviceID");
    while (getline(file, devID)){
        uniqueId = devID;
    }
    if (!uniqueId.compare(testID)){
        return true
    } else {
        return false
    }
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
