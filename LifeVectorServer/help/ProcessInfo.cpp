#include "ProcessInfo.h"
using namespace std;

ProcessInfo::ProcessInfo(int processNumber){
    parseProcessInformation(processNumber);
}


string ProcessInfo::getProcessName() const{
    return processName;
}
string ProcessInfo::getProcessState() const{
    return state;
}
int ProcessInfo::getProcessID() const{
    return processID;
}
int ProcessInfo::getParentProcessID() const{
    return parentProcessID;
}

int ProcessInfo::getOwnerUserID() const{
    return ownerUserID;
}
/*Function for string startsWith*/
bool ProcessInfo::startsWith(const string& s, const string& prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

/* Gather process information from the status file within the process ID folder. Uses procNumber as process ID*/
int ProcessInfo::parseProcessInformation (int procNumber){
    string procFileLine;
    ifstream file;
    file.open(FILENAME + to_string(procNumber) + "/status");
    while (getline(file, procFileLine)){
        int negative = string::npos;
        if (startsWith(procFileLine, "Name:")){
	    processName = procFileLine.substr(procFileLine.find(":") + 1); 
	} else if (startsWith(procFileLine, "Pid:")){
	    processID = stoi(procFileLine.substr(procFileLine.find(":") + 1));
	} else if (startsWith(procFileLine, "PPid:")){
	    parentProcessID = stoi(procFileLine.substr(procFileLine.find(":") + 1));
	} else if (startsWith(procFileLine, "State:")){
	    state = procFileLine.substr(procFileLine.find(":") + 1);
	} else if (startsWith(procFileLine, "Uid:")){
	    string second;
	    string first = procFileLine.substr(procFileLine.find(":") + 1);
	    string::size_type pos;
	    pos=first.find(' ',0);
	    second=first.substr(pos+1);
	    first=first.substr(0,pos);
	    ownerUserID = stoi(first);
	}
    }
}


ostream& operator<<(ostream& os, const ProcessInfo& processInfo){
    os << "Process Name: ";
    os << processInfo.getProcessName();
    os << "\n"; 
    os << "Process State: ";
    os << processInfo.getProcessState();
    os << "\n";
    os << "Process ID: ";
    os << processInfo.getProcessID();
    os << "\n"; 
    os << "Parent Process ID: ";
    os << processInfo.getParentProcessID();
    os << "\n";
    os << "Owner User ID: ";
    os << processInfo.getOwnerUserID();
    os << "\n"; 
    return os;
}

