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

    std::set<std::string> userLog;
    std::map<std::string, UserVisitInfo> userVisitRecord;

    // Helpers:
    void updateCounters(UserVisitInfo log_entry);

  public:
    // Constructor
  VisitLog();

  // Destructor
  ~VisitLog();

  // Setters & Adders:
  bool addNewUser(std::string userID);
  bool addFullLog(std::string userID, UserVisitInfo log);
  bool addSingleEntry(std::string userID, long time, int duration);

  // Getters:
  std::map<std::string, UserVisitInfo>::iterator getUserVisitInformation(std::string usernID);
  std::set<std::string>::iterator findUser(std::string userID);
  std::set<std::string> getVisitUsers();
  int getTotalTimesVisited();
  int getTotalTimeSpent();

  // Time Bound Getters:

  // bool checkers:
  bool userFound(std::string userID);
};

#endif