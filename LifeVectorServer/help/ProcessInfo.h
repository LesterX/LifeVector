#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#ifndef ProcessInfo_H
#define ProcessInfo_H


/* This class was developed to gather the origin and status information on individual processes*/

class ProcessInfo {
	public:
		ProcessInfo(int processNumber);
		std::string getProcessName() const;
		std::string getProcessState() const;
		int getProcessID() const;
		int getParentProcessID() const;
		int getOwnerUserID() const;
		friend std::ostream& operator<<(std::ostream& os, const ProcessInfo& processInfo);
    private:
		std::string processName, state;
		int processID, parentProcessID, ownerUserID;
		const std::string FILENAME = std::string("/proc/");
		bool startsWith(const std::string& s, const std::string& prefix);
		int parseProcessInformation (int procNumber);
};


std::ostream& operator<<(std::ostream& os, const ProcessInfo& processInfo);
#endif
