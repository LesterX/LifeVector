

#include "salt.h"
#include <string>

using namespace std;
 

 
int main(){

    std::string str = "Mario Fernandez";

    salt a ;

    a.saltUser(str);

    size_t salt = a.getSalt();
    size_t hash = a.getHash();
    string name = a.getUserName();


    cout << "Salt: " << salt << endl;
    cout << "Hash: " << hash << endl;
    cout << "Name: " << name << endl;

}