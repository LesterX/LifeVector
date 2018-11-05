#!/bin/bash
echo "Building the system hostname utility"
g++ SystemHostname.cpp MainUtilities/SystemHostnameMain.cpp -o sysHostUtility
echo "Utility has been built execute it by using the command \"./sysHostUtility\""

