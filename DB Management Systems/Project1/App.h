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
    string exhibitorName = "";          //This will store the current exhibitor
    string currAttendeeName = "";       //This will store the current attendee



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

    void exhibitManagerMenu();      //Main exhibit manager menu

    void exhibitMenu();
    void registerNewExhibit();      //Manager register
    void viewExhibits();            //Manager view
    void deleteExhibit();           //Manager delete

    //Needing functions for these manager operations:
    
    //Booths
    void boothMenu();               //Menu where manager can change booth
    void assignBoothLocations();    //Assign booth locations
    void deleteBoothLocations();    //Delete booth locations    
    void viewBoothLocations();      //List booth locations
    
    //Services
    void servicesMenu();            //Menu where manager can change booth services
    void assignBoothServices();        
    void deleteBoothServices();
    void viewBoothServices();
    
    
    //Attendees
    void attendeeManagerMenu();     //Manager can change attendees for exhibitor
    void managerRegisterAttendee();
    void managerDeleteAttendee();
    void managerSearchAttendee();   //Search for attendee based on a certain criteria
    
    //Inventory
    void inventoryMenu();           //Manager can change inventory for an exhibitor
    void addInventory();
    void deleteInventory();
    void viewInventory();
    



//----------------Exhibitor Menu Functions-------------------//

    void exhibitorMenu(); //main menu
    void exhibitorExhibitbyName(); //show table of exhibits depending on exhibitor
    void exhibitorNumAttendees(); //show table of all attenddess that have visited
    
    void invoiceCalculator(); //calculates invoice given exhibitor
    void showTotalRevenue(); //add up all the fees
    
    void addAttendee();     //Adds attendees for given exhibitor
    void deleteAttendee();  //Deletes attendee for given exhibitor
    

//----------------Attendee Menu Funcitons--------------------//

    void attendeeMenu();
    void attendeeBoothInfo();
    void attendeeBooths();
    void attendeeName();
    //add other attendee stuff





