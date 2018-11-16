#include "SystemTimeManager.h"
#include <iostream>

SystemTimeManager::SystemTimeManager(long unixTime)
{
    intTime = unixTime;
}

SystemTimeManager::SystemTimeManager()
{
    time(&intTime);
}

SystemTimeManager::~SystemTimeManager() {}

std::string SystemTimeManager::UNIXtoEST()
{
    ESTformat = localtime(&intTime);
    char buffer[80];

    // std::cout << "|" << ESTformat->tm_year << "-" << ESTformat->tm_mon << "-" << ESTformat->tm_mday << " " << ESTformat->tm_hour << ":" << ESTformat->tm_min << ":" << ESTformat->tm_sec << "|" << std::endl;

    strftime(buffer, 80, "%F %T", ESTformat);

    std::string formattedTime(buffer);

    return formattedTime;
}

std::string SystemTimeManager::UNIXtoUTC()
{
    UTCformat = gmtime(&intTime);
    char buffer[80];

    // std::cout << "|" << UTCformat->tm_year << "-" << UTCformat->tm_mon << "-" << UTCformat->tm_mday << " " << UTCformat->tm_hour << ":" << UTCformat->tm_min << ":" << UTCformat->tm_sec << "|" << std::endl;

    strftime(buffer, 80, "%F %T", UTCformat);

    std::string formattedTime(buffer);

    return formattedTime;
}

long SystemTimeManager::getTime()
{
    long t = static_cast<long>(intTime);
    return t;
}