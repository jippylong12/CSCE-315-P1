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

using namespace std;



//error checking for menu navigation
int checkInputSize(string input)
{
	if (input.size() > 1)
		return 1; //false
	else
		return 0; //true
}

//error checking for menu navigation
int checkIsDigit(string input)
{
	return isdigit(input[0]); //returns 0 if true
}

//UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
//UPDATE exhibitors SET email = "Max" WHERE age > 5;

DBsystem db;
string tables[5] = {"exhibitors","booth","services","attendees","inventory"};

string main_input;
string str_input = "";
string ManagerPW = "asdf";
void mainMenu();
void registerNewExhibit();
void viewExhibits();
void exhibitMenu();
void exhibitManagerMenu();
void exhibitPWScreen();

int managerSearchExhibits(string tableName)
{
	string newTableName = "SELECT " + tableName;
	vector<string> headers;
	headers.push_back("org_name");

	vector<string> OP;
	OP.push_back("==");

	vector<string> condition;
	condition.push_back(tableName);


	Table* pointer = db.SELECT(newTableName, "exhibitors", headers, OP, condition);
	
	if (pointer->getRowLength() < 1)
	{
		cout << "There is no table with that name. \n";
		return 1;
	}
	else
	{
		db.SHOW(pointer->getTableName());

		delete pointer;

		return 0;
	}

}


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
		if(i < 9) //for the first nine items
		{
			str_input += ", "; //put a comma
		}	
	}
	str_input += ");"; //on the last item we don't need a comma
	
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

void printExhibitName(bool all, string searchName = "")
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
			cout << "\n* Enter 1 to continue..." << endl;;

			//enter wasn't working so I just used 1
			char temp = 'x';
			while (temp != '1')
				cin.get(temp);
			system("clear"); //make screen pretty
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
			cin >> main_input;
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
		}
 		
 	}
 	
 	file.close();
			
	

}



void viewExhibits(){  		//When Exhibit Manager View/Searches for an exhibit
	int noTables = 0;		//counts how many exhibits are there
	string showName; //for searching for exhibit
	

	cout << "[View/Search for an Exhibit(s)]\n" << endl;
	cout << "   1. View all Exhibit's Names" << endl;
	cout << "   2. Search for an Exhibit(s)" << endl;
	cout << "   3. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> main_input;
	if (!checkInputSize(main_input) && !checkInputSize(main_input))
	{
		int int_input = stoi(main_input);
		system("clear");
		switch (int_input)
		{
		case 1:
			printExhibitName(true, "");
			break;
		case 2:
			cout << "Enter the Exhibit name: " << endl;
			cin >> showName; //get input
			system("clear");//clear out the screen
			managerSearchExhibits(showName); //will call select and then SHOW and then delete the temp table.
		case 3: // go back
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
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Not a valid command, try again***\n" << endl;
		viewExhibits();
	}

}

void deleteExhibit()
{
	system("clear");
	cout << "[Delete Exhibit]\n" << endl;
	
	cout << "* Enter name of Exhibit: ";
	
	cin >> str_input;
	string deleteName = str_input; //grab the tablename for output
	str_input = "DELETE FROM exhibitors WHERE org_name == " + str_input + ";";
	cout << endl;
	
	db.DBParser.sendNewInput(str_input);
    db.execute(); 
    
    db.DBParser.sendNewInput("SAVE exhibitors;");
    db.execute(); 

	system("clear"); //clean terminal

	cout << "Deleted " << deleteName << '.'<< endl;
	
}

void exhibitMenu()
{
	
	cout << "[Exhibit Menu]\n" << endl;
	cout << "   1. Register New Exhibit" << endl;
	cout << "   2. View/Search for an Exhibit(s)" << endl;
	cout << "   3. Delete an Exhibit" << endl;
	cout << "   4. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> main_input;
	if (!checkInputSize(main_input) && !checkInputSize(main_input))
	{
		int int_input = stoi(main_input);
		cout << endl;
		system("clear");
		switch (int_input)
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
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Not a valid command, try again***\n" << endl;
		exhibitMenu();
	}

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
	
	cin >> main_input;
	if (!checkInputSize(main_input) && !checkInputSize(main_input))
	{
		int int_input = stoi(main_input);
		cout << endl;
		system("clear");
		switch (int_input)
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
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Not a valid command, try again***\n" << endl;
		exhibitManagerMenu();
	}

}

//high level clearance
void exhibitPWScreen()
{
	string pw = ""; //password
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
		system("clear");
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
	
	cin >> main_input;
	if (!checkInputSize(main_input) && !checkInputSize(main_input))
	{
		int int_input = stoi(main_input);
		cout << endl;
		system("clear");
		switch (int_input)
		{

		case 1:
			exhibitPWScreen();
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
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "***Not a valid command, try again***\n" << endl;
		mainMenu();
	}


}


int main()
{	
	
	try{
		
		for(int i = 0; i < 5; i++)
		{
			db.DBParser.sendNewInput("OPEN " + tables[i] + ";");
    		db.execute(); 
		}
		
		system("clear"); //gives terminal clean look
	    mainMenu();
	
	}
	catch(...)
	{
		cout << "Please try again: " << endl;
	}
	

}
