#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
#include "DBsystem.h"
#include <algorithm>

using namespace std;

//UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
//UPDATE exhibitors SET email = "Max" WHERE age > 5;

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
	
		cin.ignore();				//needed this here because input was getting cut off
	for(int i = 0; i < 10; ++i)
	{
		string userInput;
		cout << values[i] + ": ";
		getline(cin,userInput);
		str_input += "\"" + userInput + "\"";
		if(i < 9)
			str_input += ", ";
	}
	
	str_input += ");";
	
	cout << str_input << endl;
	
	db.DBParser.sendNewInput(str_input);
    db.execute(); 
	
	

}

void printExhibitName(bool all, string searchName = "")
{
	
	ifstream file;
	file.open("exhibitors.db");
	string temp = "";
	
	if(all)
	{
		
		if (file.is_open()) 
		{
			cout << "[All Exhibits]\n" << endl;
			getline(file, temp); // skips CREATE line
			int count = 1;
			cout << "\t";
			for (int i = 0; i < 10; ++i){
					cout << '[' << db.database["exhibitors"]->getHeaders()[i] << ']' << "   ";
			}
			cout << endl;
			while (getline(file, temp)) 
			{
				int s = temp.find("\"") + 1;
				int e = temp.find("\"",s);
			
				char chars[] = "\"),;";										//Grab characters to remove
				
				//if(searchName.compare(temp.substr(s,e-s))==0){				//Get all proper headers and print
					string str = temp.substr(s,temp.length());
					for (unsigned int i = 0; i < strlen(chars); ++i)		//Do some formatting
					 {
						str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
					 }
					cout << count << ". " << str << endl;
					count++;
				//}
			}
			cout << "\n* Press ENTER. to continue...";
			cin >> int_input;
			
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
		}

 	}else{		//Searching for a specific exhibitor
 	
 		if (file.is_open()) 
		{
			cout << "[Searching Exhibits...]\n" << endl;
			getline(file, temp); // skips CREATE line
			int count = 1;
			cout << "\t";
			for (int i = 0; i < 10; ++i){
					cout << '[' << db.database["exhibitors"]->getHeaders()[i] << ']' << "    " ;
			}
			cout << endl;
			while (getline(file, temp)) 
			{
				int s = temp.find("\"") + 1;
				int e = temp.find("\"",s);
		
				char chars[] = "\"),;";										//Grab characters to remove
				
				if(searchName.compare(temp.substr(s,e-s))==0){				//Get all proper headers and print
					string str = temp.substr(s,temp.length());
					for (unsigned int i = 0; i < strlen(chars); ++i)		//Do some formatting
					 {
						str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
					 }
					cout << count << ". " << str << endl;
					count++;
				}
			}
			cout << "\n* Press ENTER to continue...";
			cin >> int_input;
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
		}
 		
 	}
 	
 	file.close();
}


void viewExhibits(){  		//When Exhibit Manager View/Searches for an exhibit
	int noTables = 0;		//counts how many exhibits are there
	string showName;
	

	cout << "[View/Search for an Exhibit(s)]\n" << endl;
	cout << "   1. View all exhibits" << endl;
	cout << "   2. Search for an Exhibit(s)" << endl;
	cout << "   3. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;
	system("clear");
	switch(int_input){
		case 1:
			printExhibitName(true, "");
			break;
		case 2:
			cout << "Enter the Exhibit name: " << endl;
			cin.ignore();
			getline(cin, showName);
			printExhibitName(false, showName);
			//db.SHOW(showTable);
			break;
		case 3:
			return;
		default:
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
			cout << "***Not a valid command, try again***\n" << endl;
			break;
	}
	viewExhibits();
}

void exhibitMenu()
{
	
	cout << "[Exhibit Manager Menu]\n" << endl;
	cout << "   1. Register New Exhibit" << endl;
	cout << "   2. View/Search for an Exhibit(s)" << endl;
	cout << "   3. Remove an Exhibit" << endl;
	cout << "   4. <- Go Back\n" << endl;
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
			viewExhibits();
			break;
		case 3:
			cout << "Remove..." << endl;
			break;
		case 4:
			return;
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
	cout << "   4. Exit and Save\n" << endl;
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
		
		
		
		//Testing things here
		//Update works if the whole column is of ONE type!
		
		
		/*
		db.DBParser.sendNewInput("OPEN exhibitors;");
		db.execute();
		db.DBParser.sendNewInput("SHOW exhibitors;");
		db.execute();
		
		db.DBParser.sendNewInput("UPDATE exhibitors SET address = 123_Fake_St, contact_person = Dead_Pool, email = fake@fmail.com WHERE fax >= 34;");
		db.execute();
		db.DBParser.sendNewInput("SHOW exhibitors;");
		db.execute();
		*/
		//db.DBParser.sendNewInput("OPEN animals;");
		//db.execute();
		//db.DBParser.sendNewInput("SHOW animals;");
		//db.execute();
		
		
		
		
		
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