#ifndef USER_VISIT_INFO_H
#define USER_VISIT_INFO_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "SystemTimeManager.h"

class UserVisitInfo
{
  private:
    int visitFrequency;
    long totalVisitDuration;
    std::map<long, int> timeLog;

  public:
    // Constructor:
    UserVisitInfo();

    // Destructor:
    ~UserVisitInfo();

    // Adding new visits
    void addSingleLog(long time_stamp, int time_spent);
    bool updateLog(UserVisitInfo log);

    // Getters:
    std::map<long, int> getTimeLog();
    int getVisitFrequency();
    int getTotalTimeSpent();

    std::string beautify();
    void printLog();
};

#endif