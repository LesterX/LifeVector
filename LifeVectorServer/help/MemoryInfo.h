#include <iostream>
#include <fstream>
#include <sys/utsname.h>
#include <string>
#include <sys/sysinfo.h>

#ifndef MEMORYINFO_H
#define MEMORYINFO_H

/* This class was developed to gather information on free available memory
 * and total system memory*/

class MemoryInfo {
    public:
        MemoryInfo();
        unsigned long int getAvailableFreeMemory() const;
        unsigned long int getTotalMemory() const;
        friend std::ostream& operator<<(std::ostream& os, const MemoryInfo& memoryInfo);
    private:
        unsigned long int availableFreeMem, totalMemory;
        struct sysinfo systemInfo;
        void getMemoryInfo();
};

std::ostream& operator<<(std::ostream& os, const MemoryInfo& memoryInfo);

#endif
