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
    string tables[5] = {"exhibitors","exhibitorsBooths","services","attendees","inventory"};
	string verificationTables[3] = { "managerCredentials","exhibitorsCredentials","attendeesCredentials" }; //for access level

    int int_input;
    string str_input = "";
    string ManagerPW = "asdf";
    string exhibitorName = "";          //This will store the current exhibitor
    string currAttendeeName = "";       //This will store the current attendee
    
    double revenue = 0;


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
    void registerNewExhibit();      //Manager register menu
    void viewExhibits();            //Manager view menu
    void deleteExhibit();           //Manager delete menu
    int managerSearchExhibits();    //Function that actually searches exhibits
    
    //Needing functions for these manager operations:
    
    //Booths
    void boothMenu();               //Menu where manager can change booth
	void createBoothLocation();     //Create a booth
    void assignBoothLocations();    //Assign booth locations
    void deleteBoothLocations();    //Delete booth locations    
    void viewBoothLocationsMenu();  //Menu for viewing booths
	void showAllBooths();			//List all booths
	void searchBoothMenu();			//search by criteria
    
    //Services
    void servicesMenu();            //Menu where manager can change booth services
    void assignBoothServices();        
    void deleteBoothServices();
    void viewBoothServices();
    
    
    //Attendees
    void attendeeManagerMenu();     //Manager can change attendees for exhibitor
    void managerRegisterAttendee();
    void managerDeleteAttendee();
    void managerSearchAttendee();   //Menu for searching for an attendee based on a certain criteria
    int managerSearchAttendees();   //Function that does the searching
    
    //Inventory
    void inventoryMenu();           //Manager can change inventory for an exhibitor
    void addInventory();
    void deleteInventory();
    void viewInventory();
    
    
    //Revenue
    void showTotalRevenue();        //add up all the fees
    



//----------------Exhibitor Menu Functions-------------------//

    void exhibitorMenu(); //main menu
    void exhibitorExhibitbyName(); //show table of exhibits depending on exhibitor
    void exhibitorNumAttendees(); //show table of all attenddess that have visited
    void invoiceCalculator(); //calculates invoice given exhibitor
    
    //void addAttendee();     //Decided that only the manager can do this
    //void deleteAttendee();  //Decided that only the manager can do this
    

//----------------Attendee Menu Funcitons--------------------//

    void attendeeMenu();
    void attendeeBoothInfo();
    void attendeeBooths();
    void attendeeName();
    //add other attendee stuff





