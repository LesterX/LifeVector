#include <iostream>
#include <fstream>
#include <sys/utsname.h>
#include <string>
#include <sys/sysinfo.h>

#ifndef PROCESSORINFO_H
#define PROCESSORINFO_H

/* This class was developed to gather processor information*/

class ProcessorInfo {
    public:
        ProcessorInfo();
        std::string getVendorID() const;
        std::string getModelName() const;
        std::string getClockSpeedInMHz() const;
        float getMinuteAverageLoad() const;
        float getFiveMinuteAverageLoad() const;
        float getTenMinuteAverageLoad() const;
        friend std::ostream& operator<<(std::ostream& os, const ProcessorInfo& processorInfo);
    private:
        std::string vendorID, modelName, clockSpeedMHz;
        unsigned long int *loadAvgs;
        struct sysinfo systemInfo;
        void extractProcInfoFromFile();
        void getLoadAverages();
};

std::ostream& operator<<(std::ostream& os, const ProcessorInfo& processorInfo);

#endif //PROCESSORINFO_H
