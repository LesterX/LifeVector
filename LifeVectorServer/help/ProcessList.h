#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include "ProcessInfo.h"
#ifndef PROCESSLIST_H
#define PROCESSLIST_H

/* This class was developed to create a list of processes from the
 * process ids found in the process folder /proc*/

class ProcessList {
    public:
        ProcessList();
        std::vector<ProcessInfo> getListOfProcesses() const;
        friend std::ostream& operator<<(std::ostream& os, const ProcessList& processList);
    private:
        const std::string fileName = std::string("/proc/");
        std::vector<std::string> listOfProcessIDs;
        std::vector<ProcessInfo> listOfProcesses;
        bool startsWith(const std::string& s, const std::string& prefix);
        bool isNotNumber(std::string line);
        int readProcessDirectory (std::string dir, std::vector<std::string> &fileList);
        void generateProcesses(std::vector<std::string> listOfProcessIDs, std::vector<ProcessInfo> &listOfProcesses);
};

std::ostream& operator<<(std::ostream& os, const ProcessList& processList);

#endif
