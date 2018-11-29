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

    VisitLog *vl;

    int totalD;

 

  public:
  // Constructor
  fetchReport();   
  // Destructor
  ~fetchReport();

  void process(VisitLog *visitL, int d);
  
  nlohmann::json getReport();



};

#endif

