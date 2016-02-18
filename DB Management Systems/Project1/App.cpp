#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
#include "DBsystem.h"

using namespace std;

//UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
//UPDATE animals SET Spot = "Max" WHERE age > 5;

int int_input = 0;
string str_input = "";

void mainMenu()
{
	cout << "[Convention Exhibit Management System]\n" << endl;
	cout << "Select user interface:" << endl;
	cout << "   1. Exhibit Manager" << endl;
	cout << "   2. Exhibitor" << endl;
	cout << "   3. Attendees\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;
	cout << endl;
	switch(int_input)
	{
		case 1:
			mainMenu();
			break;
		case 2:
			mainMenu();
			break;
		case 3:
			return;
			break;
		default:
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "***Not a valid command, try again***" << endl;
			mainMenu();
			break;
	}

}

int main()
{	
	DBsystem db;
	try{
		
		//mainMenu();
		db.DBParser.sendNewInput("OPEN CEMS;");
    	db.execute(); 
    	//db.DBParser.contain.clear(); 
		db.DBParser.sendNewInput("SHOW CEMS;");
    	db.execute();
		
		
    	/*while(1)
    	 {
    		string input0;
    		cout<<"Size of Map: "<<db.database.size()<<endl;
    		for (map<string,Table*>::iterator it = db.database.begin(); it!=db.database.end(); ++it)
    			cout<<it->first << '\n';
    	 	cout<<"What is the command?"<<endl;
    	 	getline (cin,input0); //take the command
    	 	if(input0.compare("") == 0) continue;
    	 	db.DBParser.sendNewInput(input0);
    	 	db.execute(); //not implemented yet but will take the command and use switch statement to know what to run
    	 	db.DBParser.contain.clear(); //Not implementted yet but will reset all things in container to 0
    	 	
    	 	
    	 }*/
	
	}
	catch(...)
	{
		cout << "Please try again: " << endl;
	}
	

}