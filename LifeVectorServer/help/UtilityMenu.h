#include <iostream>
#include <string>
#include <unistd.h>
#include "InterfaceList.h"
#include "MemoryInfo.h"
#include "OSDetails.h"
#include "ProcessList.h"
#include "SystemHostname.h"
#include "ProcessorInfo.h"
#ifndef UTILITYMENU_H
#define UTILITYMENU_H

/* This class was developed to call the utilities "InterfaceList.h" "MemoryInfo.h"
 * "OSDetails.h" "ProcessList.h" "SystemHostname.h" "ProcessorInfo.h" and to create
 * a user friendly interface with basic error checking.*/

class UtilityMenu {
    public:
        UtilityMenu();
        void runUtility();
    private:
        const std::string DIVIDER = "\n" + std::string(60,'*') + "\n";
        std::string command;
};

#endif
