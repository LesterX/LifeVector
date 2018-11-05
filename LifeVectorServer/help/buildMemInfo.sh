#!/bin/bash
echo "Building the memory information utility"
g++ MemoryInfo.cpp MainUtilities/MemoryInfoMain.cpp -o memUtility
echo "Utility has been built execute it by using the command \"./memUtility\""

