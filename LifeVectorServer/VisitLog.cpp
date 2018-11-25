#include "VisitLog.h"

VisitLog::VisitLog()
{
    visitCount = durationSpent = 0;
    userLog = std::set<std::pair<std::string, std::string>>();
    userVisitationLog = std::map<std::pair<std::string, std::string>, UserVisitInfo>();
}

VisitLog::~VisitLog() {}

/* -------------------------------------------------------------------------- */

// Helpers:
std::pair<std::string, std::string> VisitLog::to_pair(std::string username, std::string deviceID)
{
    return std::make_pair(username, deviceID);
}

void VisitLog::updateTotals(UserVisitInfo log_entry)
{
    visitCount += log_entry.getVisitFrequency();
    durationSpent += log_entry.getTotalTimeSpent();
}

// Getters:
std::set<std::pair<std::string, std::string>>::iterator VisitLog::findUser(std::string username, std::string deviceID)
{
    return userLog.find(to_pair(username, deviceID));
}

std::map<std::pair<std::string, std::string>, UserVisitInfo>::iterator VisitLog::getUserVisitInformation(std::string username, std::string deviceID)
{
    return userVisitationLog.find(to_pair(username, deviceID));
}

int VisitLog::getTotalTimesVisited()
{
    return visitCount;
}

int VisitLog::getTotalTimeSpent()
{
    return durationSpent;
}

// Setters & Adders:
bool VisitLog::addNewUser(std::string username, std::string deviceID)
{
    // insertion checks
    std::pair<std::set<std::pair<std::string, std::string>>::iterator, bool> check;
    std::pair<std::map<std::pair<std::string, std::string>, UserVisitInfo>::iterator, bool> map_check;

    // add user to userLog
    check = userLog.insert(to_pair(username, deviceID));

    //check if user present
    if (check.second) // new user added successfully
    {
        UserVisitInfo blank_entry(); // empty log to insert
        map_check = userVisitationLog.emplace(to_pair(username, deviceID), blank_entry);

        return map_check.second;
    }
    else
    {
        return check.second;
    }
}

bool VisitLog::addNewLog(std::string username, std::string deviceID, UserVisitInfo log)
{
    std::map<std::pair<std::string, std::string>, UserVisitInfo>::iterator target;

    target = getUserVisitInformation(username, deviceID);
    UserVisitInfo *entry = &(target->second);

    bool is_updated = entry->updateLog(log);

    if (is_updated)
    {
        updateTotals(*entry);
    }

    return is_updated;
}