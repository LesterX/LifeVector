#include "UserVisitInfo.h"

UserVisitInfo::UserVisitInfo()
{
    visitFrequency = 0;
    totalVisitDuration = 0;

    timeLog = std::map<long, int>();
}

UserVisitInfo::~UserVisitInfo() {}

// New Visit
void UserVisitInfo::addSingleLog(long time_stamp, int time_spent)
{
    timeLog.emplace(time_stamp, time_spent);

    visitFrequency++;
    totalVisitDuration += time_spent;
}

bool UserVisitInfo::updateLog(UserVisitInfo log)
{
    int initial_count = visitFrequency, initial_duration = totalVisitDuration;
    std::map<long, int>::const_iterator it;

    for (it = log.getTimeLog().begin(); it != log.getTimeLog().end(); ++it)
    {
        timeLog.emplace(it->first, it->second);

        visitFrequency++;

        totalVisitDuration += it->second;
    }

    if ((visitFrequency - initial_count == log.getVisitFrequency()) && (totalVisitDuration - initial_duration == log.getTotalTimeSpent()))
    {
        std::cout << "User Visiting Information Updated Successfully." << std::endl;
        return true;
    }
    else
    {
        std::cout << "User Visiting Information Update Failed" << std::endl;
        return false;
    }
}

// Getters:
int UserVisitInfo::getVisitFrequency()
{
    return visitFrequency;
}

int UserVisitInfo::getTotalTimeSpent()
{
    return totalVisitDuration;
}

std::map<long, int> UserVisitInfo::getTimeLog()
{
    return timeLog;
}