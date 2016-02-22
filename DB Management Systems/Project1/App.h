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

    int int_input;
    string str_input = "";
    string ManagerPW = "asdf";



//-----------General Menu Functions-----------//

    void mainMenu();
    void exhibitPWScreen();             //To get into exhibitorManager()
    int checkInputSize(string);
    int checkIsDigit(string);


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
    //add other attendee stuff





