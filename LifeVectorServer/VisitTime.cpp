#include "VisitTime.h"

VisitTime::VisitTime(long startTime)
{
    initialTimeStamp = startTime;
    duration = DEFAULT_INTERVAL; // this can be manually updated
                  // consider a default duration for 1 instance
}

VisitTime::VisitTime(long startTime, int initDuration)
{
    initialTimeStamp = startTime;
    duration = initDuration;
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

void VisitTime::extendDuration()
{
    duration += DEFAULT_INTERVAL;
}

long VisitTime::getTimestamp()
{
    return initialTimeStamp;
}

int VisitTime::getDuration()
{
    return duration;
}