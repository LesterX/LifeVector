#include "../UserController.h"
#include "../json.hpp"

int main()
{

    string username = "John Smith";
    string devID = "nexus5";
    string password = "1234";
    nlohmann::json report = {
        {"key1_1", "value1_1"},
        {"key1_2", "value1_2"}};

    cout << "Attempting to Connect to Database" << endl;
    UserController uc("server", "LifeVector123");
    cout << "Connected to Database" << endl;

    cout << "Creating New User: John Smith" << endl;
    if (uc.createUser(username, devID, password))
    {
        cout << "User " << username << "created";
    }
    else
    {
        cout << "Unable to create user" << username << endl;
    }

    cout << "Updating json report structure in database" << endl;
    if (uc.updateReport(username, devID, report))
    {
        cout << "Report updated for " << username << endl;
    }

    nlohmann::json *reportFromDB = new json();
    
    if (uc.fetchReport(reportFromDB, username, devID))
    {
        cout << "Report: " << endl
             << *reportFromDB << endl;
    }

    cout << "Testing hash function and hash reproducibility" << endl;
    if (uc.compareUserHash(username, devID, password))
    {
        cout << "Hash matched" << endl;
    }
    else
        cout << "Hash not matched" << endl;

    // test raw data uploader

    cout << "Save sample gps data file from file to database" << endl
         << "File: ./SampleFiles/sample_coordinates.json:" << endl;
    RawDataRepository sampledata("./SampleFiles/sample_coordinates.json", "gps_coordinates_dump");
    sampledata.dumpData();

    if (uc.saveRawGPStoDB("John Smith", "nexus5", sampledata))
    {
        cout << "Sample Tracking data from sample_coordinates.json from nexus5 saved to database" << endl;
    }
    else
    {
        cout << "GPS Save Failed." << endl;
    }

    cout << "Delete User" << endl;
    if (uc.deleteUser(username, devID))
    {
        printf("User deleted\n");
    }
    else
    {
        printf("Unable to delete user\n");
    }

    return 0;
}
