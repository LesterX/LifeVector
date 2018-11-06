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
  long initialTimeStamp;
  int duration;
};

#endif