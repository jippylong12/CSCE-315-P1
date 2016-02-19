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

DBsystem db;
string tables[5] = {"exhibitors","booth","services","attendees","inventory"};

int int_input = 0;
string str_input = "";


void registerNewExhibit()
{
	string values[10] = {"Name","Address","contact_person","email", "phone Number","Fax Number","category","booth_personnel","org_description","org_site"};
	
	str_input = "INSERT INTO exhibitors VALUES FROM (";
	
	cout << "[Register New Exhibit]\n" << endl;
	cout << "-Enter the details of your Organization-" << endl;
	
	for(int i = 0; i < 10; i++)
	{
		string s = "";
		cout << values[i] + ": ";
		cin.ignore();
		getline(cin,s);
		
		str_input += "\"" + s + "\"";
		if(i < 9)
			str_input += ", ";
	}
	
	str_input += ");";
	
	cout << str_input << endl;
	
	db.DBParser.sendNewInput(str_input);
    db.execute(); 
	
	/*cout << endl;
	system("clear");
	switch(int_input)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			return;
			break;
		default:
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
			cout << "***Not a valid command, try again***\n" << endl;
			exhibitMenu();
			break;
	}
	
	exhibitMenu();*/

}

void exhibitMenu()
{
	
	cout << "[Exhibit Manager Menu]\n" << endl;
	cout << "   1. Register New Exhibit" << endl;
	cout << "   2. View/Search for an Exhibit(s)" << endl;
	cout << "   3. Remove an Exhibit\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;
	cout << endl;
	system("clear");
	switch(int_input)
	{
		case 1:
			registerNewExhibit();
			break;
		case 2:
			break;
		case 3:
			return;
			break;
		default:
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
			cout << "***Not a valid command, try again***\n" << endl;
			exhibitMenu();
			break;
	}
	
	exhibitMenu();

}

void exhibitManagerMenu()
{
	
	cout << "[Exhibit Manager Menu]\n" << endl;
	cout << "Select what to view/edit:" << endl;
	cout << "   1. Exhibits" << endl;
	cout << "   2. Booths" << endl;
	cout << "   3. Services" << endl;
	cout << "   4. Attendees" << endl;
	cout << "   5. Inventory" << endl;
	cout << "   6. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;
	cout << endl;
	system("clear");
	switch(int_input)
	{
		case 1:
			exhibitMenu();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			return;
			break;
		default:
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
			cout << "***Not a valid command, try again***\n" << endl;
			break;
	}
	
	exhibitManagerMenu();

}

void mainMenu()
{

	cout << "[Convention Exhibit Management System]\n" << endl;
	cout << "Select user interface:" << endl;
	cout << "   1. Exhibit Manager" << endl;
	cout << "   2. Exhibitor" << endl;
	cout << "   3. Attendees" << endl;
	cout << "   4. Exit\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;
	cout << endl;
	system("clear");
	switch(int_input)
	{
		
		case 1:
			exhibitManagerMenu();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			return;
			break;
		default:
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "***Not a valid command, try again***\n" << endl;
			break;
	}
	mainMenu();

}

int main()
{	
	
	try{
		
		for(int i = 0; i < 1; i++)
		{
			db.DBParser.sendNewInput("OPEN " + tables[i] + ";");
    		db.execute(); 
		}
		
		
		for(int i = 0; i < 1; i++)
		{
			db.DBParser.sendNewInput("SHOW " + tables[i] + ";");
    		db.execute(); 
		}
		
		
		
		system("clear");
		mainMenu();
		
		for(int i = 0; i < 1; i++)
		{
			db.DBParser.sendNewInput("SAVE " + tables[i] + ";");
    		db.execute(); 
		}
		
		
    	//db.DBParser.contain.clear();
		//db.DBParser.sendNewInput("SAVE inventory;");
    	//db.execute();

		
		
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