/** 
 * @brief used to query the google API
 */

#include "CURLplusplus.h"
using namespace std;

/** 
 * @brief get the string representation of the json we're getting from the google api
 * @param the url of the site we're querying in our case it's google's specific site for getting location info
 * @return a string containing json information
 */
string CURLplusplus :: Get(const std::string& url){
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

    ss.str("");
    http_code = 0;
    res = curl_easy_perform(curl);
    if (res != CURLE_OK){

        throw std::runtime_error(curl_easy_strerror(res));
    }
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    return ss.str();
}
/** 
 * @brief fetches the http code stored in the class
 * @return the http code
 */
long CURLplusplus :: GetHttpCode(){

    return http_code;
}
/** 
 * @brief writes data to the buffer
 * @param buffer a buffer to store information
 * @param size the size of the buffer
 * @param nmemb a number representing the member
 * @param userp a pointer to the user
 * @return the data we need
 */
size_t CURLplusplus :: write_data(void *buffer, size_t size, size_t nmemb, void *userp){

    return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
}
/** 
 * @brief writes data to the buffer
 * @param buffer a buffer to store information
 * @param size the size of the buffer
 * @param nmemb a number representing the member
 * @return the data we need
 */
size_t CURLplusplus :: Write(void *buffer, size_t size, size_t nmemb){

    ss.write((const char*)buffer,size*nmemb);
    return size*nmemb;
}
