#include "OSDetails.h"
using namespace std;

OSDetails::OSDetails() {
	getUname();
	getSysInfo();
};
string OSDetails::getSystemName() const{
	return string(unameData.sysname);
}
string OSDetails::getOSRelease() const{
	return string(unameData.release);
}
string OSDetails::getOSVersion() const{
	return string(unameData.version);
}
string OSDetails::getMachineData() const{
	return string(unameData.machine);
}
string OSDetails::getUptime() const{
	return uptime;
}

void OSDetails::getUname() {
	uname(&unameData);
}

/*Gather system information*/
void OSDetails::getSysInfo(){
	sysinfo(&systemInfo);
	formatUptime();
}

/* Convert uptime from seconds to Days:Hours:Minutes:Seconds */
void OSDetails::formatUptime(){
	int totalSeconds, uptimeSecs, uptimeMins, uptimeHours, uptimeDays;
	totalSeconds = systemInfo.uptime;
	uptimeDays = totalSeconds / 60 / 60 / 24;
	uptimeHours = (totalSeconds / 60 / 60) % 24;
	uptimeMins = (totalSeconds / 60) % 60;
	uptimeSecs = totalSeconds % 60;
	uptime += to_string(uptimeDays);
	uptime += ":";
	uptime += to_string(uptimeHours);
	uptime += ":";
	uptime += to_string(uptimeMins);
	uptime += ":";
	uptime += to_string(uptimeSecs);
}

ostream& operator<<(ostream& os, const OSDetails& osdetails){
    os << "System Name: ";
    os << osdetails.getSystemName();
    os << "\n"; 
    os << "OS Release: "; 
    os << osdetails.getOSRelease(); 
    os << "\n"; 
    os << "OS Version: "; 
    os << osdetails.getOSVersion(); 
    os << "\n"; 
    os << "Machine Data: "; 
    os << osdetails.getMachineData(); 
    os << "\n";
    os << "Uptime: ";
    os << osdetails.getUptime();
    return os;
}

