/**
 * cpp file for salt calss
 */

#include "salt.h"


using namespace std;

struct S {
    std::string first_name;
    std::string last_name;
};

bool operator==(const S& lhs, const S& rhs) {
    return lhs.first_name == rhs.first_name && lhs.last_name == rhs.last_name;
}
 

struct MyHash
{
    std::size_t operator()(S const& s) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(s.first_name);
        std::size_t h2 = std::hash<std::string>{}(s.last_name);

        return h1 ^ (h2 << 1); 
    }
};


void salt :: saltUser(string str){
    //store username
    user_name = str;

    size_t bufsz = 1024;

    char *buf = (char *)malloc(bufsz);

    getrandom(buf, bufsz, GRND_RANDOM);

    salt = (size_t*)buf;

    //onlt generate positive salt values
    while (*salt < 0){
        getrandom(buf, bufsz, GRND_RANDOM);
        salt = (size_t*)buf;
    }

    //join str to salt
    std::string salt_str = to_string(*salt);
    std::string salt_plus_string = str + salt_str;
    //hash name and salt value together
    hash = std::hash<std::string>{}(salt_plus_string );

    //return hash;
}

size_t salt :: getSalt(){
    return *salt;
}
size_t salt :: getHash(){
    return hash;
}
string salt :: getUserName(){
    return user_name;
}



	