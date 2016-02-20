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
//UPDATE exhibitors SET email = "Max" WHERE age > 5;

DBsystem db;
string tables[5] = {"exhibitors","booth","services","attendees","inventory"};

int int_input = 0;
string str_input = "";
string ManagerPW = "asdf";
void mainMenu();
void registerNewExhibit();
void viewExhibits();
void exhibitMenu();
void exhibitManagerMenu();
void exhibitPWScreen();

void registerNewExhibit()
{
	string values[10] = {"Name","Address","contact_person","email", "phone Number","Fax Number","category","booth_personnel","org_description","org_site"};
	
	cout << "[Register New Exhibit]\n" << endl;
	cout << "-Enter the details of your Organization-" << endl;
	
		cin.ignore();				//needed this here because input was getting cut off

	str_input = "INSERT INTO exhibitors VALUES FROM (";
	for(int i = 0; i < 10; ++i)
	{
		string userInput;
		cout << values[i] + ": ";
		getline(cin,userInput);
		str_input += "\"" + userInput + "\"";
		if(i < 9)
		{
			str_input += ", ";
		}	
	}
	str_input += ");";
	
	cout<<str_input << endl;
	
	
	db.DBParser.sendNewInput("CLOSE " + tables[0] + ";");
	db.execute();
	
	db.DBParser.sendNewInput("OPEN " + tables[0] + ";");
	db.execute();
	
	db.DBParser.sendNewInput(str_input);
	db.execute();
	str_input.clear();
	
	
	//for(int i = 0; i < 1; i++)
	//{
		db.DBParser.sendNewInput("SAVE " + tables[0] + ";");
    	db.execute(); 
	//}
	system("clear");
	
}
void printExitbitNames(bool all)
{
	
	ifstream file;
	file.open("exhibitors.db");
	string temp = "";
		cout << endl;
	system("clear");
	if(all)
	{
		if (file.is_open()) 
		{
			cout << "[All Exhibits]\n" << endl;
			getline(file, temp); // skips CREATE line
			int count = 1;
			while (getline(file, temp)) 
			{
				int s = temp.find("\"") + 1;
				int e = temp.find("\"",s);
				cout << count << ". " << temp.substr(s,e-s) << endl;
				count++;
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
	string showTable;
	

	cout << "[View/Search for an Exhibit(s)]\n" << endl;
	cout << "   1. View all Exhibit's Names" << endl;
	cout << "   2. Search for an Exhibit(s)" << endl;
	cout << "   3. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;
	system("clear");
	switch(int_input){
		case 1:
			printExitbitNames(true);
			break;
		case 2:
			cout << "Enter the Exhibit name: " << endl;
			cin >> showTable;
			db.SHOW(showTable);
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

void deleteExhibit()
{
	system("clear");
	cout << "[Delete Exhibit]\n" << endl;
	
	cout << "* Enter name of Exhibit: ";
	
	cin >> str_input;
	str_input = "DELETE FROM exhibitors WHERE org_name == \"" + str_input + "\";";
	cout << endl;
	
	db.DBParser.sendNewInput(str_input);
    db.execute(); 
    
    db.DBParser.sendNewInput("SAVE exhibitors;");
    db.execute(); 
	
}

void exhibitMenu()
{
	
	cout << "[Exhibit Menu]\n" << endl;
	cout << "   1. Register New Exhibit" << endl;
	cout << "   2. View/Search for an Exhibit(s)" << endl;
	cout << "   3. Delete an Exhibit" << endl;
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
			deleteExhibit();
			break;
		case 4:
			return;
		default:
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
			cout << "***Not a valid command, try again***\n" << endl;

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

void exhibitPWScreen()
{
	string pw = "";
	cout<<"Please input the password: ";
	cin>>pw;
	if (pw.compare(ManagerPW) == 0)
	{
		exhibitManagerMenu();
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "***Not a Valid Password***" << endl;
		mainMenu();
	}
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
			exhibitPWScreen();
			//exhibitManagerMenu();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			return;
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
		
		
		
		
		
		
		system("clear");
	    mainMenu();
		
		
	
	}
	catch(...)
	{
		cout << "Please try again: " << endl;
	}
	

}
