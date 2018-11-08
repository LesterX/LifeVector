/**
 * cpp file for user class which contains getters and setters
 */

#include "user.h"

using namespace std;

// Constructors

// New user - no report or times
User::User(std::string username, std::string deviceID, std::string hash, std::string salt)
{
    self_username = username;
    self_deviceID = deviceID;
    self_hash = hash;
    self_salt = salt;
    self_syncTime = 0;
    self_reportTime = 0;
    self_report = NULL;
}

// Full user initialization
User::User(std::string username, std::string deviceID, std::string hash, std::string salt, json report, int syncTime, int reportTime)
{
    self_username = username;
    self_deviceID = deviceID;
    self_hash = hash;
    self_salt = salt;
    self_report = report;
    self_syncTime = syncTime;
    self_reportTime = reportTime;
}

// Barebone initialization
User::User(string username, string deviceID)
{
    self_username = username;
    self_deviceID = deviceID;
    self_hash = "";
    self_salt = "";
    self_report = "";
    self_syncTime = 0;
    self_reportTime = 0;
}

// Destructor
User::~User() {}

// Getters:
string User::getUsername()
{
    return self_username;
}

string User::getDeviceID()
{
    return self_deviceID;
}
string User::getHash()
{
    return self_hash;
}
string User::getSalt()
{
    return self_salt;
}
json User::getReport()
{
    return self_report;
}
long User::getSyncTime()
{
    return self_syncTime;
}
long User::getReportTime()
{
    return self_reportTime;
}

// Setters:
void User ::setUsername(string username)
{
    self_username = username;
}
void User ::setDeviceID(string deviceID)
{
    self_deviceID = deviceID;
}
void User ::setHash(string hash)
{
    self_hash = hash;
}
void User ::setSalt(string salt)
{
    self_salt = salt;
}
void User::setReport(json report)
{
    self_report = report;
}
void User ::setSyncTime(long syncTime)
{
    self_syncTime = syncTime;
}
void User ::setReportTime(long reportTime)
{
    self_reportTime = reportTime;
}
