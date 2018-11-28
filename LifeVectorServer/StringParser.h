#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
 
void split(const std::string& str, std::vector<std::string>& container, char delim)
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        container.push_back(token);
    }
}

#endif