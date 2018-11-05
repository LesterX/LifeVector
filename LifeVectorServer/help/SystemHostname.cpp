#include "SystemHostname.h"
using namespace std;

SystemHostname::SystemHostname() {
	char tempHostname[1024] = "";
	gethostname(tempHostname, 1023);
	hostname = string(tempHostname);
};
string SystemHostname::getHostname() const{
	return hostname;
}
ostream& operator<<(ostream& os, const SystemHostname& systemHostname){
	os << "Hostname: ";
	os << systemHostname.getHostname();
	return os;
}
