/**
 * @file VisitLog.h
 * @brief Storing the visiting information at each time stamp
 * 
 */

#ifndef VISIT_LOG_H
#define VISIT_LOG_H

#include <map>
#include <utility>
#include <set>
#include <vector>
#include <string>
#include <sstream>

#include "UserVisitInfo.h"
#include "StringParser.h"

class VisitLog
{
  private:
    int visitCount, durationSpent;

    std::set<std::string> userLog;
    std::map<std::string, UserVisitInfo> userVisitRecord;

    /**
     * @brief Helper method
     * 
     * @param log_entry 
     */
    void updateCounters(UserVisitInfo log_entry);

  public:
  /**
   * @brief Construct a new Visit Log object
   * 
   */
  VisitLog();

  /**
   * @brief Destroy the Visit Log object
   * 
   */
  ~VisitLog();

  /**
   * @brief Add new user 
   * 
   * @param userID 
   * @return true Created
   * @return false Not created
   */
  bool addNewUser(std::string userID);

  /**
   * @brief Add visiting log
   * 
   * @param userID 
   * @param log 
   * @return true Log added
   * @return false Not added
   */
  bool addFullLog(std::string userID, UserVisitInfo log);

  /**
   * @brief Add single visiting entry
   * 
   * @param userID 
   * @param time 
   * @param duration 
   * @return true Added
   * @return false Not added
   */
  bool addSingleEntry(std::string userID, long time, int duration);

  /**
   * @brief Get the User Visit Information object
   * 
   * @param usernID 
   * @return std::map<std::string, UserVisitInfo>::iterator 
   */
  std::map<std::string, UserVisitInfo>::iterator getUserVisitInformation(std::string usernID);

  /**
   * @brief 
   * 
   * @param userID 
   * @return std::set<std::string>::iterator 
   */
  std::set<std::string>::iterator findUser(std::string userID);

  /**
   * @brief 
   * 
   * @return std::set<std::string> 
   */
  std::set<std::string> getVisitUsers();

  /**
   * @brief Get the Total Times Visited 
   * 
   * @return int 
   */
  int getTotalTimesVisited();

  /**
   * @brief Get the Total Time Spent 
   * 
   * @return int 
   */
  int getTotalTimeSpent();

  /**
   * @brief 
   * 
   * @param userID 
   * @return true Found
   * @return false Not found
   */
  bool userFound(std::string userID);

  /**
   * @brief 
   * 
   * @return std::string 
   */
  std::string beautify();

  /**
   * @brief 
   * 
   */
  void printLog();
};

#endif