// This header is NOT generated.

#ifndef SYSTEM_TIME_MANAGER
#define SYSTEM_TIME_MANAGER

#include <time.h>
#include <string>

class SystemTimeManager
{
  private:
    time_t intTime;
    struct tm *UTCformat, *ESTformat;

  public:
    SystemTimeManager();              // initializes object with the current time
    SystemTimeManager(long unixTime); // initializes object with a given UNIX time
    ~SystemTimeManager();             //destructor

    std::string UNIXtoEST(); // converts the stored time in Eastern Time Zone into a readable format
    std::string UNIXtoUTC(); // converts the stored time in Coordinated Universal Time into a readable format
    long getTime();          // fetch the time in UNIX integer format
};

#endif
