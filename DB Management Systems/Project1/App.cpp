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

int int_input;
string str_input = "";
string ManagerPW = "asdf";
void mainMenu();
void registerNewExhibit();
void viewExhibits();
void exhibitMenu();
void exhibitManagerMenu();
void exhibitPWScreen();
void exhibitorMenu();
void exhibitorExhibitbyName();
void exhibitorNumAttendees();



int managerSearchExhibits(vector<string> headers, vector<string> OP, vector<string> conditions)
{
	string newTableName = "SEARCH QUERY";//create new name

	Table* pointer = db.SELECT(newTableName, "exhibitors", headers, OP, conditions); //get select table and assign a pointer to it
	
	if (pointer->getRowLength() < 1) //if there is not anything to show
	{
		cout << "There is no table with that name. \n"; //there must be no table
		return 1;
	}
	else //otherwise we have something to show
	{
		db.SHOW(pointer->getTableName()); //so show it

		delete pointer; //get rid of the table in memory since we don't need it 

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
	
	
	
	db.DBParser.sendNewInput("SAVE " + tables[0] + ";");
	db.execute(); 
	
	system("clear");
	
	cout << "* New Exhibit has been added *\n" << endl;;
	
	
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
			while (getline(file, temp)) 
			{
				int s = temp.find("\"") + 1;
				int e = temp.find("\"",s);
				cout << count << ". " << temp.substr(s,e-s) << endl;
				count++;
			}
			cout << "\n* Press ENTER to continue...";
			
			cin.clear();
			cin.get();
			cin.clear();
			cin.ignore(10000, '\n');
			system("clear");
		}
		

 	}
 	else{		//Searching for a specific exhibitor
 	
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


void managerSearchExhibitsMenu()
{

	//for searching for exhibit
	int case2Option = 0;
	string viewHeader ="";
	string viewOP= "";
	string viewCondition = "";

	vector<string> headers;
	vector<string> OP;
	vector<string> conditions;

	//clear out vectors
	headers.clear();
	OP.clear();
	conditions.clear();

	cout << "Search by Criteria? (1 Yes. 0 No.)\n";
	cin >> case2Option;
	if (case2Option)
	{
		cout << "Enter Criteria. Enter 1 at header stage when done." << endl;
		while (1) //get header, op, and condition for search
		{
			cout << "Header: ";
			getline (cin,viewHeader); //get header lhs
			if (viewHeader == "1") break; //break if we have 1
			cout << endl;
			headers.push_back(viewHeader); //push back into vector

			cout << "Operation: ";
			cin >> viewOP; //get operation
			cout << endl;
			OP.push_back(viewOP);

			cout << "Condtion: ";
			getline(cin, viewCondition); //get condition rhs
			cout << endl;
			conditions.push_back(viewCondition);
		}
		system("clear");//clear out the screen
		managerSearchExhibits(headers, OP, conditions);
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter the Exhibit name: " << endl;
		getline(cin, viewCondition); //get input
		headers.push_back("org_name");
		OP.push_back("==");
		conditions.push_back(viewCondition);
		system("clear");//clear out the screen
		managerSearchExhibits(headers, OP, conditions); //will call select and then SHOW and then delete the temp table.
	}



}


void viewExhibits()	//When Exhibit Manager View/Searches for an exhibit
{  	
	int noTables = 0;		//counts how many exhibits are there
	



	cout << "[View/Search for an Exhibit(s)]\n" << endl;
	cout << "   1. View all Exhibit's Names" << endl;
	cout << "   2. Search for an Exhibit(s)" << endl;
	cout << "   3. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;
	
	system("clear");
	switch (int_input)
	{
		case 1:
			printExhibitName(true, "");
			break;
		case 2:
			managerSearchExhibitsMenu();
			break;
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

	cout << "Deleted " << deleteName << '\n'<< endl;
	
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

void exhibitorMenu()
{
	cout << "[Exhibitor Menu]\n"<<endl;
	cout << "Select option:"<<endl;
	cout << "  1. View Exhibit by Entering Name"<<endl;
	cout << "  2. View Attendees by Exhibit"<<endl;
	cout << "  3. <-- Go Back"<<endl<<endl;
	
	cout<< "* Enter command number: ";
	cin >> int_input;
	cout<<endl;
	system ("clear");
	switch (int_input)
	{
		case 1:
			exhibitorExhibitbyName();
			break;
		case 2:
			exhibitorNumAttendees();
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
	exhibitorMenu();
}

void exhibitorExhibitbyName()
{
	cout << "Enter the Name of the Exhibit: ";
	cin >> str_input;
}

void exhibitorNumAttendees()
{
	
}

void attendeeName()
{
	cout << "[Attendee Info by Name]\n"<<endl;
	cout << "Enter the attendee name: ";
	cin.ignore();
	getline(cin, str_input);
	
	//using the str_input, serach through the attendee.db and get the values.
	//Make sure to add error chekcing for wrong input or name that is not on the table.

}

void attendeeBooths()
{
	cout << "[Attendee Booth by Name]\n"<<endl;
	cout << "Enter the attendee name: ";
	cin.ignore();
	getline(cin, str_input);
}

void attendeeBoothInfo()
{
	attendeeName();
	attendeeBooths();
}

void attendeeMenu()
{
	cout << "[Attendee Menu]\n"<<endl;
	cout << "Select option:"<<endl<<endl;
	cout << "  1. View Info by Name"<<endl;
	cout << "  2. View Visited Booths by Name"<<endl;
	cout << "  3. View both Info and Booths by Name"<<endl;
	cout << "  4. <-- Go Back"<<endl<<endl;
	
	cout<< "* Enter command number: ";
	cin >> int_input;
	cout<<endl;
	system ("clear");
	switch (int_input)
	{
		case 1:
			attendeeName();
			break;
		case 2:
			attendeeBooths();
			break;
		case 3:
			attendeeBoothInfo();
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
	attendeeMenu();
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

//high level clearance
void exhibitPWScreen()
{
	string pw = ""; //password
	cout<<"Please input the password: ";
	cin>>pw;
	if (pw.compare(ManagerPW) == 0)
	{
		system("clear");
		exhibitManagerMenu();
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Not a Valid Password***\n" << endl;
		
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
	switch (int_input)
	{

	case 1:
		exhibitPWScreen();
		break;
	case 2:
		exhibitorMenu();
		break;
	case 3:
		attendeeMenu();
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
