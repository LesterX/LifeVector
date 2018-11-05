#include <iostream>
#include <sys/utsname.h>
#include <string>
#include <sys/sysinfo.h>
#ifndef OSDETAILS_H
#define OSDETAILS_H

/* This class was developed to gather operating system details*/

class OSDetails {
    public:
        OSDetails();
        std::string getSystemName() const;
        std::string getOSRelease() const;
        std::string getOSVersion() const;
        std::string getMachineData() const;
        std::string getUptime() const;
        friend std::ostream& operator<<(std::ostream& os, const OSDetails& osdetails);
    private:
        struct utsname unameData;
        struct sysinfo systemInfo;
        std::string uptime = "";
        void getUname();
        void getSysInfo();
        void formatUptime();
};

std::ostream& operator<<(std::ostream& os, const OSDetails& osdetails);

#endif
