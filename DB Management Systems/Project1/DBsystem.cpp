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
#include <sstream>
#include <iomanip>
#include <map>
#include "Parser.h"
#include "DBsystem.h"

using namespace std;


DBsystem::DBsystem()
{
	//not sure if we need anything to be done since create will add the 
	//new tables
}



Table* DBsystem::OPEN(string nameOpen) //bring a table into memory from file 
{
	//read in from the comma seperated text file
	//the numbers of rows and columns should be the first two lines of every file
	//we create a table with those dimensions
	//change the values of the newly created table in memory by reading from file.
	//return 0;  //I just think it's better to return 0 on success rather than 1.
}

int DBsystem::CLOSE(string nameClose) //saves and removes table instance from memory
{
	//create a new txt file with the name of the file
	//read in the rowLength and columnLenght of table first
	//read in row by row into file
	//remove from memory
	//return 0;
	//database["nameClose"]
	//Just call Save Function.
	this->SAVE(nameClose);
	database.erase(nameClose);
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
	for (int i = 0; i< t.getColumnLength() - 1; ++i)
	{

		//saveFile<< t.getTable()[i] << ", ";
		temp = i;
	}
	//saveFile<<t.getTable()[temp]<<")";
	
	
	//Missing the Primary Key part.
	
	
	for (int i = 1; i<t.getRowLength(); ++i)
	{
		saveFile<<"INSERT INTO " + nameSave + " VALUES FROM (";
		for (int j = 0; j<t.getColumnLength(); ++j)
		{
			saveFile << t.getTable()[i][j];
		}
		saveFile<<endl;
	}
	
	saveFile.close();
	return 0;
}

//Don't think that this needs the input of string either.  If it's accessing the current table in memory, I don' think it needs a string argument.
int DBsystem::SHOW(string nameShow) //print out the table currently in memory
{
	//nested for loop
	//print each cell in the table
	//return 0;
	//First, print the name of the table
    cout << " ---------------------------------------- " <<endl;
    cout<<' '<<setw(21)<<nameShow<<setw(21)<<' '<<endl;
    cout << " ---------------------------------------- " <<endl;
	//print headers.
	for (int i = 0; i< database[nameShow]->getHeaders().size(); ++i)
	{
        cout << setw(5)<<"["<<database[nameShow]->getHeaders()[i]<<"]" << setw(5);
	}
    cout<<endl;
	//print table
	for (int i = 0; i<database[nameShow]->getRowLength(); ++i)
	{
		for (int j = 0; j<database[nameShow]->getColumnLength(); ++j)
		{
			cout << setw(10) << database[nameShow]->getTable()[i][j]<<setw(10) ;
		}
		cout<<endl<<endl;
	}
	return 0;
	
	
}

Table* DBsystem::CREATE(int columnCreate, string nameCreate,vector<string> createHeaders, vector<string> createKeys, vector<string> createTypes) //create a new table in memory
{
	//intiliaze new Table
	Table* newTable = new Table(columnCreate,nameCreate,createHeaders, createKeys, createTypes);
	database[nameCreate] = newTable; //add the table to the database
	//return new Table
	return newTable;
	
}

//updates a record in the database given certain criteria
int DBsystem::UPDATE(string nameUpdate, string headerName, string criteria, string replace)
{
	//go to table nameUpdate
	//search first row for headerName to find column
	//search that column for the criteria
	//replace the criteria with replace
	
	//need to iterate through all columns
	int row, col;
	
	for (int i = 0; i < database[nameUpdate]->getColumnLength(); ++i)
	{
		if (database[nameUpdate]->getTable()[0][i] == headerName)
		{
			col = i;
		}
	}
	
	for (int i = 0; i < database[nameUpdate]->getRowLength(); ++i)
	{
		if (database[nameUpdate]->getTable()[i][col] == criteria)
		{
			row = i;
		}
	}
	
	database[nameUpdate]->getTable()[row][col] = replace;
	
	
    //Else returns 1 for failure.
  
    
    	return 0;
	
}

//Takes in the input of nameInsert and returns an int for error checking.
int DBsystem::INSERT(string nameInsert, vector<vector<string> > inputs)
{
	//go to the table request
	//check that the table is compatable?
	//add all the items in inputs to the bottom of the able
	
	vector<vector<string> > tempTable = database[nameInsert]->getTable();
	tempTable.push_back(inputs[0]);
	int tempRow = database[nameInsert]->getRowLength() + 1;
	database[nameInsert]->setRowLength(tempRow);
	

	//cout<<"Input Size: "<<inputs.size()<<endl; //error checkking
	if(inputs.size()> 1)
	{
		for(int i = 1; i<inputs.size(); ++i)
		{
			tempRow = database[nameInsert]->getRowLength() + 1;
			database[nameInsert]->setRowLength(tempRow);
			tempTable.push_back(inputs[i]);
		}
	}

	database[nameInsert]->setTable(tempTable); //set the old table equal to the new table
	
	return 0;

}

//nameDelete may not be neede depending on the implementation of the Parser.
//Parser may end up finding the row and may only need one input here.
int DBsystem::DELETE(string nameDelete, int rowDelete)
{
	vector<vector <string> >* tempTable = new vector<vector<string> >();
	*tempTable = database[nameDelete]->getTable();
	//Check for out of bounds error
    if (rowDelete < database[nameDelete]->getRowLength())
    {
		for(int i = 0; i<database[nameDelete]->getRowLength(); ++i)
		{
			tempTable[rowDelete].erase(tempTable[rowDelete].begin(),tempTable[rowDelete].end());
		}
        database[nameDelete]->getTable() = *tempTable;
		delete tempTable;
        return 0;
    }
    //If out of bounds, return 1 for failure.
    else
    {
        return 1;
    }
}

//exits program and deletes everything not saved
void DBsystem::EXIT()
 {
 	
	for(map<string, Table*>::iterator itr = database.begin(); itr != database.end(); itr++){
		delete itr->second; //deletes all *Table pointers
	}
	exit(EXIT_SUCCESS);
 }

//----------------Database queries---------------//

Table* DBsystem::SELECT(string nameShow, vector<string> attributes) 
{
	
	
}

vector<Table*> DBsystem::PROJECT(string t1, vector<string> attributes)
{
    vector<Table*> t;
    Table* tempTable = new Table();
    vector<string> attr;
    vector<int> pos;
   
    
    for (int i = 0; i < database[t1]->getColumnLength(); ++i){      //Go through DB
        if (database[t1]->getHeaders()[i].compare(attributes[i])==0){//See if and DB header fits attribute
            pos.push_back(i);
            //grab (push back) all applicable tables
            //cout << database[t1]->getHeaders()[i] << " vs " << attributes[i] << endl;
        }else { cout << "No projection done" << endl; }
    }
    for (int i = 0; i < pos.size(); ++i){
        attr.push_back(attributes[pos[i]]);
        //cout << pos[i];
    }
    tempTable->setHeader(attr);
    t.push_back(tempTable);
    
    //delete tempTable;
    return t;
	
}

Table* DBsystem::RENAME(string tName, vector<string> tableAttributes, vector<string> replaceAttributes)
{
    Table *t;
    for (int i = 0; i < database[tName]->getColumnLength(); ++i){
        if(tableAttributes.size()==replaceAttributes.size()){  //Check if we need to add back existing table headers
            //replaceAttributes.push_back(tableAttributes[i]);
            tableAttributes[i] = replaceAttributes[i];      //Assume that attribute names to be replaced are in the same index
        }else{
            replaceAttributes.push_back(tableAttributes[max(tableAttributes.size()-1, replaceAttributes.size()-1)]);            //Push back the missed Tables
        }
    }
    database[tName]->setHeader(replaceAttributes);      //Rename the headers.
    

    
    return database[tName];
}

Table* DBsystem::SET_UNION(string t1, vector<string> t2)
{
    //Returns a Table of the Union
    

}

Table* DBsystem::SET_DIFFERENCE(string t1, string t2)
{
	
	
}

Table* DBsystem::CROSS_PRODUCT(string t1, string t2)
{
    //The cross product of two tables A x B builds a huge virtual table by pairing every row of A with every row of B.
    
    Table* tempTable;                                   //Table to be produced
    vector<string> newHeaders;
    int t1_rowLength = database[t1]->getRowLength();
    int t1_columnLength = database[t1]->getColumnLength();
    vector<string> t1Rows;
    int t2_rowLength = database[t2]->getRowLength();
    int t2_columnLength = database[t2]->getColumnLength();
    vector<string> t2Rows;
    vector<string> joinedRows;                          //Store a vector for t1 x t2
    
    
    
    //Get the attributes for both rows, concatenate them to be the new headers
    for (int i = 0; i < database[t1]->getHeaders().size() + database[t2]->getHeaders().size(); ++i){
        newHeaders.push_back(database[t1]->getHeaders()[i] + " + " + database[t2]->getHeaders()[i] );
    }
    tempTable->setHeader(newHeaders);                   //Set the new Table headers
   
    for (int i = 0; i < t1_columnLength; ++i){          //
        t1Rows = database[t1]->getTable()[i];           //Grab rows from Table 1
        for (int j = 0; j < t2_columnLength; ++j){
            t2Rows = database[t2]->getTable()[j];       //Grab rows from Table 2
            joinedRows = t1Rows;                        //Store 1..i rows from t1 (table 2 column times)
            for (int k = 0; k < t2Rows.size(); ++k){
                joinedRows.push_back(t2Rows[k]);        //Push all rows from t2 after the 1..ith row of t1
            }
        }
    }
    
    tempTable->setRows(joinedRows);                     //Rows of the new table
    return tempTable;
    

}



















