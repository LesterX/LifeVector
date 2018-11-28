/*
to instal cURL on debian run :
sudo apt-get install libcurl4-openssl-dev

to compile as "main" executable run:
g++ main.cpp -L/usr/include/curl/lib -lcurl

to run:
./main

*/

/*queries google api and returns json formatted text*/

#include "placesAPI.h"

using namespace std;

    string placesAPI :: getLocationName(){

        string result = doc.at("result").at("name");

        return result;
    }



