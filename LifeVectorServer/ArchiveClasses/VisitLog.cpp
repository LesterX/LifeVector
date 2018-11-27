#include "VisitLog.h"

VisitLog::VisitLog()
{
    visitCount = durationSpent = 0;
    userLog = std::set<std::string>();
    userVisitRecord = std::map<std::string, UserVisitInfo>();
}

VisitLog::~VisitLog() {}

/* -------------------------------------------------------------------------- */

// Helpers:
void VisitLog::updateCounters(UserVisitInfo log_entry)
{
    visitCount += log_entry.getVisitFrequency();
    durationSpent += log_entry.getTotalTimeSpent();
}

// Checkers:
bool VisitLog::userFound(std::string userID)
{
    std::set<std::string>::iterator target = findUser(userID);

    // if iterator not pointing to end, then a user was found;
    return (target != userLog.end());
}

// Getters:
std::set<std::string>::iterator VisitLog::findUser(std::string userID)
{
    return userLog.find(userID);
}

std::map<std::string, UserVisitInfo>::iterator VisitLog::getUserVisitInformation(std::string userID)
{
    return userVisitRecord.find(userID);
}

int VisitLog::getTotalTimesVisited()
{
    return visitCount;
}

int VisitLog::getTotalTimeSpent()
{
    return durationSpent;
}

std::set<std::string> VisitLog::getVisitUsers()
{
    return userLog;
}

// Setters & Adders:
bool VisitLog::addNewUser(std::string userID)
{
    if (userFound(userID))
    {
        std::cout << "User Found, don't need to add" << std::endl;
        return false;
    }
    else
    {
        UserVisitInfo blank_entry; // empty log to insert
        userVisitRecord.emplace(userID, blank_entry);
        userLog.insert(userID);
        return true;
    }
}

bool VisitLog::addFullLog(std::string userID, UserVisitInfo log)
{
    std::map<std::string, UserVisitInfo>::iterator target = getUserVisitInformation(userID);

    if (target == userVisitRecord.end())
    {
        return false;
    }

    UserVisitInfo *entry = &(target->second);
    bool is_updated = entry->updateLog(log);
    std::cout << "here" << std::endl;

    if (is_updated)
    {
        updateCounters(*entry);
    }

    return is_updated;
}

bool VisitLog::addSingleEntry(std::string userID, long time, int duration)
{
    std::map<std::string, UserVisitInfo>::iterator target = getUserVisitInformation(userID);

    if (target == userVisitRecord.end())
    {
        return false;
    }

    UserVisitInfo *entry = &(target->second);
    entry->addSingleLog(time, duration);
    return true;
}

