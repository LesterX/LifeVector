#!/bin/bash
echo "Building the process list utility"
g++ ProcessList.cpp ProcessInfo.cpp MainUtilities/ProcessListMain.cpp -o procListUtility
echo "Utility has been built execute it by using the command \"./procListUtility\""

