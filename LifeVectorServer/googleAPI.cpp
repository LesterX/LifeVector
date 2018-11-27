/*
to instal cURL on debian run :
sudo apt-get install libcurl4-openssl-dev

to compile as "main" executable run:
g++ main.cpp -L/usr/include/curl/lib -lcurl

to run:
./main

*/

/*queries google api and returns json formatted text*/

#include "googleAPI.h"

using namespace std;


    void googleAPI :: splitstr(const std::string& str, std::vector<std::string>& container, char delim)
    {
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim)) {
            container.push_back(token);
        }
    }

    string googleAPI :: getName(){

        return name;
    }


    string googleAPI :: getFormattedLocation(){

        std::vector<std::string> c;

        string result = "";

        result = doc.at("results")[0].at("formatted_address");
       // cout << "from json: " << result << endl;
        splitstr(result, c, ',');

        if (!isdigit((c[0].c_str())[0])){
            string n = c[0];
            //cout << "assignToNAME: " << c[0] << ", " << n << endl;

            name = n;
            result = "";
            for (int i = 1; i < c.size(); i++){
               // cout << c[i] << endl;
                result = result + c[i];
            }
        }
        
        location = result;
        
        return location;
    }

    string googleAPI :: getNorthEastLat(){

        string result;
        // Create an output string stream
        std::ostringstream streamObj;
        //Add double to stream
        streamObj << doc.at("results")[0].at("geometry").at("viewport").at("northeast").at("lat");
        // Get string from output string stream
        std::string strObj = streamObj.str();
     
        return strObj;
    }

    string googleAPI :: getNorthEastLng(){

        string result;
        // Create an output string stream
        std::ostringstream streamObj;
        //Add double to stream
        streamObj << doc.at("results")[0].at("geometry").at("viewport").at("northeast").at("lng");
        // Get string from output string stream
        std::string strObj = streamObj.str();
     
        return strObj;
    }


    string googleAPI :: getSouthWestLat(){

        string result;
        // Create an output string stream
        std::ostringstream streamObj;
        //Add double to stream
        streamObj << doc.at("results")[0].at("geometry").at("viewport").at("southwest").at("lat");
        // Get string from output string stream
        std::string strObj = streamObj.str();
     
        return strObj;
    }

    string googleAPI :: getSouthWestLng(){

        string result;
        // Create an output string stream
        std::ostringstream streamObj;
        //Add double to stream
        streamObj << doc.at("results")[0].at("geometry").at("viewport").at("southwest").at("lng");
        // Get string from output string stream
        std::string strObj = streamObj.str();
     
        return strObj;
    }

    string googleAPI :: getTypes(){

        string result = "";

        //char *arr = doc.at("results")[0].at("types");

        for (int i = 0; i < doc.at("results")[0].at("types").size(); i++){

            result = result.append(doc.at("results")[0].at("types")[i]);
            if (i + 1 != doc.at("results")[0].at("types").size()){
                result = result.append(", ");
            }
            
        }

        return result;

    }



