#include "VisitationInformation.h"

// Constructs new instance of VisitationInformation. Defaults with no visits (visitFrequency = 0) and no time spent (totalTimeSpent = 0)
VisitationInformation::VisitationInformation()
{
    timesVisited = std::map<long, int>();

    visitFrequency = 0;
    totalTimeSpent = 0;
}

VisitationInformation::~VisitationInformation() {}

// Inserts a new visit instance to the timesVisited vector. Generated through GPS Squashing Process
void VisitationInformation::addInstance(VisitTime newVisitInstance)
{
    timesVisited.emplace(newVisitInstance.getTimestamp(), newVisitInstance.getDuration());

    visitFrequency++;

    totalTimeSpent += newVisitInstance.getDuration();
}

int VisitationInformation::getFrequency()
{
    return visitFrequency;
}

long VisitationInformation::getTotalTime()
{
    return totalTimeSpent;
}

std::map<long, int> VisitationInformation::getFullVisitList()
{
    return timesVisited;
}

VisitTime VisitationInformation::getFirst()
{
    std::map<long, int>::iterator first = timesVisited.begin();
    VisitTime output(first->first, first->second);
    return output;
}

VisitTime VisitationInformation::getMostRecent()
{
    std::map<long,int>::reverse_iterator recent = timesVisited.rbegin();
    VisitTime output(recent->first, recent->second);
    return output;
}

// Retrieve List of times visited between a time range, range is provided in UNIX time
std::map<long, int> VisitationInformation::getVisitsFrom(long startTime, long endTime)
{
    // duplicate map to output
    std::map<long, int> output = timesVisited;

    // find the bounds for the time range provided
    std::map<long, int>::iterator lower, upper;
    lower = output.lower_bound(startTime); // lower >= startTime
    upper = output.upper_bound(endTime); // upper > endTime

    // remove entries outside of specified range
    output.erase(output.begin(), lower); // removes [first, startTime)
    output.erase(upper, output.end());   // removes [endTime+1, end)
    
    return output;
}