#!/bin/bash
echo "Building the OS Details utility"
g++ OSDetails.cpp MainUtilities/OSDetailsMain.cpp -o osDetsUtility
echo "Utility has been built execute it by using the command \"./osDetsUtility\""

