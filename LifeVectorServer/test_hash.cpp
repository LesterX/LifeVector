

#include "hashfunc.h"
#include <string>

using namespace std;
 

 
int main(){

    std::string str = "1234";

    hashfunc a ;

    a.hashUser(str);

    size_t salt = a.getSalt();
    size_t hash = a.getHash();
    string name = a.getUserName();
    size_t specific_salt = a.getHash("1234", to_string(salt));

    cout << "Salt: " << salt << endl;
    cout << "Hash: " << hash << endl;
    cout << "Name: " << name << endl;

    cout << "Return specific hash: " << specific_salt << endl;

}