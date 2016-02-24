#include "App.h"
using namespace std;

/*

        PROJECT 1 APPLICATION - "App.cpp"

*/

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

//PDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
//UPDATE exhibitors SET email = "Max" WHERE age > 5;


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

//Works with "attendees.db"
int managerSearchAttendees(vector<string> headers, vector<string> OP, vector<string> conditions)
{
	string newTableName = "SEARCH QUERY";//create new name

	Table* pointer = db.SELECT(newTableName, "attendees", headers, OP, conditions); //get select table and assign a pointer to it
	
	if (pointer->getRowLength() < 1) //if there is not anything to show
	{
		cout << "Their data was not found. \n"; //there must be no table
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
					for (unsigned int i = 0; i < strlen(chars); ++i)		//Do some formating
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


void printAttendeeName(bool all, string searchName = ""){

	
	ifstream file;
	file.open("attendees.db");
	string temp = "";
		cout << endl;
	system("clear");
	if(all)
	{
		if (file.is_open()) 
		{
			cout << "[All Attendees]\n" << endl;
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
			cout << "[Searching Attendees...]\n" << endl;
			getline(file, temp); // skips CREATE line
			int count = 1;
			cout << "\t";
			for (int i = 0; i < 10; ++i){
					cout << '[' << db.database["attendees"]->getHeaders()[i] << ']' << "    " ;
			}
			cout << endl;
			while (getline(file, temp)) 
			{
				int s = temp.find("\"") + 1;
				int e = temp.find("\"",s);
		
				char chars[] = "\"),;";										//Grab characters to remove
				
				if(searchName.compare(temp.substr(s,e-s))==0){				//Get all proper headers and print
					string str = temp.substr(s,temp.length());
					for (unsigned int i = 0; i < strlen(chars); ++i)		//Do some formating
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
        cin.ignore();			//Need this here or else input for Header gets cut off

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

            cin.ignore(); //Input getting cut off
            cout << "Condition: ";
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
	cin.clear();
	cin.ignore(10000, '\n');
	system("clear");
	cout << "[Delete Exhibit]\n" << endl;
	
	cout << "* Enter name of Exhibit: ";
	
	getline(cin, str_input);
	string deleteName = str_input; //grab the tablename for output
	str_input = "DELETE FROM exhibitors WHERE org_name == " + str_input + ";";
	cout << endl;
	
	db.DBParser.sendNewInput(str_input);
    db.execute(); 
	db.DBParser.contain.clear();
    
    db.DBParser.sendNewInput("SAVE exhibitors;");
    db.execute(); 
	db.DBParser.contain.clear();

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

//Begin Manager Booth Menu
void boothMenu(){
	cout << "[Booth Menu]\n" << endl;
	cout << "   1. Assign Booth Locations" << endl;
	cout << "   2. Delete Booth Locations" << endl;
	cout << "   3. View Booth Locations" << endl;
	cout << "   4. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;

	cout << endl;
	system("clear");
	switch (int_input)
	{
	case 1:
		assignBoothLocations();
		break;
	case 2:
		deleteBoothLocations();
		break;
	case 3:
		viewBoothLocations();
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

	boothMenu();
	
	
}

void assignBoothLocations(){
	cout << "Assigning booth..." << endl;
}

void deleteBoothLocations(){
	cout << "Deleting booth..." << endl;
	
}

void viewBoothLocations(){		//View all or search
	cout << "Viewing..." << endl;
	
}
//End Manager Booth Menu


//Begin Manager Services Menu
void servicesMenu(){
	cout << "[Services Menu]\n" << endl;
	cout << "   1. Assign Services to an Exhibit Booth" << endl;
	cout << "   2. Delete Services for an Exhibit(s) Booth" << endl;
	cout << "   3. View Services for Exhibits" << endl;
	cout << "   4. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;

	cout << endl;
	system("clear");
	switch (int_input)
	{
	case 1:
		assignBoothServices();
		break;
	case 2:
		deleteBoothServices();
		break;
	case 3:
		viewBoothServices();
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

	servicesMenu();
	
	
}

void assignBoothServices(){
	cout << "Assign booth services.." << endl;
	
}

void deleteBoothServices(){
	cout << "Deleting booth services" << endl;
	
}

void viewBoothServices(){
	cout << "Viewing booth service " << endl;
   vector<string> orgHeader;               //Search by attendee name
        orgHeader.push_back("name");
    
        vector<string> OP;                      //Take all entries that have the name
        OP.push_back("==");
    
        vector<string> orgName;                 //Search for the ACUTAL name entries
        orgName.push_back(exhibitorName);
    
        //Will select and show the corresponding info for the current attendee.
    
    
        Table* pointer = db.SELECT("", "services", orgHeader, OP, orgName); //get select table and assign a pointer to it
    
        //Now, we can search through this table to grab their exhibits_visited
    
    vector<string> exhibitsVisited;
    if(pointer->getRowLength()!=0){   //search through the attendee info in attendees.db.  If there is no info for the attendee, there will be no exhibits visited.
        for (int i = 0; i < pointer->getRowLength(); ++i){
            cout << i+1 << ". " << pointer->getTable()[i][6] << endl;       //index 6 because it is the 7th column
        }
    }else cout << "You have not visited any exhibits. \n" << endl;

	
    
    
}
//End Manager Services Menu



//Begin Manager Attendee Menu
void attendeeManagerMenu(){
	cout << "[Manager Attendee Menu]\n" << endl;
	cout << "   1. Register an attendee" << endl;
	cout << "   2. Delete an attendee" << endl;
	cout << "   3. Search for an attendee(s)" << endl;
	cout << "   4. List all attendee(s)" << endl;
	cout << "   5. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;

	cout << endl;
	system("clear");
	switch (int_input)
	{
	case 1:
		managerRegisterAttendee();
		break;
	case 2:
		managerDeleteAttendee();
		break;
	case 3:
		managerSearchAttendee();
		break;
	case 4:
		printAttendeeName(true, "");
	case 5:
		return;
	default:
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Not a valid command, try again***\n" << endl;

		break;
	}

	attendeeManagerMenu();
}

void managerRegisterAttendee(){		//should be like registering an exhibit

	string values[9] = {"Name","Organization","Address","email", "Registration Fee","Category","Exhibits Visited","Badge Status","org_description"};
	
	cout << "[Register New Attendee]\n" << endl;
	cout << "-Enter the details of the Attendee-" << endl;
	
		cin.ignore();				//needed this here because input was getting cut off

	str_input = "INSERT INTO attendees VALUES FROM (";
	for(int i = 0; i < 8; ++i)
	{
		string userInput;
		cout << values[i] + ": ";
		getline(cin,userInput);
		str_input += "\"" + userInput + "\"";
		if(i < 8) //for the first nine items
		{
			str_input += ", "; //put a comma
		}	
	}
	str_input += ");"; //on the last item we don't need a comma
	
	cout<<str_input << endl;
	
	//tables[3] is attendees
	
	db.DBParser.sendNewInput("CLOSE " + tables[3] + ";");
	db.execute();
	
	db.DBParser.sendNewInput("OPEN " + tables[3] + ";");
	db.execute();
	
	db.DBParser.sendNewInput(str_input);
	db.execute();
	str_input.clear();
	
	
	
	db.DBParser.sendNewInput("SAVE " + tables[3] + ";");
	db.execute(); 
	
	system("clear");
	
	cout << "* New Attendee has been added! *\n" << endl;;






	
}
void managerDeleteAttendee(){
	cout << "Delete an attendee" << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	system("clear");
	cout << "[Delete Attendee]\n" << endl;
	
	cout << "* Enter name of the Attendee: ";
	
	getline(cin, str_input);
	string deleteName = str_input; //grab the tablename for output
	str_input = "DELETE FROM attendees WHERE name == " + str_input + ";";
	cout << endl;
	
	db.DBParser.sendNewInput(str_input);
    db.execute(); 
	db.DBParser.contain.clear();
    
    db.DBParser.sendNewInput("SAVE attendees;");
    db.execute(); 
	db.DBParser.contain.clear();

	system("clear"); //clean terminal

	cout << "Deleted " << deleteName << "!\n"<< endl;

	
	
}
void managerSearchAttendee(){
	//cout << "Seraching for an attendee..." << endl;
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
        cin.ignore();			//Need this here or else input for Header gets cut off

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

            cin.ignore(); //Input getting cut off
            cout << "Condition: ";
			getline(cin, viewCondition); //get condition rhs
			cout << endl;
			conditions.push_back(viewCondition);
		}
		system("clear");//clear out the screen
		managerSearchAttendees(headers, OP, conditions);
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter the attendee name: " << endl;
		getline(cin, viewCondition); //get input
		headers.push_back("name");	 //push back "name" 
		OP.push_back("==");
		conditions.push_back(viewCondition);
		system("clear");//clear out the screen
		managerSearchAttendees(headers, OP, conditions); //will call select and then SHOW and then delete the temp table.
	}


	
	
	
	
	
	
}
//End Manager Attendee Menu



//Begin Manager Inventory Menu
void inventoryMenu(){
	cout << "[Manager Inventory Menu]\n" << endl;
	cout << "   1. Add To Inventory" << endl;
	cout << "   2. Delete From Inventory" << endl;
	cout << "   3. List Current Inventory" << endl;
	cout << "   4. <- Go Back\n" << endl;
	cout << "* Enter command number: ";
	
	cin >> int_input;

	cout << endl;
	system("clear");
	switch (int_input)
	{
	case 1:
		addInventory();
		break;
	case 2:
		deleteInventory();
		break;
	case 3:
		viewInventory();
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

	inventoryMenu();
}
void addInventory(){			//Insert into inventory
	
}
void deleteInventory(){
	
}
void viewInventory(){
	
}
//End Manager Inventory Menu



//Manager Revenue
void showTotalRevenue(){
	//Revenue initialized in App.h
	
	 cout << "Revenue generated: " << revenue << endl;
	 double tempPrice = 0;
	 double total = 0;
	 
	 vector<string> inventoryList;
	 vector<string> servicesList;
	 
	 
	 vector<string> orgHeader;               //Search by exhibitsName (will have the corresponding item)
     orgHeader.push_back("org_name");
     
     vector<string> itemHeader;
     itemHeader.push_back("item");
    
     vector<string> OP;                      //Take all entries that have the exhibitorName
     OP.push_back("!=");
    
     vector<string> orgName;                 //Search for the ACUTAL exhibits visited entries
     orgName.push_back("-1");
     
    Table* ptr = db.SELECT("", "exhibitors", orgHeader, OP, orgName ); //grab all exhibitor names
    //db.SHOW(ptr -> getTableName());
    
    vector <string> orgNames;
    
    for (int i = 0; i < ptr -> getRowLength(); ++i)
    {
    	orgNames.push_back(ptr -> getTable()[i][0]);
    	cout<<orgNames[i]<<endl;
    }
    delete ptr;
    
    
    
    for (int f = 0; f < orgNames.size(); ++f)
    {
    	orgName.clear();
    	orgHeader.clear();
    	OP.clear();
    	inventoryList.clear();
    	servicesList.clear();
    	orgName.push_back(orgNames[f]);
    	orgHeader.push_back("exhibitorName");
    	exhibitorName = orgNames[f];
    	OP.push_back("==");
    	
    	
		Table* pointer = db.SELECT("", "inventory", orgHeader, OP,  orgName); //get select table and assign a pointer to it
	    if (pointer->getRowLength() < 1) //if there is not anything to show
        {
            cout << "There is no table with that name. \n"; //there must be no table
            return;
        }
        else //otherwise we have something to show
        {
            //db.SHOW(pointer->getTableName());   //so show it

            //delete pointer;                     //get rid of the table in memory since we don't need it

            //return 0;
        }

		for (int i = 0; i < pointer->getRowLength(); ++i)
		{
			inventoryList.push_back(pointer->getTable()[i][0]);			//This will grab the items list
			servicesList.push_back(pointer-> getTable()[i][2]);
		}
		
		cout << "Inventory List for " << exhibitorName << ":" << endl;
		for (int i = 0; i < inventoryList.size(); ++i)
		{
			cout <<"item: "<< inventoryList[i] <<"  service: "<<servicesList[i]<< endl;
		}
		
		delete pointer;
		
		//Find the prices using the servicesList.
		
		//db.SHOW(pointer1 -> getTableName());
		for (int a = 0; a < servicesList.size(); ++a)
		{
			cout<<servicesList[a]<<endl;
			//itemHeader.push_back("item");
		}
		//cout<<endl<<"size of servicesList: "<<servicesList.size()<<"  size of itemHeader: "<<itemHeader.size()<<endl;
		for (int i = 0; i < servicesList.size(); ++i)
		{
			//cout<<endl<<servicesList[i]<<endl;
		}
		//Table* pointer1 = db.SELECT("", "services", itemHeader, OP,  servicesList); //get select table and assign a pointer to it
		//db.SHOW(pointer1 -> getTableName());
		for(int a = 0; a<servicesList.size(); ++a)
		{
			vector <string> tempServicesList;
			tempServicesList.push_back(servicesList[a]);
			Table* pointer1 = db.SELECT("", "services", itemHeader, OP,  tempServicesList);
			
			
			for (int i = 0; i < pointer1->getRowLength(); ++i)
			{
				if (pointer1 -> getTable()[i][0].compare(servicesList[a]) == 0)
				{
					tempPrice = stod(pointer -> getTable()[i][3]);
					cout << "Before string to double conversion: "<< pointer1 -> getTable()[i][3]<<endl;;
					cout << "After string to double Conversion: " <<stod(pointer1 -> getTable()[i][3])<<endl;
				}
				else
				{
					tempPrice = 0;
				}
				total += tempPrice;
			}
		delete pointer1;
	}
    }
    
	//
	
	cout<<"The total revenue is: $"<<total<<endl;
	
	
	//delete pointer1;
	
}


//-----------------------------------------------------------------------------------//


//Exhibitor Menu//


void invoiceCalculator()
{

	//show invoice for exhibitor (booth, service, and the cost for each subitem, and total cost).
	//Check through inventory.db and match exhibitor name with item.  Grab all of the relevant items and print
	//Go through services match the items with the price and grab the price
	 
	 
	 double tempPrice = 0;
	 double total = 0;
	 
	 vector<string> inventoryList;
	 vector<string> servicesList;
	 
	 
	 vector<string> orgHeader;               //Search by exhibitsName (will have the corresponding item)
     orgHeader.push_back("exhibitorName");
     
     vector<string> itemHeader;
     itemHeader.push_back("item");
    
     vector<string> OP;                      //Take all entries that have the exhibitorName
     OP.push_back("==");
    
     vector<string> orgName;                 //Search for the ACUTAL exhibits visited entries
     orgName.push_back(exhibitorName);
     
    
	
	
	 Table* pointer = db.SELECT("", "inventory", orgHeader, OP,  orgName); //get select table and assign a pointer to it
    
        if (pointer->getRowLength() < 1) //if there is not anything to show
        {
            cout << "There is no table with that name. \n"; //there must be no table
            return;
        }
        else //otherwise we have something to show
        {
            db.SHOW(pointer->getTableName());   //so show it

            //delete pointer;                     //get rid of the table in memory since we don't need it

            //return 0;
        }

	for (int i = 0; i < pointer->getRowLength(); ++i){
		inventoryList.push_back(pointer->getTable()[i][0]);			//This will grab the items list
		servicesList.push_back(pointer-> getTable()[i][2]);
	}
	
	cout << "Inventory List for " << exhibitorName << ":" << endl;
	for (int i = 0; i < inventoryList.size(); ++i){
		cout <<"item: "<< inventoryList[i] <<"  service: "<<servicesList[i]<< endl;
	}
	
	delete pointer;
	
	//Find the prices using the servicesList.
	
	//db.SHOW(pointer1 -> getTableName());
	for (int a = 0; a < servicesList.size(); ++a)
	{
		cout<<servicesList[a]<<endl;
		//itemHeader.push_back("item");
	}
	cout<<endl<<"size of servicesList: "<<servicesList.size()<<"  size of itemHeader: "<<itemHeader.size()<<endl;
	for (int i = 0; i < servicesList.size(); ++i)
	{
		cout<<endl<<servicesList[i]<<endl;
	}
	//Table* pointer1 = db.SELECT("", "services", itemHeader, OP,  servicesList); //get select table and assign a pointer to it
	//db.SHOW(pointer1 -> getTableName());
	for(int a = 0; a<servicesList.size(); ++a)
	{
		vector <string> tempServicesList;
		tempServicesList.push_back(servicesList[a]);
		Table* pointer1 = db.SELECT("", "services", itemHeader, OP,  tempServicesList);
		
		
		for (int i = 0; i < pointer1->getRowLength(); ++i)
		{
			if (pointer1 -> getTable()[i][0].compare(servicesList[a]) == 0)
			{
				tempPrice = stod(pointer -> getTable()[i][3]);
				cout << "Before string to double conversion: "<< pointer1 -> getTable()[i][3]<<endl;;
				cout << "After string to double Conversion: " <<stod(pointer1 -> getTable()[i][3])<<endl;
			}
			else
			{
				tempPrice = 0;
			}
			total += tempPrice;
		}
		delete pointer1;
	}
	//
	
	cout<<"The total invoice is: $"<<total<<endl;
	
	
	//delete pointer1;
	
}


//show total revenue (add up all the fees).
//Will work with services.db
//Should the manager do this?


void addAttendee(){

}
void deleteAttendee(){
	
}


void exhibitorMenu()
{
	cout << "[Exhibitor Menu]\n"<<endl;
	cout << "Select option:"<<endl;
	cout << "  1. View My Info"<<endl;
	cout << "  2. View Your Attendees"<<endl;
	cout << "  3. View Invoice"<<endl;
	cout << "  4. Add Attendee For Your Exhibit" << endl;
	cout << "  5. Delete Attendee From Your Exhibit" << endl;
	cout << "  6. <-- Go Back"<<endl<<endl;
	
	
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
			invoiceCalculator(); //not implemented yet
			break;
		case 4:
			addAttendee();
			break;
		case 5:
			deleteAttendee();
			break;
		case 6:
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
	bool exhibitNameFound = 0;

    cout << "Hi, " + exhibitorName << endl;
	
    //cin.ignore();
    //getline(cin,str_input);

    
    
    for (int i = 0; i < db.getDB()["exhibitors"]->getRowLength(); ++i){
        //Search through all org_names in exhibitors
       if(db.getDB()["exhibitors"]->getTable()[i][0].compare(exhibitorName)==0){
            exhibitNameFound = 1;
       }
    }
    
    if(exhibitNameFound==0){
        cout << "You were not found in the database! \n";
        return;
    }else{
        //DBsystem tempDB;
        
        vector<string> orgHeader;          //Search by org_name
        orgHeader.push_back("org_name");
    
        vector<string> OP;                  //Remove all tables that are not the org name
        OP.push_back("==");
    
        vector<string> orgName;          //Search for the ACUTAL org_name entry
        orgName.push_back(exhibitorName);
    
    	managerSearchExhibits(orgHeader, OP, orgName);
        
    }
    
    
    
    
    
}

void exhibitorNumAttendees()
{
	cout << "Hi, " + exhibitorName + ".  Your attendees: " << endl;
    string newTableName = "ATTENDEES FOR: " + exhibitorName;//create new name
    
        vector<string> orgHeader;               //Search by exhibits visted
        orgHeader.push_back("exhibits_visited");
    
        vector<string> OP;                      //Take all entries that have visited said exhibit
        OP.push_back("==");
    
        vector<string> orgName;                 //Search for the ACUTAL exhibits visited entries
        orgName.push_back(exhibitorName);
    
        //Used code from managerSearchExhibits
        //Will select and show the corresponding attendees for the current exhibitor.
    
        Table* pointer = db.SELECT(newTableName, "attendees", orgHeader, OP, orgName); //get select table and assign a pointer to it
    
        if (pointer->getRowLength() < 1) //if there is not anything to show
        {
            cout << "There is no table with that name. \n"; //there must be no table
            return;
        }
        else //otherwise we have something to show
        {
            db.SHOW(pointer->getTableName());   //so show it

            delete pointer;                     //get rid of the table in memory since we don't need it

            return;
        }
    
    
    
    
}

void attendeeName()
{
	
	//cin.ignore();
	//getline(cin, str_input);
	cout << "Hi, " + currAttendeeName + ".  Here is your info: " << endl;
    string newTableName = "ATTENDEE INFO FOR: " + currAttendeeName;//create new name
    
        vector<string> orgHeader;               //Search by attendee name
        orgHeader.push_back("name");
    
        vector<string> OP;                      //Take all entries that have the name
        OP.push_back("==");
    
        vector<string> orgName;                 //Search for the ACUTAL name entries
        orgName.push_back(currAttendeeName);
    
        //Used code from managerSearchExhibits
        //Will select and show the corresponding info for the current attendee.
    
        Table* pointer = db.SELECT(newTableName, "attendees", orgHeader, OP, orgName); //get select table and assign a pointer to it
    
        if (pointer->getRowLength() < 1) //if there is not anything to show
        {
            cout << "You currently have no information in the database! \n"; //there must be no table
            return;
        }
        else //otherwise we have something to show
        {
            db.SHOW(pointer->getTableName());   //so show it

            delete pointer;                     //get rid of the table in memory since we don't need it

            return;
        }
	//using the str_input, serach through the attendee.db and get the values.
	//Make sure to add error chekcing for wrong input or name that is not on the table.

}

void attendeeBooths()
{
	cout << "[Exhibitors " + currAttendeeName +" has visited]\n";
    //Need to search through attendees
    //find currentAttendee name
    //find their booths visited
        vector<string> orgHeader;               //Search by attendee name
        orgHeader.push_back("name");
    
        vector<string> OP;                      //Take all entries that have the name
        OP.push_back("==");
    
        vector<string> orgName;                 //Search for the ACUTAL name entries
        orgName.push_back(currAttendeeName);
    
        //Will select and show the corresponding info for the current attendee.
    
    
        Table* pointer = db.SELECT("", "attendees", orgHeader, OP, orgName); //get select table and assign a pointer to it
    
        //Now, we can search through this table to grab their exhibits_visited
    
    vector<string> exhibitsVisited;
    if(pointer->getRowLength()!=0){   //search through the attendee info in attendees.db.  If there is no info for the attendee, there will be no exhibits visited.
        for (int i = 0; i < pointer->getRowLength(); ++i){
            cout << i+1 << ". " << pointer->getTable()[i][6] << endl;       //index 6 because it is the 7th column
        }
    }else cout << "You have not visited any exhibits. \n" << endl;

	
    
    
    
    
}

void attendeeBoothInfo()
{
	attendeeName();
	attendeeBooths();
}

void attendeeMenu()
{
	cout << "[Attendee Menu for " + currAttendeeName + "]"<<endl;
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
	cout << "   6. Show Total Revenue" << endl;
	cout << "   7. <- Go Back\n" << endl;
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
		boothMenu();		//assign, delete, and list booth location(s) for a given exhibitor
		break;
	case 3:		
		servicesMenu();		//assign, delete, and list booth services to exhibitor
		break;
	case 4:
		attendeeManagerMenu();
		break;
	case 5:
		inventoryMenu();
		break;
	case 6:
		showTotalRevenue();
		break;
	case 7:
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

int verifyNameAndPassword(string tableName,vector<string> IDtuples)
{
	string username = IDtuples[0]; //we pushed username fist
	string password = IDtuples[1]; //password 2nd

	//check for username 
	//if success break and check for password
	//if fails at any point send message and return 1
	for (int i = 0; i < db.database[tableName]->getRowLength(); ++i)
	{
		if (username == db.database[tableName]->getTable()[i][0]) //0 because it should be in the first column
		{
			if (password == db.database[tableName]->getTable()[i][1]) //1 because that is where the password should be
			{
				return 0;
			}
			else
			{
				cout << "Wrong Password.\n";
				cout << "Press ENTER to continue. \n";
				return 1;
			}
		}
	}

	//if we get to this point then we did not find a matching username
	cout << "Could not find username. \n";
	cout << "Press ENTER to continue. \n";
	return 1; //failure
}


void attendeePWScreen()
{
	string pw = ""; //password
	string username = "";
	vector<string> IDtuples;
	int test; //if 0 pass 1 fail

	cin.clear();
	cin.ignore(10000, '\n');
	IDtuples.clear(); //just to be safe

	cout << "Please input the username: ";
	getline(cin, username);
	IDtuples.push_back(username);
    currAttendeeName = username;

	cout << "Please input the password: ";
	getline(cin, pw);
	IDtuples.push_back(pw);


	test = verifyNameAndPassword("attendeesCredentials",IDtuples);

	if (!test) //not test because 0 is pass 
	{
		system("clear");
		attendeeMenu();
	}
	else //failed verifcation
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Verification Failed. Please Try again.***\n" << endl;

	}
}

void exhibitorPWScreen()
{
	string pw = ""; //password
	string username = "";
	vector<string> IDtuples;
	int test; //if 0 pass 1 fail

	cin.clear();
	cin.ignore(10000, '\n');
	IDtuples.clear(); //just to be safe

	cout << "Please input the username: ";
	getline(cin, username);
	IDtuples.push_back(username);
    exhibitorName = username;

	cout << "Please input the password: ";
	getline(cin, pw);
	IDtuples.push_back(pw);

	test = verifyNameAndPassword("exhibitorsCredentials",IDtuples);

	if (!test) //not test because 0 is pass 
	{
		system("clear");
		exhibitorMenu();
	}
	else //failed verifcation
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Verification Failed. Please Try again.***\n" << endl;

	}
}


//high level clearance
void managerPWScreen()
{
	string pw = ""; //password
	string username = "";
	vector<string> IDtuples;
	int test; //if 0 pass 1 fail


	cin.clear();
	cin.ignore(10000, '\n');
	IDtuples.clear(); //just to be safe

	cout << "Please input the username: ";
	getline(cin, username);
	IDtuples.push_back(username);

	cout << "Please input the password: ";
	getline(cin, pw);
	IDtuples.push_back(pw);

	test = verifyNameAndPassword("managerCredentials",IDtuples);

	if (!test) //not test because 0 is pass 
	{
		system("clear");
		exhibitManagerMenu();
	}
	else //failed verifcation
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("clear");
		cout << "***Verification Failed. Please Try again.***\n" << endl;
		return;
		
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
		managerPWScreen();
		break;
	case 2:
		exhibitorPWScreen();
		break;
	case 3:
		attendeePWScreen();
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
		//char path[] = "DBMS/";
		//open 5 main databases
		for(int i = 0; i < 5; i++)
		{
			db.DBParser.sendNewInput("OPEN " + tables[i] + ";");
    		db.execute(); 
		}
		//open verfication DBs
		for (int i = 0; i < 3; ++i)
		{
			db.DBParser.sendNewInput("OPEN " + verificationTables[i] + ';');
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
