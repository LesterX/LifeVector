/**
 * @file UserVisitInfo.h
 * @author Rukun Wang (rwang264@uwo.ca)
 * @brief Class holding all the squashed and processed user 
 * visit information
 * @version 0.1
 * 
 */
#ifndef USER_VISIT_INFO_H
#define USER_VISIT_INFO_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "SystemTimeManager.h"

class UserVisitInfo
{
  private:
    int visitFrequency;
    long totalVisitDuration;
    std::map<long, int> timeLog;

  public:
    /**
     * @brief Construct a new User Visit Info object
     * 
     */
    UserVisitInfo();

    /**
     * @brief Destroy the User Visit Info object
     * 
     */
    ~UserVisitInfo();

    /**
     * @brief adds a single instance of squashed data into the 
     * object map
     * 
     * @param time_stamp long - start time when reached location 
     * in unix time format 
     * @param time_spent int - time spent at the at instance in
     * seconds
     */
    void addSingleLog(long time_stamp, int time_spent);
    bool updateLog(UserVisitInfo log);

    // Getters:
    std::map<long, int> getTimeLog();
    int getVisitFrequency();
    int getTotalTimeSpent();

    std::string beautify();
    void printLog();
};

#endif