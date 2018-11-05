#include <iostream>
#include <string>
#include <unistd.h>

#ifndef SYSTEMHOSTNAME_H
#define SYSTEMHOSTNAME_H

/* This class was developed to gather the system hostname*/

class SystemHostname {
    public:
        SystemHostname();
        std::string getHostname() const;
        friend std::ostream& operator<<(std::ostream& os, const SystemHostname& systemHostname);
    private:
        std::string hostname;
};

std::ostream& operator<<(std::ostream& os, const SystemHostname& systemHostname);

#endif
