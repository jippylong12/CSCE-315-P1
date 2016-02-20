/* _authors_
Marcus Salinas
Brian Ta
Deokman Park
Clifton Sims
Ivan Rupert */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include "DBsystem.h"

using namespace std;


DBsystem::DBsystem()
{
	//not sure if we need anything to be done since create will add the 
	//new tables
}


//if statements based on functionName in Container. 
void DBsystem::execute()
{
    string currentFunction;

	bool open = 0; //for when open is called
	//cout<<"Size of stack: "<<DBParser.contain.functionName.size()<<endl;
	//for the size of the function stack
	for(int i = DBParser.contain.functionName.size(); i > 0; --i)
	{
		
	currentFunction = DBParser.contain.functionName.top(); //get current function
    //cout << "Function name to be run: " << currentFunction << endl;
    
    //-----------------------COMMANDS----------------------//
	if(currentFunction.compare("CREATE") == 0){
		//run OPEN
		string nameCreate = DBParser.contain.parserTableName;
		vector<string> createHeaders = DBParser.contain.parserHeaders;
		vector<string> createKeys= DBParser.contain.parserKeys;
		vector<string> createHeaderTypes= DBParser.contain.parserHeaderTypes;
		vector<int> createHeaderSizes = DBParser.contain.parserHeaderSizes;
		int columnSize = DBParser.contain.parserHeaders.size();
		CREATE(columnSize,nameCreate, createHeaders,createKeys,createHeaderTypes,createHeaderSizes);
	}	
	
	if(currentFunction.compare("OPEN") == 0){ //broken
		//run OPEN
		DBParser.contain.functionName.pop(); //move on to the next function
		open = 1;
		string nameOpen = DBParser.contain.parserTableName;
		OPEN(nameOpen);
	}
	
	
	if (currentFunction.compare("CLOSE") == 0){
        //run CLOSE
        string nameClose = DBParser.contain.parserTableName; //Grab relation name from parser
        CLOSE(nameClose);
        
        currentFunction = DBParser.contain.functionName.top(); //get current function
        cout << "Function name to be run: " << currentFunction << endl;
        
    }
    if (currentFunction.compare("SAVE") == 0){
        //run SAVE
        string nameSave = DBParser.contain.parserTableName;
        cout<<"Save: "<<nameSave<<endl;
        SAVE(nameSave);
        
    }
    if (currentFunction.compare("SHOW") == 0){
	    //run SHOW, checks if the table exists first.
	    bool tableFound = 0;
	    string nameShow = DBParser.contain.parserTableName;
	    
	    if (database.size() != 0){
	    	for (map<string,Table*>::iterator it = database.begin(); it!= database.end(); ++it){
		    	if (nameShow.compare(it->first) == 0){
		   			SHOW(nameShow);
		   			tableFound = 1;
		    		break;
		    	}else tableFound = 0;
	    	}
	    }else cout << "There are no tables in the database!" << endl;
	    
	    if(!tableFound) cout << nameShow << " was not found in the database!" << endl;
        
    }
            
        
    if (currentFunction.compare("UPDATE") == 0){
        //run UPDATE
        string nameUpdate = DBParser.contain.parserTableName;
        vector<string> headerName = DBParser.contain.updateHeaderName;
        string criteria = DBParser.contain.updateCriteria;
        vector<string> replace = DBParser.contain.updateReplace;
        //string compareTo = DBParser.contain.updateCompareTo;
        
        cout << "nameUpdate: " << nameUpdate << endl;
        
        cout << "headerName vector: " << endl;
        for (int i = 0; i < headerName.size(); ++i){
        	cout << headerName[i] << endl;
        }
        
        cout << "criteria: " << criteria << endl;
        
        cout << "replace : " << endl;
       
        //	cout << replace << endl;
        
        
        cout << "replace OP: " << DBParser.contain.updateOP <<  endl;
       
        
        
        
        
        
        
        UPDATE (nameUpdate, headerName, criteria, replace);
        // nameUpdate = "";
        // criteria = "";
        // replace = "";
        
        // headerName.clear();
        
        
    }
    if (currentFunction.compare("INSERT") == 0){
        //run INSERT
        string nameInsert = DBParser.contain.parserTableName;
        vector<string> input = DBParser.contain.insertInput;
        INSERT(nameInsert, input);
        
    }
    if (currentFunction.compare("DELETE") == 0){
        //run DELETE
        string nameDelete = DBParser.contain.parserTableName;
        string compareHeader = DBParser.contain.deleteCompareHeader;
        string compareTo = DBParser.contain.deleteCompareTo;
		string deleteOP = DBParser.contain.deleteOP;
		DELETE(nameDelete,compareHeader,compareTo, deleteOP);
        
    }
    if (currentFunction.compare("EXIT") == 0){
        //run EXIT
        
        EXIT();
    }
	
	
	//---------------------QUERIES------------------------//
	if (currentFunction.compare("QUERY") == 0) 
	{
		cout<<"parserTableName: "<<DBParser.contain.parserTableName<<endl;
		Table newTable(*database[DBParser.contain.parserTableName]);
		//should just make a copy of the table with new name or just rename the new table.
		newTable.setTableName(DBParser.contain.newQueryName);

		database[DBParser.contain.newQueryName] = new Table(newTable);
	}
	if (currentFunction.compare("select") == 0){
		//run select
		//string newTableName,string nameShow, string header ,string comparator, string condition
		string newTableName = DBParser.contain.selectSecondName;
		cout<<"New tAble Name: "<<newTableName<<endl;;
		string nameShow = DBParser.contain.parserTableName;
		cout<<nameShow<<endl;
		string header = DBParser.contain.selectHeader;
		cout<<header<<endl;
		string comparator = DBParser.contain.selectComparator;
		cout<<comparator<<endl;
		string condition = DBParser.contain.selectCondition;
		cout<<condition<<endl;
		Table *newTable (SELECT(newTableName,nameShow,header,comparator,condition));
		DBParser.contain.parserTableName = newTable->getTableName();
		cout<<"Select new Table name: "<<newTable->getTableName()<<endl;
		
		
		
	}
	if (currentFunction.compare("project") == 0){
		//run project
		string t1 = DBParser.contain.parserTableName;
		vector<string> attributes = DBParser.contain.projectAttributes;
		
		cout << "table Name: " << t1 << endl;
		cout << "attrbutes: " << endl;
		for (int i = 0; i < attributes.size(); ++i){
			cout << "\t" << attributes[i] << endl;
		}
		
		//PROJECT(t1,attributes);
		//b <- project (dogs) name; SEG faults in query...
		
	}
	if (currentFunction.compare("rename") == 0){
		//do rename
		string tName = DBParser.contain.renameTableToGet;
		vector<string> tableAttributes = database[DBParser.contain.renameTableToGet]->getHeaders();
		vector<string> renameReplaceAttributes = DBParser.contain.renameReplaceAttributes;
		RENAME(tName,tableAttributes,renameReplaceAttributes);
	}
	if (DBParser.contain.isSetUnion){
		//do Union
		string t1 = DBParser.contain.parserTableName;
		string t2 = DBParser.contain.secondTableName;
		string newName = DBParser.contain.newQueryName;
		SET_UNION(t1,t2,newName);
	}
	if (DBParser.contain.isSetDifference){
		//do set difference
		string tableName1 = DBParser.contain.parserTableName;
		string tableName2 = DBParser.contain.secondTableName;
		SET_DIFFERENCE(tableName1,tableName2);
	}
	if (DBParser.contain.isCrossProduct){
		//do cross product
		string t1 = DBParser.contain.parserTableName;
		string t2 = DBParser.contain.secondTableName;
		CROSS_PRODUCT(t1,t2);
	}
	if(!open) DBParser.contain.functionName.pop(); //move on to the next function
	}
    
}

Table* DBsystem::OPEN(string nameOpen) //bring a table into memory from file
{
	//read in from the comma seperated text file
	string inputLine; //for getline
	string fileName = nameOpen + ".db"; //generate name
	ifstream dbFile(fileName); //create stream
	int testCount = 0;
	if (dbFile.is_open())
	{
		while(!dbFile.eof()) //read until the end
		{
			getline (dbFile,inputLine); //grab the line
			cout<<"String: "<<inputLine<<endl;
			DBParser.sendNewInput(inputLine); //send it to the parser
			execute(); //run the stuff. 
			DBParser.contain.clear(); //wipe the vectors clean. 
		}
	}
	else
		cout << "File does not exists" << endl;
	
	dbFile.close();
}

int DBsystem::CLOSE(string nameClose) //saves and removes table instance from memory
{
	//Just call Save Function.
	this->SAVE(nameClose);
	database.erase(nameClose);
    cout << nameClose << " successfully closed." << endl;
	return 0;
    
	
}


int DBsystem::SAVE(string nameSave) //save the table to file keep in memory
{
//create a new txt file with the name of the file
	//read in the rowLength and columnLenght of table first
	//read in row by row into file
	//close file
	//return 0;
	
	
	
	//output CREATE TABLE
	//get table name and concat table name
	//add (
	//then use the headers to print out them and the type
	//);
	//For each row use INSERT INTO <table name> VALUES FROM (
	//Then fill in with each row by accessing the table at the that row
	//then );
	//Strings need to have "" around them and ints are just numbers
	
	string filename;
	filename = nameSave + ".db";
	ofstream saveFile;
	saveFile.open(filename);
	Table t = *database[nameSave];
	
	saveFile<<"CREATE TABLE " + nameSave + " (";
	int temp = 0;
	
	
	//Get headers and header types
	for (int i = 0; i< database[nameSave]->getHeaders().size(); ++i)
	{
		if(database[nameSave]->getHeaderTypes()[i].compare("INTEGER") ==0)
		{
			saveFile<<database[nameSave]->getHeaders()[i]<<" "<<database[nameSave]->getHeaderTypes()[i];
		}
		else
		{
			saveFile<<database[nameSave]->getHeaders()[i]<<" "<<database[nameSave]->getHeaderTypes()[i]
					<<"("<<database[nameSave]->getHeaderSizes()[i]<<")";
		}
		if(i != database[nameSave]->getHeaders().size()-1)
		{
			saveFile<<", ";
		}
		temp = i;
	}
	saveFile<<") "<<"PRIMARY KEY (";
	//Primary Key
	temp = 0;
	for (int i = 0; i< database[nameSave]->getPrimaryKeys().size() -1; ++i)
	{
		saveFile<<database[nameSave]->getPrimaryKeys()[i]<<", ";
		temp = i + 1;
	}
	saveFile<<database[nameSave]->getPrimaryKeys()[temp]<<");";
	
	saveFile<<endl;
	
	
	
	
	temp = 0;
	for (int i = 0; i<t.getRowLength(); ++i)
	{
		saveFile<<"INSERT INTO " + nameSave + " VALUES FROM (";
		for (int j = 0; j<t.getColumnLength() - 1; ++j)
		{
			saveFile <<"\""<< t.getTable()[i][j]<<"\""<<", ";
			temp = j;
		}
		if(i != t.getRowLength() - 1)
			saveFile<<t.getTable()[i][temp + 1]<<");"<<endl;
		else
			saveFile<<t.getTable()[i][temp + 1]<<");";
	}
	
	
	saveFile.close();
	return 0;
}

int DBsystem::SHOW(string nameShow) //print out the table currently in memory
{
	//nested for loop
	//print each cell in the table
	//return 0;
	//First, print the name of the table
    cout << "\t\t\t ----------------------------------- " <<endl;
    cout << setw(47)<<database[nameShow]->getTableName() << setw(47) << endl;
    cout << "\t\t\t ----------------------------------- " <<endl;
	//print headers.
	for (int i = 0; i< database[nameShow]->getHeaders().size(); ++i)
	{
        cout << setw(25) << '[' + database[nameShow]->getHeaders()[i] + ']';
	}
   
	//print table
	for (int i = 0; i<database[nameShow]->getRowLength(); ++i)
	{
		cout << endl;
		for (int j = 0; j<database[nameShow]->getColumnLength(); ++j)
		{
			cout << setw(25);
			cout << database[nameShow]->getTable()[i][j] << setw(25);
			if(j==database[nameShow]->getColumnLength()-1){
				cout << setw(0);
			}
		}

	}
	cout << endl << endl;
	return 0;
	
	
}

Table* DBsystem::CREATE(int columnCreate, string nameCreate,vector<string> createHeaders, vector<string> createKeys, vector<string> createTypes, vector<int> sizes) //create a new table in memory
{
	//intiliaze new Table
	Table* newTable = new Table(columnCreate,nameCreate,createHeaders, createKeys, createTypes,sizes);
	cout<<"Map size: "<<database.size()<<endl;
	database[nameCreate] = newTable; //add the table to the database
	cout<<"Map size: "<<database.size()<<endl;
	//return new Table
	return newTable;
	
}

//updates a record in the database given certain criteria
int DBsystem::UPDATE(string nameUpdate, vector<string> headerName, string criteria, vector<string> replace)
{
	//go to table nameUpdate
	//search headervector for headerName to find column
	//search that column for the criteria
	//replace the criteria with replace
	//update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
	
 	//UPDATE animals SET kind = MOG WHERE years == 3;
	
	
	int minIndex = min(database[nameUpdate]->getHeaders().size(), headerName.size());   //store size mismatch
	
	vector<int> colPos; 		  //store which column(s) to be updated
	vector<int> rowPos;			  //store the position of row(s) to be updated			
	vector<int> colComparePos;	  //store the position of column used to compare
	vector<int> replacePos;		  //trying to store the position of the replace vector so we know what to replace
	string updateOP = DBParser.contain.updateOP; //grab OP
	vector<vector<string>> tempTable = database[nameUpdate]->getTable(); //get table info
	//store which rows to be updated
	//need to iterate through all columns
	//int row, col;
	
//UPDATE animals SET kind = fatANIMAL WHERE age == 1;

	
	for(int i = 0; i < minIndex; ++i){			//Go through table headers and find header to be updated
		for (int j = 0; j < database[nameUpdate]->getHeaders().size(); ++j){
			if(database[nameUpdate]->getHeaders()[j].compare(headerName[i]) == 0){
				colPos.push_back(j);			//Store the positions where the header names match
			}
		}
	}
	
	bool cmpHeaderFound = 0;
	cout << "DBHeaders: " << database[nameUpdate]->getHeaders().size() << endl;
	
	for(int i = 0; i < minIndex; ++i){		    	//Go through table headers and headers to be COMPARED
		for (int j = 0; j < database[nameUpdate]->getHeaders().size(); ++j){
			
			if(database[nameUpdate]->getHeaders()[j].compare(criteria) == 0){
				colComparePos.push_back(j);			//Store the positions where te header matches COMPARED header
				
				cmpHeaderFound = 1;
			} 
		}
	}
	cout << "updateCompareTo: " << DBParser.contain.updateCompareTo << endl;
	if (!cmpHeaderFound){ 
		cout << "Comparison header not found.  Please try again." << endl; 
		return 0; 
	}
	
	
	
	//In our table, 
	//Go through the rows of the COMPARED column and see if its elements match up
	//Store the respective position of the row
	
	for(int i = 0; i <database[nameUpdate]->getRowLength(); ++i ){ 
		for (int j = 0; j < colPos.size(); ++j){
			if(!isdigit(DBParser.contain.updateCompareTo[0])){	//see if we are comparing strings
				if(database[nameUpdate]->getTable()[i][colComparePos[j]].compare(DBParser.contain.updateCompareTo)==0  && updateOP.compare("==")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
				    replacePos.push_back(j);
				}
				if(database[nameUpdate]->getTable()[i][colComparePos[j]].compare(DBParser.contain.updateCompareTo)!=0  && updateOP.compare("!=")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
					replacePos.push_back(j);
				}
			}else{												//we're comparing ints
				int updateCmpTo = stoi(DBParser.contain.updateCompareTo);
				int updateEntry = stoi(database[nameUpdate]->getTable()[i][colComparePos[j]]);
				cout << "updateEntry ? cmpTo: " <<updateEntry << updateOP << updateCmpTo << endl;
			
			
				if(updateEntry >= updateCmpTo && updateOP.compare(">=")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
			    	replacePos.push_back(j);
				}
					if(updateEntry > updateCmpTo && updateOP.compare(">")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
			    	replacePos.push_back(j);
				}
					if(updateEntry <= updateCmpTo && updateOP.compare("<=")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
			    	replacePos.push_back(j);
				}
					if(updateEntry < updateCmpTo && updateOP.compare("<")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
			    	replacePos.push_back(j);
				}
					if(updateEntry == updateCmpTo && updateOP.compare("==")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
			    	replacePos.push_back(j);
				}
					if(updateEntry != updateCmpTo && updateOP.compare("!=")==0){
					rowPos.push_back(i);			//Store the position of the row where criteria is met
			    	replacePos.push_back(j);
				}
			
			}

		}
	}
	
	
	
			for (int j = 0; j < rowPos.size(); ++j){		//update the table with new element
					for (int i = 0; i < colPos.size(); ++i){
						tempTable[rowPos[j]][colPos[i]] = replace[replacePos[i]];			//FK my life
					}
			}
			
		
		
		
		
		
		//	}
	//	cout << 2 << endl;
	//for (int i = 0; i < database[nameUpdate]->getRowLength(); ++i){
	//	if(database[nameUpdate]->getTable()[i][colPos[i]].compare(criteria)==0){
	//		rowPos.push_back(i);				//Store the rows which meet the criteria
	//	}
	//} 
	
	 	
/*
UPDATE animals SET name = BirdName2 WHERE kind != bird;
UPDATE animals SET name = NEWJOE, kind = young WHERE age > 1; 
UPDATE exhibitors SET address = 123_College_Dr. WHERE fax > 1;
UPDATE org_name SET address = 123_College_Dr. WHERE fax > 1;
		*/
	
	
	//Need to add conditional DBParser.contain.updateOP
	//	cout << 3 << endl;
	// for (int i = 0; i < colPos.size(); ++i){
	// 	for (int j = 0; j < rowPos.size(); ++j){
	// 		tempTable[rowPos[j]][colPos[i]] = replace[0];			//updates to default values
	// 	}
	// }
	
	database[nameUpdate]->setTable(tempTable);
	//delete tempTable;
	tempTable.clear();
	replace.clear();
	colPos.clear(); 		  //store which column(s) to be updated
	rowPos.clear();			  //store the position of row(s) to be updated			
	colComparePos.clear();	  //store the position of column used to compare
	replacePos.clear();	
	headerName.clear();
	DBParser.contain.updateHeaderName.clear();
	DBParser.contain.updateReplace.clear();
	

	// for (int i = 0; i < database[nameUpdate]->getColumnLength(); ++i)
	// {
	// 	if (database[nameUpdate]->getHeaders()[i].compare(headerName)==0)
	// 	{
	// 		col = i;
	// 	}
	// }
	// for (int i = 0; i < database[nameUpdate]->getRowLength(); ++i)
	// {
	// 	if (database[nameUpdate]->getTable()[i][col].compare(criteria)==0)
	// 	{
	// 		row = i;
	// 	}
	// }
	
	// tempTable[row][col] = replace;
	// database[nameUpdate]->setTable(tempTable);

	
    
    	return 0;
	
}

//Takes in the input of nameInsert and returns an int for error checking.
int DBsystem::INSERT(string nameInsert, vector<string> input)
{
	if (input.size() != database[nameInsert]->getHeaders().size())
	{
		cout << "Did not insert the correct amount of information." << endl;
		return -1;
	}

	vector<vector<string>> tempTable = database[nameInsert]->getTable();

	tempTable.push_back(input);

	database[nameInsert]->setTable(tempTable);

	int tempRow = database[nameInsert]->getRowLength() + 1;
	database[nameInsert]->setRowLength(tempRow);
    return 0;

}

//nameDelete may not be neede depending on the implementation of the Parser.
//Parser may end up finding the row and may only need one input here.
int DBsystem::DELETE(string nameDelete, string compareHeader, string compareTo, string deleteOP)
{
	vector<vector <string> > tempTable;
	tempTable = database[nameDelete]->getTable();
	string tableComparer;
	int rowToDelete;
	int columnToCheck;
	bool foundInHeader = 0;
	bool isString = 0;
	
	for(int i = 0; i<database[nameDelete]->getColumnLength();++i)
	{
		if(database[nameDelete]->getHeaders()[i].compare(compareHeader) == 0 ) // if we find the matching header
		{
			columnToCheck = i; //keep track of column
			foundInHeader = 1;
			break; // end for loop
		}
	}
	if(!foundInHeader)
	{
    	cout<<"Not Found in Header.\n";
		return 0;
	}
	cout<<"Column To check: "<<columnToCheck<<endl;
	cout<<"rowLength before loop: "<<database[nameDelete]->getRowLength()<<endl;
	cout << "deleteOP: " << deleteOP;
	
	
	for(int i = 0; i<database[nameDelete]->getRowLength(); ++i)
	{
		tableComparer = tempTable[i][columnToCheck];
		cout<<"Comparer: "<<tableComparer<<endl;
		//Checks for equality of strings
		
	
	
	
	//Check if what we want to compare is a string...
		
		
	if(!isdigit(DBParser.contain.deleteCompareTo[0])){
		if(deleteOP.compare("==") == 0 && tableComparer.compare(DBParser.contain.deleteCompareTo)==0){
			tempTable.erase(tempTable.begin() + i); //delete the row
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
			continue;
		}
		 //Inequality of strings
		if(deleteOP.compare("!=") == 0 && tableComparer.compare(DBParser.contain.deleteCompareTo)!=0){
			tempTable.erase(tempTable.begin() + i); //delete the row
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
			continue;
		}
	}else{
	
		
		if(deleteOP.compare("==") == 0 && stoi(tableComparer) == stoi(DBParser.contain.deleteCompareTo)){ //DELETE WHERE EQUALS for INTS
			tempTable.erase(tempTable.begin() + i); //delete the row
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
		}
		
		
		
		
		if(deleteOP.compare(">=") == 0 && stoi(tableComparer) >= stoi(DBParser.contain.deleteCompareTo)){
		 	tempTable.erase(tempTable.begin() + i); //delete the row
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
		 }
	    if(deleteOP.compare(">") == 0 && stoi(tableComparer) > stoi(DBParser.contain.deleteCompareTo)){
			tempTable.erase(tempTable.begin() + i); //delete the row
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
		}
	    if(deleteOP.compare("<=") == 0 && stoi(tableComparer) <= stoi(DBParser.contain.deleteCompareTo)){
		 	tempTable.erase(tempTable.begin() + i); //delete the ro
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
		 	
		 }
		 if(deleteOP.compare("<") == 0 && stoi(tableComparer) < stoi(DBParser.contain.deleteCompareTo)){
		 	tempTable.erase(tempTable.begin() + i); //delete the row
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
		 	
		 }
		 //Inequality of ints
		 if(deleteOP.compare("!=") == 0 && stoi(tableComparer) != stoi(DBParser.contain.deleteCompareTo)){ //DELETE WHERE NOT EQUALS	
		 	tempTable.erase(tempTable.begin() + i); //delete the row
			database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
			cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
			--i;
		 }
	}
	
		
		
		
		// if(tableComparer.compare(compareTo) == 0)
		// {
		// 	tempTable.erase(tempTable.begin() + i); //delete the row
		// 	database[nameDelete]->setRowLength(database[nameDelete]->getRowLength()-1); // change row length
		// 	cout<<"rowLength inside loop: "<<database[nameDelete]->getRowLength()<<endl;
		// 	--i;
		// }
	
	}
	
	cout<<"rowLength after loop: "<<database[nameDelete]->getRowLength()<<endl;
    database[nameDelete]->setTable(tempTable);
    //return 0;

}

//exits program and deletes everything not saved
void DBsystem::EXIT()
 {
 	
	for(map<string, Table*>::iterator itr = database.begin(); itr != database.end(); itr++){
		delete itr->second; //deletes all *Table pointers
	}
	cout<<"Exiting...Goodbye\n";
	exit(EXIT_SUCCESS);
 }

//----------------Database queries---------------//

Table* DBsystem::SELECT(string newTableName,string nameShow, string header ,string comparator, string condition) 
{
	//Select multiple columns and join them together by a certain condition
	cout<<1<<endl;
	string newName;
	Table* tempTable = new Table();
	vector< vector<string> > origT = database[nameShow]->getTable();
	vector< vector<string> > returnT;
	int newRow = 0;
	int col = 0;
	vector<string> tempHeaders = database[nameShow]->getHeaders();
	
	
	for (int i = 0; i<tempHeaders.size(); ++i)
	{
		cout<<11<<endl;
		if (header.compare(tempHeaders[i]) == 0)
		{
			col = i;
			break;
		}
	}
	
	if (comparator.compare("==") == 0)
	{
		cout<<12<<endl;
		for (int i = 0; i < database[nameShow]->getRowLength(); ++i)
		{
			if (origT[i][col].compare(condition) == 0)
			{
				cout << 12.5 << endl;
				returnT.push_back(origT[i]);			
				newRow++;
			}
		}
		cout << 12.75 << endl;
	}
	
	else if (comparator.compare(">") == 0)
	{
		cout<<13<<endl;
		for (int i = 0; i < database[nameShow]->getRowLength(); ++i){
			cout<<"Condition: "<<condition<<endl;
			cout<<"Value: "<<origT[i][col]<<endl;
			if (origT[i][col].compare(condition) < 0)
			{
				returnT.push_back(origT[i]);
				newRow++;
			}
		}
	}
	
	else if (comparator.compare("<") == 0)
	{
		cout<<14<<endl;
		for (int i = 0; i < database[nameShow]->getRowLength(); ++i){
			if (origT[i][col].compare(condition) < 0)
			{
				returnT.push_back(origT[i]);
				newRow++;
			}
		}
		
	}
	
	else if (comparator.compare("<=") == 0)
	{
		cout<<15<<endl;
		for (int i = 0; i < database[nameShow]->getRowLength(); ++i){	
			if (origT[i][col].compare(condition) < 0 || origT[i][col].compare(condition) == 0)
			{
				returnT.push_back(origT[i]);
				newRow++;
			}
		}
	}
	else if (comparator.compare(">=") == 0)
	{
		for (int i = 0; i < database[nameShow]->getRowLength(); ++i){	
			if (origT[i][col].compare(condition) == 0 || origT[i][col].compare(condition) > 0)
			{
				returnT.push_back(origT[i]);
				newRow++;
			}
		}
	}
	else if (comparator.compare("!=") == 0){
		for (int i = 0; i < database[nameShow]->getRowLength(); ++i){
			if (origT[i][col].compare(condition) != 0)
			{
				returnT.push_back(origT[i]);
				newRow++;
			}
		}
	}

	newName = newTableName;
	tempTable->setTableName(newTableName);
	tempTable->setHeader(database[nameShow]->getHeaders());
	tempTable->setHeaderTypes(database[nameShow]->getHeaderTypes());
	tempTable->setHeaderSizes(database[nameShow]->getHeaderSizes());
	tempTable->setPrimaryKeys(database[nameShow]->getPrimaryKeys());
	tempTable->setColumnLength(tempTable->getHeaders().size());
	tempTable->setRowLength(newRow);
	tempTable->setTable(returnT);
	
	database[newTableName] = tempTable;
	return tempTable;
}

vector<Table*> DBsystem::PROJECT(string t1, vector<string> attributes)
{
    vector<Table*> t;
    Table* tempTable = database[t1];
    vector<string> attr;
    vector<int> pos;
    vector< vector <string> > tempT = database[t1]->getTable();
    vector< vector <string> > retT(30, vector<string>(30, "")); //Had to initialize this
	cout<<"Table col Length: "<<tempTable->getColumnLength();
	cout<<"Table row Length: "<<tempTable->getRowLength();
    
    cout << t1 << " PROJECTION OF: "  << endl;
    for (int i = 0; i < database[t1]->getColumnLength(); ++i){          //Go through DB
        if (database[t1]->getHeaders()[i].compare(attributes[i])==0){   //See if and DB header fits attribute
            pos.push_back(i);           				//Store corresponding position in vector
            cout << database[t1]->getHeaders()[i] << " " << endl;
        }else { cout << "Column " << i+1 << " not projected."<< endl; }
    }
    for (int i = 0; i < pos.size(); ++i){
        attr.push_back(attributes[pos[i]]);			        //Store the corresponding attribute
    }
    for (int i = 0; i < pos.size(); ++i){
        for (int j = 0; j < database[t1]->getColumnLength(); ++j){
            retT[j][i] = tempT[j][pos[i]];			        //Construct a new table with the proper selected column
        }
    }
    tempTable->setHeader(attr);
    tempTable->setTable(retT);
	tempTable->setColumnLength(database[t1]->getHeaders().size());
    
    return t;
	
}

Table* DBsystem::RENAME(string tName, vector<string> tableAttributes, vector<string> replaceAttributes)
{
    Table *t;
    int rowCounter;
    for (int i = 0; i < database[tName]->getColumnLength(); ++i){
        if(tableAttributes.size()==replaceAttributes.size())
        {  //Check if we need to add back existing table headers
            //replaceAttributes.push_back(tableAttributes[i]);
            tableAttributes[i] = replaceAttributes[i];      //Assume that attribute names to be replaced are in the same index
        }
        else
        {
            replaceAttributes.push_back(tableAttributes[max(tableAttributes.size()-1, replaceAttributes.size()-1)]);
        }
    }
    //database[tName]->setHeader(replaceAttributes);      //Rename the headers.

    //database[tName]->setColumnLength();

    
    return database[tName];
}

Table* DBsystem::SET_UNION(string t1, string t2, string newName)
{
	//check if the headers are the same size and the same values
	
	//push_back the table ofone 
	//push back the rows of the other table
	//possibly check each time to see if there are any duplicates. 
	//return new table
	cout << 99;
	//if(database[t1]->getHeaders().size() == database[t2]->getHeaders().size())
	//{

		//intiliaze new Table for holding the union
		//create a  new table
		cout << 100;
		Table* unionTable = new Table(database[t1]->getColumnLength(),newName, database[t1]->getHeaders(),
			database[t1]->getPrimaryKeys(),database[t1]->getHeaderTypes(),database[t1]->getHeaderSizes());
		database[newName] = unionTable; //add the table to the database
		
		unionTable->setTable(database[t1]->getTable());// change the header
		unionTable->setRowLength(database[t1]->getRowLength());//change the row Length
		
		
		vector< vector <string> > copyTable;
		copyTable = unionTable->getTable();
		int count = unionTable->getRowLength();
		//add all the elements from B 
		cout << 101;
		for(int i = 0; i < database[t2]->getRowLength(); ++i)
		{
			copyTable.push_back(database[t2]->getTable()[i]);
			count+=1;
		}
		cout << 102;
		unionTable->setTable(copyTable);
		unionTable->setRowLength(count);
		
		return unionTable;
//	}	
	//else
	//{
		cout<<"The headers aren't the same size.\n";
		return 0;
	//}
    //Returns a Table of the Union
	//return the union
	
}



Table* DBsystem::SET_DIFFERENCE(string tableName1, string tableName2)
{
	Table* differenceTable = database[tableName1]; //to return
	
	vector< vector<string> > tempT1; // for doing the difference
	vector< vector<string> > tempT2;
	
	//make a copy of each table
	tempT1 = database[tableName1]->getTable(); 
	tempT2 = database[tableName2]->getTable();
	string newName = "Difference " + tableName1	 + ' ' + tableName2;
	int rowCount = 0;
	//check if the headers are the same size and the same values
	if(database[tableName1]->getHeaders().size() == database[tableName2]->getHeaders().size())
	{
		
		*differenceTable = *database[tableName1]; //set them equal not sure why this works. 
		for(int i = 0; i< database[tableName2]->getRowLength(); ++i) // keep the second table equal 
		{
			for(int j = 0; j < differenceTable->getRowLength(); ++j) //for each row in the first table
			{
				for(int k = 0; k <differenceTable->getColumnLength(); ++k) // for each column in the first table
				{
					if(tempT2[i][k] != tempT1[j][k]) //if there is a mismatch
					{
						//erase from table1
						tempT1.erase(tempT1.begin() + j); //j will be the row
						//rease from table2
						tempT2.erase(tempT2.begin() + i); // i will be the row it's found
						//need adjust for loops to accomodate for the removed rows. 
						j = 0; //need to search over again
					}
				}
				
			}
		}
	}
	
	
	//combine the tables into one
	cout << "tempT2 size: " << tempT2.size() << endl; 
	for(int i = 0; i< tempT2.size(); ++i)
	{
		tempT1.push_back(tempT2[i]);
	}
	//rowCount = tempT1.size();
	
	differenceTable->setTable(tempT1);
	differenceTable->setTableName(newName);

	//Row length will be at most the sum of both of the Tables' rows
	differenceTable->setRowLength(database[tableName1]->getRowLength() + database[tableName2]->getRowLength());
	
	//differenceTable->setColumnLength(differenceTable()->getColumnLength())
	return differenceTable;
}

Table* DBsystem::CROSS_PRODUCT(string t1, string t2)
{
    //The cross product of two tables A x B builds a huge virtual table by pairing every row of A with every row of B.

    Table* returnTable = database[t1];                   //Table to be produced
            
    vector<string> newHeaders;
    int t1_rowLength = database[t1]->getRowLength();
    int t1_columnLength = database[t1]->getColumnLength();
    int rowCounter = 0;
    vector<string> t1Rows;
    int t2_rowLength = database[t2]->getRowLength();
    int t2_columnLength = database[t2]->getColumnLength();
    vector< vector<string> > tempTable;                 //for setting later. 
    vector<string> t2Rows;
    vector<string> joinedRows;                          //Store a vector for t1 x t2
    
    cout << "test1" << endl;
    
    //Get the attributes for both rows, concatenate them to be the new headers//
    for (int i = 0; i < database[t1]->getHeaders().size(); ++i)
    {
        newHeaders.push_back(database[t1]->getHeaders()[i]);
        
    }
    for (int i = 0; i < database[t2]->getHeaders().size(); ++i){
        newHeaders.push_back(database[t2]->getHeaders()[i] );
    }
    
    //set memeber items for the new table
    
    string newName = "Cross Product " + t1	 + ' ' + t2;
    returnTable->setTableName(newName); // change name
    returnTable->setColumnLength( t1_columnLength + t2_columnLength);  //columnLength
    returnTable->setHeader(newHeaders);                   //Set the new Table headers
    returnTable->setPrimaryKeys(database[t1]->getPrimaryKeys()); //primary keys
    returnTable->setHeaderTypes(database[t1]->getHeaderTypes()); //header types
    
	
	
    for (int i = 0; i < t1_rowLength; ++i)
    {          //
        t1Rows = database[t1]->getTable()[i];           //Grab rows from Table 1
        for (int j = 0; j < t2_rowLength; ++j)
        {
            t2Rows = database[t2]->getTable()[j];       //Grab rows from Table 2
            joinedRows = t1Rows;                        //Store 1..i rows from t1 (table 2 column times)
            for (int k = 0; k < t2Rows.size(); ++k)
            {
                joinedRows.push_back(t2Rows[k]);        //Push all rows from t2 after the 1..ith row of t1
				
			}
            tempTable.push_back(joinedRows); // push back the row into the tempTable
            rowCounter+=1;
        }
    }
	//cout<<"rowCounter: "<<rowCounter<<endl;
    //rowCounter = 12;
    
    returnTable->setTable(tempTable);                     //add the new table
    returnTable->setRowLength(rowCounter); // change the rows.
    
    return returnTable;

}


















