/**
 * cpp file for salt calss
 */

#include "hashfunc.h"


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


void hashfunc :: hashUser(string str){
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
    string salt_str = to_string(*salt);
    string salt_plus_string = str + salt_str;
    //hash name and salt value together
    hash = std::hash<std::string>{}(salt_plus_string );

    //return hash;
}

size_t hashfunc :: getHash(string password, string in_salt){

    size_t ret_hash;

    

    
    string salt_plus_string = password + in_salt;

    ret_hash = std::hash<std::string>{}(salt_plus_string );




    return ret_hash;
}


size_t hashfunc :: getSalt(){
    return *salt;
}
size_t hashfunc :: getHash(){
    return hash;
}
string hashfunc :: getUserName(){
    return user_name;
}
/*
void hashfunc :: hashUser(string str){
   
    CkCrypt2 crypt;

    bool success = crypt.UnlockComponent("Anything for 30-day trial");
    if (success != true) {
        std::cout << crypt.lastErrorText() << "\r\n";
        return;
    }

    const char *hexKey = 0;
    //  http://www.di-mgt.com.au/cryptoKDFs.html#examplespbkdf

    const char *pw = "password";
    const char *pwCharset = "ansi";
    //  Hash algorithms may be: sha1, md2, md5, etc.
    const char *hashAlg = "sha1";
    //  The salt should be 8 bytes:
    const char *saltHex = "78578E5A5D63CB06";
    int iterationCount = 2048;
    //  Derive a 192-bit key from the password.
    int outputBitLen = 192;

    //  The derived key is returned as a hex or base64 encoded string.
    //  (Note: The salt argument must be a string that also uses
    //  the same encoding.)
    const char *enc = "hex";

    hexKey = crypt.pbkdf2(pw,pwCharset,hashAlg,saltHex,iterationCount,outputBitLen,enc);

    std::cout << hexKey << "\r\n";

    //  The output should have this value:
    //  BFDE6BE94DF7E11DD409BCE20A0255EC327CB936FFE93643

    }
*/


	