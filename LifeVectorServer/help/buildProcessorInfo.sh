#!/bin/bash
echo "Building the processor information utility"
g++ ProcessorInfo.cpp MainUtilities/ProcessorInfoMain.cpp -o procInfoUtility
echo "Utility has been built execute it by using the command \"./procInfoUtility\""

