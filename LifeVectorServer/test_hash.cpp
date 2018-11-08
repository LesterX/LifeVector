

#include "hashfunc.h"
#include <string>

using namespace std;
 

 
int main(){

    std::string str = "1234";

    hashfunc a ;

    a.hashUser(str);

    size_t salt = a.getSalt();
    size_t hash = a.getHash();
    string pass = a.getUserPass();
    size_t specific_salt = a.getHash(str, to_string(salt));

    cout << "Salt: " << salt << endl;
    cout << "Hash: " << hash << endl;
    cout << "Password: " << pass << endl;

    cout << "Return specific hash: " << specific_salt << endl;

}