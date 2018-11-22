#ifndef VISITATION_INFORMATION_H
#define VISITATION_INFORMATION_H

#include <string>
#include <iostream>
#include <map>

#include "VisitTime.h"

class VisitationInformation
{
  private:
    std::map<long, int> timesVisited;
    int visitFrequency;
    long totalTimeSpent;

  public:
    /* Constructor & Deconstructor */
    VisitationInformation();
    ~VisitationInformation();

    // Incrementor
    void addInstance(VisitTime newVisitInstance);

    /* Getters */
    int getFrequency();
    long getTotalTime();
    std::map<long, int> getFullVisitList();
    std::map<long, int> getVisitsFrom(long startTime, long endTime);
    VisitTime getFirst();
    VisitTime getMostRecent();
};

#endif