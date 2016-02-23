#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include <vector>
#include <sstream>
#include <map>
#include "DBsystem.h"
#include <algorithm>


//-----------Things we need---------//

    DBsystem db;
    string tables[5] = {"exhibitors","booth","services","attendees","inventory"};
	string verificationTables[3] = { "managerCredentials","exhibitorsCredentials","attendeesCredentials" }; //for access level

    int int_input;
    string str_input = "";
    string ManagerPW = "asdf";
    string exhibitorName = "";      //This will store the current exhibitor



//-----------General Menu Functions-----------//

    void mainMenu();
	int checkInputSize(string);
    int checkIsDigit(string);

//-----------Clearance Functions-----------//
	void managerPWScreen();
	void exhibitorPWScreen();
	void attendeePWScreen();
	int verifyNameAndPassword(string tableName,vector<string> IDtuples);

//-----------Exhibitor MANAGER Menu Functions-------------//

    void exhibitManagerMenu();

    void exhibitMenu();
    void registerNewExhibit();      //Manager register
    void viewExhibits();            //Manager view
    void deleteExhibit();           //Manager delete

    /*  Needing functions for these manager operations:
            Booths
            Services
            Attendees
            Inventory
    */



//-----------Exhibitor Menu Functions-------------------//

    void exhibitorMenu();
    void exhibitorExhibitbyName();
    void exhibitorNumAttendees();



//-----------Attendee Menu Funcitons--------------------//

    void attendeeMenu();
    void attendeeBoothInfo();
    void attendeeBooths();
    void attendeeName();
    //add other attendee stuff





