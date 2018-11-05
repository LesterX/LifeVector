#include "UtilityMenu.h"
using namespace std;
/*Runs infinite loop that can only be broken by an exit*/
UtilityMenu::UtilityMenu(){
    while (true){
        runUtility();
    }
}

/*Runs within an infinite loop and runs a loop for input validation and creating utility objects*/
void UtilityMenu::runUtility (){
    bool correctCommand = true;
    while (correctCommand){
        /*Provide user with information*/
        cout << "\n\n\nPlease enter one of the following characters:\n";
        cout << "o for the operating system details\n";
        cout << "m for available and total memory\n";
        cout << "n for a list of network interfaces\n";
        cout << "l for a list of processes\n";
        cout << "p for processor information\n";
        cout << "s for the system hostname\n";
        cout << "e to exit this utility menu\n\n" << endl;
        cin >> command;
        /*Error check for strings > 1*/
        if (command.size() > 1){
            cout << "More than one character was entered please try again.\n\n";
            break;
        }
        /*Select first char in string and compare using upper and lower case characters*/
        switch (command[0]){
            case 'o':
            case 'O':
                {
                    OSDetails osDets;
                    cout << DIVIDER + DIVIDER + DIVIDER;
                    cout << osDets << DIVIDER + DIVIDER + DIVIDER << "\n\n\n" << endl;
                    break;
                }
            case 'm':
            case 'M':
                {
                    MemoryInfo memInfo;
                    cout << DIVIDER + DIVIDER + DIVIDER;
                    cout << memInfo << DIVIDER + DIVIDER + DIVIDER << "\n\n\n" << endl;
                    break;
                }
            case 'n':
            case 'N':
                {
                    InterfaceList interfaceList;
                    cout << DIVIDER + DIVIDER + DIVIDER;
                    cout << interfaceList << DIVIDER + DIVIDER + DIVIDER << "\n\n\n" << endl;
                    break;
                }

            case 'l':
            case 'L':
                {
                    ProcessList procList;
                    cout << DIVIDER + DIVIDER + DIVIDER;
                    cout << procList << DIVIDER + DIVIDER + DIVIDER << "\n\n\n" << endl;
                    break;
                }
            case 'p':
            case 'P':
                {
                    ProcessorInfo procInfo;
                    cout << DIVIDER + DIVIDER + DIVIDER;
                    cout << procInfo << DIVIDER + DIVIDER + DIVIDER << "\n\n\n" << endl;
                    break;
                }
            case 's':
            case 'S':
                {
                    SystemHostname sysHost;
                    cout << DIVIDER + DIVIDER + DIVIDER;
                    cout << sysHost << DIVIDER + DIVIDER + DIVIDER << "\n\n\n" << endl;
                    break;
                }
            case 'e':
            case 'E':
                {
                    exit(0);
                    break;
                }
            default:
                {
                    cout << "Incorrect character entered please try again.\n\n" << endl;
                    correctCommand = false;
                    break;
                }
        }

    }
}

