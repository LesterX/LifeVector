#include "MemoryInfo.h"
using namespace std;

MemoryInfo::MemoryInfo() {
    getMemoryInfo();
};

unsigned long int MemoryInfo::getAvailableFreeMemory() const{
    return availableFreeMem/1000;
}
unsigned long int MemoryInfo::getTotalMemory() const{
    //convert to kilobytes
    return totalMemory/1000;
}

/*Access system information and gather free available and total memory information*/
void MemoryInfo::getMemoryInfo(){
    sysinfo(&systemInfo);
    availableFreeMem = systemInfo.freeram;
    totalMemory = systemInfo.totalram;
}

ostream& operator<<(ostream& os, const MemoryInfo& memoryInfo){
    os << "Available Free Memory: ";
    os << memoryInfo.getAvailableFreeMemory() << " Kb";
    os << "\n"; 
    os << "Total Memory: "; 
    os << memoryInfo.getTotalMemory() << " Kb";
    os << "\n"; 
    return os;
}


