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
	Table* temp = 0;
	bool open = 0; //for when open is called
	bool setTable = 0;
	
	
	cout<<"Size of stack: "<<DBParser.contain.functionName.size()<<endl;
	//for the size of the function stack
	
	
	for(int i = DBParser.contain.functionName.size(); i > 0; --i)
	{
		
	currentFunction = DBParser.contain.functionName.top(); //get current function
    //cout << "Function name to be run: " << currentFunction << endl;
    
    //-----------------------COMMANDS----------------------//
	if(currentFunction.compare("CREATE") == 0){
		//run OPEN
		string nameCreate = DBParser.contain.nameCreate;
		vector<string> createHeaders = DBParser.contain.createHeaders;
		vector<string> createKeys= DBParser.contain.createKeys;
		vector<string> createHeaderTypes= DBParser.contain.createTypes;
		vector<int> createHeaderSizes = DBParser.contain.sizes;
		int columnSize = DBParser.contain.createHeaders.size();
		CREATE(columnSize,nameCreate, createHeaders,createKeys,createHeaderTypes,createHeaderSizes);
	}	
	
	if(currentFunction.compare("OPEN") == 0){ //broken
		//run OPEN
		DBParser.contain.functionName.pop(); //move on to the next function
		open = 1;
		string nameOpen = DBParser.contain.nameOpen;
		OPEN(nameOpen);
	}
	
	
	if (currentFunction.compare("CLOSE") == 0){
        //run CLOSE
        string nameClose = DBParser.contain.nameClose; //Grab relation name from parser
        CLOSE(nameClose);
    }
    if (currentFunction.compare("SAVE") == 0){
        //run SAVE
        string nameSave = DBParser.contain.nameSave;
        cout<<"Save: "<<nameSave<<endl;
        SAVE(nameSave);
        
    }
    if (currentFunction.compare("SHOW") == 0){
	    //run SHOW
	    string nameShow = DBParser.contain.nameShow;
	    SHOW(nameShow);
        
    }
            
        
    if (currentFunction.compare("UPDATE") == 0){
        //run UPDATE
        string nameUpdate = DBParser.contain.nameUpdate;
        vector<string> headerName = DBParser.contain.updateHeaderName;
        vector<string> replace = DBParser.contain.updateReplace;
        vector<string> updateOperand1 = DBParser.contain.updateOperand1;
        vector<string> updateOperand2 = DBParser.contain.updateOperand2;
        vector<string> updateOP = DBParser.contain.updateOP;
        
        cout << "nameUpdate: " << nameUpdate << endl;
        
        cout << "headerName vector: " << endl;
        for (int i = 0; i < headerName.size(); ++i){
        	cout << headerName[i] << endl;
        }
 
        //	cout << replace << endl;
      
        UPDATE(nameUpdate, headerName, replace, updateOperand1,updateOperand2,updateOP);
    }
    if (currentFunction.compare("INSERT") == 0){
        //run INSERT
		vector<string> input;

        string nameInsert = DBParser.contain.nameInsert;
        cout<<"nameInsert: "<<nameInsert<<endl;
		if (setTable) //when we do insert values from relation
		{
			for (int i = 0; i < temp->getRowLength(); ++i)
			{
				input = temp->getTable()[i]; //get row
				INSERT(nameInsert, input); //insert into table
			}
		}
		else
		{
			input = DBParser.contain.insertInput;
			INSERT(nameInsert, input);
		}

        
    }
    if (currentFunction.compare("DELETE") == 0){
        //run DELETE
        string nameDelete = DBParser.contain.nameDelete;
        vector<string> deleteOperand1 = DBParser.contain.deleteOperand1;
        vector<string> deleteOperand2 = DBParser.contain.deleteOperand2;
		vector<string> deleteOP = DBParser.contain.deleteOP;
		DELETE(nameDelete,deleteOperand1,deleteOperand2, deleteOP);
        
    }
    if (currentFunction.compare("EXIT") == 0){
        //run EXIT
        EXIT();
    }
	
	
	//---------------------QUERIES------------------------//
	if (currentFunction.compare("QUERY") == 0) 
	{
		cout<<"Query: "<<DBParser.contain.lhsQuery<<endl;
		if(setTable)
		{
			Table newTable0(*temp);
			//should just make a copy of the table with new name or just rename the new table.
			newTable0.setTableName(DBParser.contain.lhsQuery);
			database[DBParser.contain.lhsQuery] = new Table(newTable0);

		}
		else
		{
			Table newTable1(*database[DBParser.contain.rhsQuery]);	
			//should just make a copy of the table with new name or just rename the new table.
			newTable1.setTableName(DBParser.contain.lhsQuery);
			database[DBParser.contain.lhsQuery] = new Table(newTable1);
		}

	}
	if (currentFunction.compare("select") == 0){
		//run select
		string newTableName;
		
		string nameSelect = DBParser.contain.nameSelect;
		cout<<"Select Table Name: "<<nameSelect<<endl;
		vector<string> header = DBParser.contain.selectHeader; //lhs
		vector<string> selectOP = DBParser.contain.selectOP; 
		vector<string> condition = DBParser.contain.selectCondition; //rhs

		if(setTable) // if we have set a Table the new name needs ot be the temp name we gave it
		{
			newTableName = temp->getTableName(); //get the table name of the temp table
		}
		else //esle we are just running once. 
		{
			newTableName = "SELECT " + nameSelect;	
		}
		cout<<"New Table Name: "<<newTableName<<endl;;
		
		
		Table *newTable (SELECT(newTableName,nameSelect,header,selectOP,condition));
		Table* selectReturnTable = newTable;
		
		if(DBParser.contain.functionName.size() > 1) //if we have more than one query to run
		{
			temp = selectReturnTable;
			setTable = 1;
		}
		
		cout<<"Select new Table name: "<<newTable->getTableName()<<endl;
	}
	if (currentFunction.compare("project") == 0){
		string t1;
		vector<string> attributes;
		//run project
		if (setTable)
		{
			t1 = temp->getTableName();
			attributes = temp->getHeaders();

		}
		else
		{
			t1 = DBParser.contain.nameProject;
			attributes = DBParser.contain.projectAttributes;
		}

		cout<<"Name Project: "<<t1<<endl;
		
		
		Table* newTable(PROJECT(t1, attributes));
		Table* projectReturnTable = newTable;

		if (DBParser.contain.functionName.size() > 1)
		{
			temp = projectReturnTable;
			setTable = 1;
		}

		//b <- project (dogs) name; SEG faults in query...
		
	}
	if (currentFunction.compare("rename") == 0){
		string tName;
		vector <string> tableAttributes;
		vector<string> renameReplaceAttributes;
			
		//do rename
		if (setTable) //a function ran before this
		{
			tName = temp->getTableName();
			tableAttributes = temp->getHeaders();
		}
		else //just rename
		{
			tName = DBParser.contain.nameRename;
			tableAttributes = database[DBParser.contain.nameRename]->getHeaders();
		}
		renameReplaceAttributes = DBParser.contain.renameReplaceAttributes;

		
		Table* newTable(RENAME(tName, tableAttributes, renameReplaceAttributes));
		Table* renameReturnTable = newTable;

		if (DBParser.contain.functionName.size() > 1)
		{
			temp = renameReturnTable;
			setTable = 1;
		}

	}
	if (currentFunction.compare("UNION") == 0){
		//do Union
		string t2;
		
		string t1 = DBParser.contain.nameUnion1;
		cout<<"T1: "<<t1<<endl;
		
		if(setTable) // if we had a function run before
		{
			t2 = temp->getTableName();
		}
		else // it's just a union call
		{
			t2 = DBParser.contain.nameUnion2;
		}
		cout<<"T2: "<<t2<<endl;
		string newName = DBParser.contain.lhsQuery;
		cout<<"newName: "<<newName<<endl;
		
		cout<<"About to run Union..\n";
		
		Table* newTable(SET_UNION(t1, t2, newName));
		Table * unionReturnTable = newTable;
		if(DBParser.contain.functionName.size() > 1) //if there are more functions to run
		{
			temp = unionReturnTable; //assign tem table
			setTable = 1;
		}
	}
	if (currentFunction.compare("DIFFERENCE") == 0){
		string tableName2;
		
		//do set difference
		string tableName1 = DBParser.contain.nameDifference1;
		if(setTable)
		{
			tableName2 = temp->getTableName();
		}
		else
		{
			tableName2 = DBParser.contain.nameDifference2;	
		}
		
		string newName = DBParser.contain.lhsQuery;

		
		Table* newTable(SET_DIFFERENCE(tableName1, tableName2, newName));
		
		Table* differenceReturnTable = newTable;
		if(DBParser.contain.functionName.size() > 1)
		{
			temp = differenceReturnTable;
			setTable = 1;
		}
	}
	if (currentFunction.compare("CROSS PRODUCT") == 0){
		string t2;
		
		//do cross product
		string t1 = DBParser.contain.nameCrossProduct1;
		if(setTable)
		{
			t2 = temp->getTableName();
		}
		else
		{
			t2 = DBParser.contain.nameCrossProduct2;
			setTable = 1;
		}
		
		string newName = DBParser.contain.lhsQuery;

		
		Table* newTable(CROSS_PRODUCT(t1, t2, newName));
		Table* crossProductReturnTable = newTable;
		if(DBParser.contain.functionName.size() > 1)
		{
			temp = crossProductReturnTable;
			setTable = 1;
			
		}
	}
	cout<<"Popping off: "<<endl;
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
	return 0;
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
	
	
	//INSERTS
	
	temp = 0;
	for (int i = 0; i<t.getRowLength(); ++i)
	{
		saveFile<<"INSERT INTO " + nameSave + " VALUES FROM (";
		if (t.getColumnLength() == 1) // for when there is only one column
		{
			if (i != t.getRowLength() - 1)
			{
				saveFile << "\"" << t.getTable()[i][0] << "\"" << ");" << endl;
				continue;
			}
			else
			{
				saveFile << "\"" << t.getTable()[i][0] << "\"" << ");";
			}			
		}
		else //when column length is greater than 1
		{
			for (int j = 0; j<t.getColumnLength() - 1; ++j)
			{
				saveFile << "\"" << t.getTable()[i][j] << "\"" << ", ";
				temp = j;
			}
			if (i != t.getRowLength() - 1)
				saveFile << t.getTable()[i][temp + 1] << ");" << endl;
			else
				saveFile << t.getTable()[i][temp + 1] << ");";
		}

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
int DBsystem::UPDATE(string nameUpdate, vector<string> headerName, vector<string> replace, vector<string> updateOperand1, vector<string> updateOperand2,vector<string> updateOP)
{
	
	//go to table nameUpdate
	//search headervector for headerName to find column
	//search that column for the criteria
	//replace the criteria with replace
	//update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
	
 	//UPDATE animals SET kind = MOG WHERE years == 3;
	
	//headerName holds the header to change
	//replace holds the value we want to replace in that headerName given that where is true
	// operand1 is the lhs of WHERE arguement
	//operand2 is the rhs
	//updateOP is the operand for the WHERE arguement
	
	vector<int> headerColPos; 		  //store which column to check for header
	vector<int> whereColPos;			  //store which column to look at for the where fuction			
	vector<vector<string>> tempTable = database[nameUpdate]->getTable(); //get table info
	//store which rows to be updated
	//need to iterate through all columns
	//int row, col;
	
//UPDATE animals SET kind = fatANIMAL WHERE age == 1;

	//Go through table headers and find header to be updated
	for (int i = 0; i < headerName.size(); ++i) //for headers
	{
		for (int j = 0; j < database[nameUpdate]->getHeaders().size(); ++j)
		{
			if (database[nameUpdate]->getHeaders()[j].compare(headerName[i]) == 0) //if we find a match in the header
			{
				headerColPos.push_back(j); //push back it's location in header
			}
			if (database[nameUpdate]->getHeaders()[j].compare(updateOperand1[i]) == 0)
			{
				whereColPos.push_back(j); //push back the header locations
			}
		}
	}


	//go through table with the columns in colPos and use where condidtion to 


	for (int i = 0; i < headerName.size(); ++i) //for each column we need to change
	{
		//In our table, 
		//Go through the rows of the COMPARED column and see if its elements match up
		//Store the respective position of the row

		for (int j = 0; j < database[nameUpdate]->getRowLength(); ++j) //for each row
		{
			bool whereTrue = 0; //let the program know that WHERE is true
			//check the correct column and check if the where(s) function is(are) true
			for (int k = 0; k < updateOP.size(); ++k)
			{
				if (updateOP[k] == "==") //==
				{
					if (database[nameUpdate]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
					{
						int lhs, rhs;
						lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
						rhs = stoi(updateOperand2[k]); //convert to int
						if (lhs == rhs) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
					else
					{
						if (tempTable[j][whereColPos[k]] == updateOperand2[k]) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break; //we break because we know we don't need to check other arguements
						}
					}
				}
				else if (updateOP[k] == "!=") //!=
				{
					if (database[nameUpdate]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
					{
						int lhs, rhs;
						lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
						rhs = stoi(updateOperand2[k]); //convert to int
						if (lhs != rhs) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
					else
					{
						if (tempTable[j][whereColPos[k]] != updateOperand2[k]) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
				}
				else if (updateOP[k] == "<=") //<=
				{
					if (database[nameUpdate]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
					{
						int lhs, rhs;
						lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
						rhs = stoi(updateOperand2[k]); //convert to int
						if (lhs <= rhs) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
					else
					{
						if (tempTable[j][whereColPos[k]] <= updateOperand2[k]) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
				}
				else if (updateOP[k] == ">=") //>=
				{
					if (database[nameUpdate]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
					{
						int lhs, rhs;
						lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
						rhs = stoi(updateOperand2[k]); //convert to int
						if (lhs >= rhs) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
					else
					{
						if (tempTable[j][whereColPos[k]] >= updateOperand2[k]) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
				}
				else if (updateOP[k] == "<") //<
				{
					if (database[nameUpdate]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
					{
						int lhs, rhs;
						lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
						rhs = stoi(updateOperand2[k]); //convert to int
						if (lhs < rhs) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
					else
					{
						if (tempTable[j][whereColPos[k]] < updateOperand2[k]) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}

				}
				else if (updateOP[k] == ">") //>
				{
					if (database[nameUpdate]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
					{
						int lhs, rhs;
						lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
						rhs = stoi(updateOperand2[k]); //convert to int
						if (lhs > rhs) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
					else
					{
						if (tempTable[j][whereColPos[k]] > updateOperand2[k]) //check the column in the right row
						{
							whereTrue = 1;
						}
						else
						{
							whereTrue = 0;
							break;
						}
					}
				}
			}
			if (whereTrue) //if we have passed the tests
			{
				tempTable[j][headerColPos[i]] = replace[i]; //change the value in the right column
			}
		}

	}
	
 	
/*
UPDATE animals SET name = BirdName2 WHERE kind != bird;
UPDATE animals SET name = NEWJOE, kind = young WHERE age > 1; 
UPDATE exhibitors SET address = 123_College_Dr. WHERE fax > 1;
UPDATE org_name SET address = 123_College_Dr. WHERE fax > 1;
		*/
	
	database[nameUpdate]->setTable(tempTable); //update table
	
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

int DBsystem::DELETE(string nameDelete, vector<string> deleteOperand1, vector<string> deleteOperand2, vector<string> deleteOP)
{
	vector<int> whereColPos;			  //store which column to look at for the where fuction		
	vector<int> rowsToDelete;
	vector<vector<string>> tempTable = database[nameDelete]->getTable(); //get table info

	int newRowCount = database[nameDelete]->getRowLength();

	 //Go through table headers and find column Position
	 for (int i = 0; i < deleteOperand1.size(); ++i) //for headers
	 {
		 for (int j = 0; j < database[nameDelete]->getHeaders().size(); ++j)
		 {
			 if (database[nameDelete]->getHeaders()[j] == deleteOperand1[i]) //check each header
			 {
				 whereColPos.push_back(j); //push back the header locations if matched
			 }
		 }
	 }

	 //go through table with the columns in colPos and use where condidtion to 


	 for (int j = 0; j < newRowCount; ++j) //for each row
	 {
		 bool whereTrue = 0; //let the program know that WHERE is true
							 //check the correct column and check if the where(s) function is(are) true
		 for (int k = 0; k < deleteOP.size(); ++k)
		 {
			 if (deleteOP[k] == "==") //==
			 {
				 if (database[nameDelete]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
				 {
					 int lhs, rhs;
					 lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
					 rhs = stoi(deleteOperand2[k]); //convert to int
					 if (lhs == rhs) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
				 else
				 {

				 }
				 if (tempTable[j][whereColPos[k]] == deleteOperand2[k]) //check the column in the right row
				 {
					 whereTrue = 1;
				 }
				 else
				 {
					 whereTrue = 0;
					 break; //we break because we know we don't need to check other arguements
				 }
			 }
			 else if (deleteOP[k] == "!=") //!=
			 {
				 if (database[nameDelete]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
				 {
					 int lhs, rhs;
					 lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
					 rhs = stoi(deleteOperand2[k]); //convert to int
					 if (lhs != rhs) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
				 else
				 {
					 if (tempTable[j][whereColPos[k]] != deleteOperand2[k]) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
			 }
			 else if (deleteOP[k] == "<=") //<=
			 {
				 if (database[nameDelete]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
				 {
					 int lhs, rhs;
					 lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
					 rhs = stoi(deleteOperand2[k]); //convert to int
					 if (lhs <= rhs) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
				 else
				 {
					 if (tempTable[j][whereColPos[k]] <= deleteOperand2[k]) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
			 }
			 else if (deleteOP[k] == ">=") //>=
			 {
				 if (database[nameDelete]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
				 {
					 int lhs, rhs;
					 lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
					 rhs = stoi(deleteOperand2[k]); //convert to int
					 if (lhs >= rhs) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
				 else
				 {
					 if (tempTable[j][whereColPos[k]] >= deleteOperand2[k]) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
			 }
			 else if (deleteOP[k] == "<") //<
			 {
				 if (database[nameDelete]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
				 {
					 int lhs, rhs;
					 lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
					 rhs = stoi(deleteOperand2[k]); //convert to int
					 if (lhs < rhs) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
				 else
				 {
					 if (tempTable[j][whereColPos[k]] < deleteOperand2[k]) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
			 }
			 else if (deleteOP[k] == ">") //>
			 {
				 if (database[nameDelete]->getHeaderSizes()[whereColPos[k]] < 0)//if it's an int
				 {
					 int lhs, rhs;
					 lhs = stoi(tempTable[j][whereColPos[k]]); //convert to int
					 rhs = stoi(deleteOperand2[k]); //convert to int
					 if (lhs > rhs) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
				 else
				 {
					 if (tempTable[j][whereColPos[k]] > deleteOperand2[k]) //check the column in the right row
					 {
						 whereTrue = 1;
					 }
					 else
					 {
						 whereTrue = 0;
						 break;
					 }
				 }
			 }
		 }
		 if (whereTrue) //if we have passed the tests
		 {
			 tempTable.erase(tempTable.begin() + j); //delete the row
			 --j; //the rows move down in the vector so we have to account for that
			 newRowCount--; //accont for removing a row

		 }
	 }


	//DELETE FROM animals WHERE kind == cat;
	 database[nameDelete]->setTable(tempTable); //update table
	 database[nameDelete]->setRowLength(newRowCount);


    return 0;

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

Table* DBsystem::SELECT(string newTableName,string nameSelect, vector<string> header ,vector<string> selectOP, vector<string> condition) 
{
	//Select multiple columns and join them together by a certain condition
	//header is lhs
	//selectOP is operation
	//condition is rhs


	Table* tempTable = new Table(); //table to return
	vector< vector<string> > origT = database[nameSelect]->getTable(); //make a copy 
	vector<int> colPosition;
	vector< vector<string> > returnT;
	int rowCount = 0;
	vector<string> tempHeaders = database[nameSelect]->getHeaders();
	
	
	for (int a = 0; a < header.size(); a++) //for each header
	{
		for (int i = 0; i < tempHeaders.size(); ++i) //go through all the headers in the table
		{
			if (header[a] == tempHeaders[i]) //if they are equal
			{
				colPosition.push_back(i); //keep track of the location
			}
		}
	}
	for (int j = 0; j < database[nameSelect]->getRowLength(); ++j) //for each row
	{
		bool whereTrue = 0; //let the program know that WHERE is true
							//check the correct column and check if the where(s) function is(are) true
		for (int k = 0; k < selectOP.size(); ++k)
		{
			if (selectOP[k] == "==") //==
			{
				if (database[nameSelect]->getHeaderSizes()[colPosition[k]] < 0)//if it's an int
				{
					int lhs, rhs;
					lhs = stoi(origT[j][colPosition[k]]); //convert to int
					rhs = stoi(condition[k]); //convert to int
					if (lhs == rhs) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}
				else
				{
					if (origT[j][colPosition[k]] == condition[k]) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break; //we break because we know we don't need to check other arguements
					}
				}

			}
			else if (selectOP[k] == "!=") //!=
			{
				if (database[nameSelect]->getHeaderSizes()[colPosition[k]] < 0)//if it's an int
				{
					int lhs, rhs;
					lhs = stoi(origT[j][colPosition[k]]); //convert to int
					rhs = stoi(condition[k]); //convert to int
					if (lhs != rhs) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}
				else
				{
					if (origT[j][colPosition[k]] != condition[k]) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}

			}
			else if (selectOP[k] == "<=") //<=
			{
				if (database[nameSelect]->getHeaderSizes()[colPosition[k]] < 0)//if it's an int
				{
					int lhs, rhs;
					lhs = stoi(origT[j][colPosition[k]]); //convert to int
					rhs = stoi(condition[k]); //convert to int
					if (lhs <= rhs) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}
				else
				{
					if (origT[j][colPosition[k]] <= condition[k]) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}

			}
			else if (selectOP[k] == ">=") //>=
			{
				if (database[nameSelect]->getHeaderSizes()[colPosition[k]] < 0)//if it's an int
				{
					int lhs, rhs;
					lhs = stoi(origT[j][colPosition[k]]); //convert to int
					rhs = stoi(condition[k]); //convert to int
					if (lhs >= rhs) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}
				else
				{
					if (origT[j][colPosition[k]] >= condition[k]) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}
			}
			else if (selectOP[k] == "<") //<
			{
				if (database[nameSelect]->getHeaderSizes()[colPosition[k]] < 0)//if it's an int
				{
					int lhs, rhs;
					lhs = stoi(origT[j][colPosition[k]]); //convert to int
					rhs = stoi(condition[k]); //convert to int
					if (lhs < rhs) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}
				else
				{
					if (origT[j][colPosition[k]] < condition[k]) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}

			}
			else if (selectOP[k] == ">") //>
			{
				if (database[nameSelect]->getHeaderSizes()[colPosition[k]] < 0)//if it's an int
				{
					int lhs, rhs;
					lhs = stoi(origT[j][colPosition[k]]); //convert to int
					rhs = stoi(condition[k]); //convert to int
					if (lhs > rhs) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}
				else
				{
					if (origT[j][colPosition[k]] > condition[k]) //check the column in the right row
					{
						whereTrue = 1;
					}
					else
					{
						whereTrue = 0;
						break;
					}
				}

			}
		}
		if (whereTrue) //if we have passed the tests
		{
			returnT.push_back(origT[j]); //push back that row into the return Table
			++rowCount;
		}
	}
	
	
	tempTable->setTableName(newTableName);
	tempTable->setRowLength(rowCount);
	tempTable->setHeader(database[nameSelect]->getHeaders());
	tempTable->setHeaderTypes(database[nameSelect]->getHeaderTypes());
	tempTable->setHeaderSizes(database[nameSelect]->getHeaderSizes());
	tempTable->setPrimaryKeys(database[nameSelect]->getPrimaryKeys());
	tempTable->setColumnLength(tempTable->getHeaders().size());
	tempTable->setTable(returnT);
	
	database[newTableName] = tempTable;
	return tempTable;
}

Table* DBsystem::PROJECT(string t1, vector<string> attributes)
{
	Table tempTable0(*database[t1]);
	Table* tempTable = new Table(tempTable0);
    vector<int> pos; //for keeping track of the columns we need to grab
    vector<string> newHeaders; //for return header
    vector<string> tempRow; //holds the row for the projected table
    vector< vector <string> > returnTable; //this what we will pass to our return Table
    
    //get table
    vector< vector <string> > tempT = database[t1]->getTable(); //makes code nicers
	cout<<"Table col Length: "<<tempTable->getColumnLength();
	cout<<" Table row Length: "<<tempTable->getRowLength();
    
    cout <<" "<< t1 << " PROJECTION OF: "  << endl;
    cout<<"Size of Headers: "<<database[t1]->getHeaders().size()<<endl;
   
   	//we need to check the headers for each attribute
	for(int i = 0; i<attributes.size(); ++i) //for each attribute
	{
		for (int j = 0; j < database[t1]->getHeaders().size(); ++j) //look at each header
	    {   //Go through headers and find matching attribute
	        if (database[t1]->getHeaders()[j].compare(attributes[i])==0) //if it matches
	        {   //See if and DB header fits attribute
	            cout << "Found: " << database[t1]->getHeaders()[j] << endl;
	            pos.push_back(j);           				//Store corresponding position in vector
	        }
	        else //did not find it
	        { 
	        	cout << "Column " << j+1 << " not projected for attribute "<<attributes[i]<< endl; 
	        }
	    }
	}

    //we've found all the header locations
    //now we need to create a table from those columns
	newHeaders = attributes; //set the new headers
    
    //here we will grab the column by going throw all the rows for each column 
    for (int j = 0; j < database[t1]->getRowLength(); ++j) //for each row
    {
		tempRow.clear(); 
	    for(int i = 0; i < pos.size(); ++i)  //go to the right columns
	    {
			tempRow.push_back(tempT[j][pos[i]]); //add the columns 
	    }	    	
	    returnTable.push_back(tempRow); //add the row to the new table.
    }

	//these are just to fix the new table
	vector<string> tempHeaderTypes;
	vector<string> tempPrimaryKeys;
	vector<int> tempHeaderSizes;

	//we have to fill the tables with adjusted values
	for (int i = 0; i < pos.size(); ++i)
	{
		tempHeaderSizes.push_back(database[t1]->getHeaderSizes()[pos[i]]); 
		tempHeaderTypes.push_back(database[t1]->getHeaderTypes()[pos[i]]);
	}
	tempPrimaryKeys.push_back(attributes[0]); //set the primary key to the first attribute
	
	string tempTableName = "Project" + t1;
	tempTable->setTableName(tempTableName);
	tempTable->setHeader(newHeaders);
	tempTable->setHeaderTypes(tempHeaderTypes);
	tempTable->setHeaderSizes(tempHeaderSizes);
	tempTable->setPrimaryKeys(tempPrimaryKeys);
	cout<<"Old Table col Length: "<<tempTable->getColumnLength()<<endl;
	cout<<"Old Table row Length: "<<tempTable->getRowLength()<<endl;
    tempTable->setTable(returnTable);
	tempTable->setColumnLength(pos.size());
	cout<<"New Table col Length: "<<tempTable->getColumnLength()<<endl;
    
	database[tempTableName] = tempTable;

    return tempTable;
	
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
    database[tName]->setHeader(replaceAttributes);      //Rename the headers.

    
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
		//database[newName] = unionTable; //add the table to the database
		
		vector< vector <string> > copyTable;
		copyTable = database[t1]->getTable();
		int count = database[t1]->getRowLength();
		
		//add all the elements from B 
		cout << 101;
		for(int i = 0; i < database[t2]->getRowLength(); ++i)
		{
			copyTable.push_back(database[t2]->getTable()[i]); // push back each row
			count+=1; //increase row count
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



Table* DBsystem::SET_DIFFERENCE(string tableName1, string tableName2, string newName)
{
	Table* differenceTable = database[tableName1]; //to return
	
	vector< vector<string> > tempT1; // for doing the difference
	vector< vector<string> > tempT2;
	
	//make a copy of each table
	tempT1 = database[tableName1]->getTable(); 
	tempT2 = database[tableName2]->getTable();
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

Table* DBsystem::CROSS_PRODUCT(string t1, string t2, string newName)
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


















