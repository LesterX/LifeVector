#include "../StringParser.h"

#include "../Database.h"
#include "../UserController.h"

// All Archive Classes
#include "../UserVisitInfo.h"
#include "../VisitLog.h"
#include "../LocationInformation.h"
#include "../CoordinateInformation.h"
#include "../ArchivedLocation.h"
#include "../ArchiveLibrary.h"

#include "../googleAPI.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <cmath>

Database add_database_entries()
{
    // init local db and add test entries
    Database db;
    db.initDB("localhost", "server", "LifeVector123", "LifeVector");

    db.exeSQL("DELETE FROM VisitLog WHERE locationID = 114;");

    db.exeSQL("INSERT INTO VisitLog (visitTime, locationID, duration, username, deviceID) VALUES (1543183200, 114, 900, 'usr1', 'nx5');");

    db.exeSQL("INSERT INTO VisitLog (visitTime, locationID, duration, username, deviceID) VALUES (1540519559, 114, 1800, 'usr1', 'nx5');");

    db.exeSQL("INSERT INTO VisitLog (visitTime, locationID, duration, username, deviceID) VALUES (1542337559, 114, 3000, 'usr1', 'nx5');");

    std::cout << "VisitLog Insert Successful" << std::endl;

    return db;
}

int main()
{
    using namespace std;

    UserController uc("server", "LifeVector123");
    uc.getDBConnection()->exeSQL("DELETE FROM User;");

    uc.createUser("usr1", "nx5", "LV123");
    uc.createUser("main_usr", "nx5", "archve");
    // uc.~UserController();

    // Location Archiver Tests

    LocationInformation l(200);
    l.setName("Thompson Arena");
    l.setAddress("Western University, Lambton Drive, Stoneybrook Gardens, London, Middlesex County, Ontario, N6G 5K8, Canada");
    l.setDescription("sports centre");

    cout << "LocInfo: \n"
         << l.getID() << " - has been created.\n"
         << l.getAddress() << "\n"
         << l.getName() << "\n"
         << l.getDescription()
         << endl;

    double x = 43.00307, y = -81.27547;
    double n = 43.00341, w = -81.27605, s = 43.00268, e = -81.27488;
    CoordinateInformation c(x, y);
    c.setLimits(n, s, e, w);

    cout << "Coordinate Object created" << endl;

    ArchivedLocation archL(l.getID(), x, y, n, s, e, w);
    archL.setLocationInformation(l.getName(), l.getAddress(), l.getDescription());

    cout << "ArchivedLocation object created: archL : " << endl;
    archL.printInformation();

    // Log class tests

    UserVisitInfo uvi;
    uvi.addSingleLog(1543183200, 900);
    uvi.addSingleLog(1540519559, 3000);
    uvi.addSingleLog(1542337559, 6000);

    cout << "UserVisitInfo object created : uvi" << endl;
    uvi.printLog();

    VisitLog vl;
    bool check = false;

    string uID = "usr1/nx5";

    if (vl.userFound(uID))
    {
        check = vl.addFullLog(uID, uvi);
    }
    else
    {
        if (vl.addNewUser(uID))
        {
            check = vl.addFullLog(uID, uvi);
        }
    }

    cout << "VisitLog vl is populated with uvi - " << check << endl;

    UserVisitInfo uvi2;

    uvi2.updateLog(uvi);

    // Archive Library Test
    cout << "~~~~~ Testing Library ~~~~~" << endl;
    ArchiveLibrary TestLibrary(uc.getDBConnection());
    uc.getDBConnection()->exeSQL("DELETE FROM ArchivedLocations;");

    // single instance
    cout << "add from above" << endl;
    
    TestLibrary.saveLocationToDatabase(archL);
    ArchivedLocation *frmDB_l = (ArchivedLocation *)malloc(sizeof(ArchivedLocation));
    TestLibrary.getLocationFromDatabase(frmDB_l, 200);
    cout << frmDB_l->getID() << endl;
    TestLibrary.archiveUserLog(200, "usr1", "nx5", uvi);

    cout << "loc 200 added with log" << endl;

    // Add a location
    string loc_name, address, desc;
    int loc_id = 400, id[4], temp = 3, cnt = 0;
    double x_ref, y_ref, n_border, e_border, s_border, w_border;

    // create some locations:
    string lat[4] = {"43.009005", "43.005586", "43.642571", "43.653440"};
    string lng[4] = {"-81.269028", "-81.276231", "-79.387057", "-79.384094"};

    // add 4 locations
    for (; cnt < 4; cnt++)
    {
        // get info from google API
        googleAPI google(lat[cnt], lng[cnt]);
        loc_name = google.getName();
        address = google.getFormattedLocation();

        int azero = 0;
        desc = google.getTypes(azero);

        x_ref = atof(google.getLat().c_str());
        y_ref = atof(google.getLng().c_str());

        n_border = atof(google.getNorthEastLat().c_str());
        e_border = atof(google.getNorthEastLng().c_str());
        s_border = atof(google.getSouthWestLat().c_str());
        w_border = atof(google.getSouthWestLng().c_str());

        // create ArchiveLocation
        ArchivedLocation loca_loca = TestLibrary.constructLocation(loc_id, loc_name, address, desc, x_ref, y_ref, n_border, s_border, e_border, w_border);
        id[cnt] = loc_id;

        // print whats found
        loca_loca.printInformation();

        // save to database
        TestLibrary.saveLocationToDatabase(loca_loca);

        if (loc_id == loca_loca.getID())
        {
            cout << "new location added to DB" << endl;
            id[cnt] = loca_loca.getID();
            cout << "here: " << cnt << ", id " << id[cnt] << endl;
        }

        // make new id
        loc_id += temp;

        cout << "check - reached" << endl;
    }

    cout << " 4 locations archived" << endl;

    // create some time logs;
    int interval = 5 * 60; // tracking interval 5min => 300s

    // generate some logs

    cout << "inserting time logs for locations: " << endl;

    UserVisitInfo u1;
    u1.addSingleLog(1538745600, (4 * interval));  // 2018-10-05 09:20:00, 20min
    u1.addSingleLog(1538756100, (20 * interval)); // 2018-10-05 12:15:00, 100min
    u1.addSingleLog(1539895800, (15 * interval)); // 2018-10-18 16:50:00, 75min

    UserVisitInfo u2;
    u2.addSingleLog(1540039500, (45 * interval)); // 2018-10-20 08:45:00, 225min
    u2.addSingleLog(1540831500, (25 * interval)); // 2018-10-29 12:45:00, 125min

    UserVisitInfo u3;
    u3.addSingleLog(1542767520, (31 * interval)); // 2018-11-20 21:32:00, 155min

    UserVisitInfo u4;
    u4.addSingleLog(1541472300, (48 * interval)); // 2018-11-5 21:45:00, 240min

    cout << "t_log populated" << endl;

    //get locations from DB

    cout << "the incredible loop (id : 200 - 450)" << endl;

    cnt = 0;
    for (temp = 200; temp < 450; temp++)
    {
        void *found = (ArchivedLocation *)malloc(sizeof(ArchivedLocation *));

        if (TestLibrary.getLocationFromDatabase(((ArchivedLocation *)found), temp))
        {
            if (cnt < 4)
            {
                id[cnt] = ((ArchivedLocation *)found)->getID();
                cout << "here: " << cnt << ", id " << id[cnt] << endl;
                cnt++;

                ((ArchivedLocation *)found)->printInformation();
            }
        }

        free(found);
    }

    // add the logs to the 4 locations
    temp = 0;
    UserVisitInfo userlogs[4] = {u1, u2, u3, u4};
    for (; temp < 4; temp++){
        TestLibrary.archiveUserLog(id[temp], "main_usr", "nx5", userlogs[temp]);
    }
    
    cout << "logs archived to related locations" << endl;

    // get and print log information for each location
    for (temp = 0; temp < 4; temp++)
    {
        void *found = (ArchivedLocation *)malloc(sizeof(ArchivedLocation *));

        if (TestLibrary.getLocationFromDatabase(((ArchivedLocation *)found), id[temp]))
        {
            ((ArchivedLocation *)found)->printInformation();

            // User Log
            std::map<int, UserVisitInfo> *u_log = new std::map<int, UserVisitInfo>();
            TestLibrary.getUserLogFromDatabase(u_log, "main_usr", "nx5");
            map<int, UserVisitInfo>::iterator uit = u_log->begin();

            for (uit; uit != u_log->end(); ++uit)
            {
                cout << "User at " << uit->first << endl;
                uit->second.printLog();
                free(u_log);
            }

            // Location Log
            void *vlog = (VisitLog *)malloc(sizeof(VisitLog *));
            TestLibrary.getLocationRecordFromDatabase((VisitLog *)vlog, ((ArchivedLocation *)found)->getID());
            ((VisitLog *)vlog)->printLog();
            free(vlog);

            // Visit count function test
            int l_count = TestLibrary.getVisitCount(((ArchivedLocation *)found)->getID());
            int lu_count = TestLibrary.getVisitCount(((ArchivedLocation *)found)->getID(), "main_usr", "nx5");

            if (l_count == lu_count)
            {
                cout << "count functions test passed: " << l_count << endl;
            }

            // Duration function test
            int dur = TestLibrary.getDurationAtLocation(((ArchivedLocation *)found)->getID());
            int udur = TestLibrary.getDurationAtLocation(((ArchivedLocation *)found)->getID(), "main_usr", "nx5");

            if (dur == udur)
            {
                cout << "duration functions test passed : " << dur << endl;
            }
        }

        free(found);
    }

    cout << "end of test" << endl;
}
