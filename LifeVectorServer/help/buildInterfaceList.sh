#!/bin/bash
echo "Building the network interface list utility"
g++ InterfaceList.cpp MainUtilities/InterfaceListMain.cpp NetworkInterface.cpp -o interfaceUtility
echo "Utility has been built execute it by using the command \"./interfaceUtility\""

