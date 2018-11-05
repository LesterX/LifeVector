#include "ProcessorInfo.h"
using namespace std;

ProcessorInfo::ProcessorInfo() {
    extractProcInfoFromFile();
    getLoadAverages();
};
string ProcessorInfo::getVendorID() const{
    return vendorID;
}
string ProcessorInfo::getModelName() const{
    return modelName;
}
string ProcessorInfo::getClockSpeedInMHz() const{
    return clockSpeedMHz;
}
float ProcessorInfo::getMinuteAverageLoad() const{
    return loadAvgs[0] / (float)(1 << SI_LOAD_SHIFT);
}
float ProcessorInfo::getFiveMinuteAverageLoad() const{
    return loadAvgs[1] / (float)(1 << SI_LOAD_SHIFT);
}
float ProcessorInfo::getTenMinuteAverageLoad() const{
    return loadAvgs[2] / (float)(1 << SI_LOAD_SHIFT);
}

/*Extract processor information from file and isolate field information */
void ProcessorInfo::extractProcInfoFromFile() {
    string procFileLine;
    ifstream file;
    file.open("/proc/cpuinfo");
    while (getline(file, procFileLine)){
        int negative = string::npos;
        //Check if the field gather matches a valid field for extraction
        if (procFileLine.find("vendor_id") != negative ){
            // Extract everything past the colon
            vendorID = procFileLine.substr(procFileLine.find(":") + 1);
        } else if (procFileLine.find("model name") != negative){
            modelName = procFileLine.substr(procFileLine.find(":") + 1);
        } else if (procFileLine.find("cpu MHz") != negative){
            clockSpeedMHz = procFileLine.substr(procFileLine.find(":") + 1);
        }
    }
    file.close();
}

/*Gather system information*/
void ProcessorInfo::getLoadAverages(){
    sysinfo(&systemInfo);
    loadAvgs = systemInfo.loads;
}


ostream& operator<<(ostream& os, const ProcessorInfo& processorInfo){
    os << "Processor Vendor ID: ";
    os << processorInfo.getVendorID();
    os << "\n";
    os << "Processor Model Name: ";
    os << processorInfo.getModelName();
    os << "\n";
    os << "Processor Clock Speed (MHz): ";
    os << processorInfo.getClockSpeedInMHz();
    os << "\n";
    os << "Processor 1 Minute Average Load: ";
    os << processorInfo.getMinuteAverageLoad();
    os << "\n";
    os << "Processor 5 Minute Average Load: ";
    os << processorInfo.getFiveMinuteAverageLoad();
    os << "\n";
    os << "Processor 10 Minute Average Load: ";
    os << processorInfo.getTenMinuteAverageLoad();
    return os;
}



