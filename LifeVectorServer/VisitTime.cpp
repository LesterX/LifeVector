#include "VisitTime.h"

VisitTime::VisitTime(long startTime)
{
    initialTimeStamp = startTime;
    duration = 0; // this can be manually updated
                  // consider a default duration for 1 instance
}

/*
* This function is to set a definitive duration
*/
void VisitTime::setDuration(int durationTime)
{
    duration = durationTime;
}

/*
* This function builds on the setDuration function, 
* allowing for incrementation of the duration
*/
void VisitTime::extendDuration(int moreTime)
{
    duration += moreTime;
}

long VisitTime::getTimestamp()
{
    return initialTimeStamp;
}

int VisitTime::getDuration()
{
    return duration;
}