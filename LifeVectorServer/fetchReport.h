#ifndef FETCHREPORT_H
#define FETCHREPORT_H

#include "json.hpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include "StringParser.h"
#include <sstream> 
#include <vector>

#include "Database.h"
#include "UserController.h"
#include "VisitLog.h"

#include "json.hpp"

#include "UserVisitInfo.h"
#include "LocationInformation.h"
#include "CoordinateInformation.h"
#include "ArchivedLocation.h"
#include "ArchiveLibrary.h"

#include "googleAPI.h"

#include <iostream>
#include <utility>
#include <cmath>
#include <stdlib.h>


class fetchReport
{
  private:

    nlohmann::json report;

    Database *connect_db;

  public:
  // Constructor
  fetchReport();   
  // Destructor
  ~fetchReport();

  void process(VisitLog *visitL, Database *db_connect, int loc_id);
  
  nlohmann::json getReport();



};

#endif

