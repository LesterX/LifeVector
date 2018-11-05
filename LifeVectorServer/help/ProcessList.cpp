#include "ProcessList.h"
using namespace std;


ProcessList::ProcessList() {
    readProcessDirectory(fileName, listOfProcessIDs);
    generateProcesses(listOfProcessIDs, listOfProcesses);
};

vector<ProcessInfo> ProcessList::getListOfProcesses() const {
    return listOfProcesses;
}

bool ProcessList::startsWith(const string& s, const string& prefix) {
        return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

bool ProcessList::isNotNumber(string line) {
    //checks if there are any numbers in the string
    return line.find_first_not_of("0123456789") == string::npos;
}

/*Reads the process directory to gather all the process IDs and store them in a vector of strings*/
int ProcessList::readProcessDirectory (string dir, vector<string> &fileList) {
    DIR *dp;
        struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
        //ignores hidden files and non-numeric files
        if (!startsWith(string(dirp->d_name), ".") && isNotNumber(string(dirp->d_name))){
            fileList.push_back(string(dirp->d_name));
        }
    }
    closedir(dp);
    return 0;
}

/* Vector of process IDs is used to generate individual process objects*/
void ProcessList::generateProcesses(vector<string> listOfProcessIDs, vector<ProcessInfo> &listOfProcesses){
        for(int i = 0; i < listOfProcessIDs.size() ; i++){
            ProcessInfo tempProcess(stoi(listOfProcessIDs[i]));
            listOfProcesses.push_back(tempProcess);
    }
}
ostream& operator<<(ostream& os, const ProcessList& processList){
    vector<ProcessInfo> procTemp = processList.getListOfProcesses();
    for (int i = 0; i < procTemp.size(); i ++){
        os << "\n" + string(60,'=') + "\n";//creates a string divider
        os << procTemp[i];
        os << "\n" + string(60,'=') + "\n";
    }
    return os;
}

