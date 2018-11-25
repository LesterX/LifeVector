#ifndef VISIT_LOG_H
#define VISIT_LOG_H

#include <map>
#include <utility>
#include <set>
#include <string>

#include "UserVisitInfo.h"

class VisitLog
{
  private:
    int visitCount, durationSpent;
    std::set<std::pair<std::string, std::string>> userLog;
    std::map<std::pair<std::string, std::string>, UserVisitInfo> userVisitationLog;

    // Helpers:
    std::pair<std::string, std::string> to_pair(std::string username, std::string deviceID);
    void updateTotals(UserVisitInfo log_entry);

  public:
    // Constructor
    VisitLog();

    // Destructor
    ~VisitLog();

    // Setters & Adders:
    bool addNewUser(std::string username, std::string deviceID);
    bool addNewLog(std::string username, std::string deviceID, UserVisitInfo log);

    // Getters:
    std::map<std::pair<std::string, std::string>, UserVisitInfo>::iterator getUserVisitInformation(std::string username, std::string deviceID);
    std::set<std::pair<std::string, std::string>>::iterator findUser(std::string username, std::string deviceID);
    int getTotalTimesVisited();
    int getTotalTimeSpent();

    // Time Bound Getters:
    
};

#endif