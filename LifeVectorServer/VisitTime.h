/* 
* This class holds is for the collated GPS coordinate data. 
* "initialTimeStamp" holds the time (in UNIX format)
* when the associated location was first frequented
* "duration" is the time spent at the associated location
*/
#ifndef VISITTIME_H
#define VISITTIME_H

class VisitTime
{
public:
  // constructor
  VisitTime(long startTime);

  // destructor
  ~VisitTime();

  // Setters
  void setDuration(int durationTime);
  void extendDuration(int moreTime);

  // Getters
  long getTimestamp();
  int getDuration();

private:
  long initialTimeStamp; // stores time in UNIX time format
  int duration;
};

#endif