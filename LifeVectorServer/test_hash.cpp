#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <stdlib.h> 
#include <sys/random.h>

using namespace std;
 
struct S {
    std::string first_name;
    std::string last_name;
};

bool operator==(const S& lhs, const S& rhs) {
    return lhs.first_name == rhs.first_name && lhs.last_name == rhs.last_name;
}
 
// custom hash can be a standalone function object:
struct MyHash
{
    std::size_t operator()(S const& s) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(s.first_name);
        std::size_t h2 = std::hash<std::string>{}(s.last_name);

        return h1 ^ (h2 << 1); 
    }
};
 
int main(){

    size_t bufsz = 1024;
    char *buf = (char *)malloc(bufsz);

    getrandom(buf, bufsz, GRND_RANDOM);
    int *salt ;
    salt = (int*)buf;
    while (*salt < 0){
        getrandom(buf, bufsz, GRND_RANDOM);
        salt = (int*)buf;
    }

    std::string str = "Mario Fernandez";

    //join str to salt
    std::string salt_str = to_string(*salt);
    std::string salt_plus_string = str + salt_str;

    //hash name and salt value together
    std::size_t str_hash = std::hash<std::string>{}(salt_plus_string );
    std::cout << "User Name: Mario Fernandez" << endl; 
    cout << "Salt: " << *salt << endl;
    std::cout << "Hash Value: " << str_hash << endl;


}