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
#include <map>
#include "Parser.h"
#include "Table.h"

using namespace std;



class DBsystem
{
	map<string,Table*> database;

public:
	DBsystem();
	
	//-------Database queries--------//
	Table* OPEN(string); //bring a table into memory from file 
	int CLOSE(string);
	int SAVE(string);
	int SHOW(string);    	//::== SHOW atomic-expr 
	Table* CREATE(int,int,string,vector<string>,vector<string>); //::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
	int UPDATE(string, string, string, string);	//::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
	int INSERT(string, int , int );	//::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) | INSERT INTO relation-name VALUES FROM RELATION expr
	int DELETE(string , int );	//::= DELETE FROM relation-name WHERE condition
	//-------Database commands (need definitions)-------//
	Table* SELECT(string, vector<string>);    //select table with certain criteria
	Table*  PROJECT(string, string);
	void RENAME(string, string);			
	Table* SET_UNION(string, string);			//Take the union of 2 tables
	Table* SET_DIFFERENCE(string, string);		//2 table names
	Table* CROSS_PRODUCT(string, string);		//2 table names used to perform cross product
	void EXIT();
};


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
	this.SAVE()
	database.erase("nameClose");
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
	Table t = *database["nameSave"];
	
	saveFile<<"CREATE TABLE " + nameSave + " (";
	int temp = 0;
	for (int i = 0; i< t.getColumnLength() - 1; ++i)
	{

		saveFile<< t->getTable()[i] << ", ";
		temp = i;
	}
	saveFile<<t->getTable()[temp]<<")";
	
	
	//Missing the Primary Key part.
	
	
	for (int i = 1; i<t.getRowLength(); ++i)
	{
		saveFile<<"INSERT INTO " + nameSave + " VALUES FROM (";
		for (int j = 0; j<t.getColumnLength(); ++j)
		{
			saveFile << t->getTable()[i][j];
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
	cout<<nameShow<<endl<<endl;
	//iterate through the table and print.
	for (int i = 0; i<database["nameShow"]->getRowLength(); ++i)
	{
		for (int j = 0; j<database["nameShow"]->getColumnLength(); ++j)
		{
			cout<<database["nameShow"]->getTable()[i][j]<<"  ";
		}
		cout<<endl;
	}
	return 0;
	
	
}

Table* DBsystem::CREATE(int rowCreate, int columnCreate, string nameCreate,vector<string> createHeaders, vector<string> createKeys, vector<string> createTypes) //create a new table in memory
{
	//intiliaze new Table
	Table* newTable = new Table(rowCreate, columnCreate,nameCreate,createHeaders, createKeys, createTypes);
	database["nameCreate"] = newTable; //add the table to the database
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
	
	 if (rowInsert < database["nameInsert"]->getRowLength() && colInsert < database["nameInsert"]->getColumnLength())
    {
        database["nameInsert"]->getTable()[rowInsert][colInsert] = nameInsert;
        return 0;
    }
    //Else returns 1 for failure.
    else
    {
    
        return 1;
    }
	
}

//Takes in the input of nameInsert and returns an int for error checking.
int DBsystem::INSERT(string nameInsert, int rowInsert, int colInsert)
{
	//Check if the rowInsert and colInsert are within the bounds of the table.
	cout << "INSERT test 1";
    if (rowInsert < database["nameInsert"]->getRowLength() && colInsert < database["nameInsert"]->getColumnLength())
    {
        database["nameInsert"]->getTable()[rowInsert][colInsert] = nameInsert;
        return 0;
    }
    //Else returns 1 for failure.
    else
    {
    
        return 1;
    }
}

//nameDelete may not be neede depending on the implementation of the Parser.
//Parser may end up finding the row and may only need one input here.
int DBsystem::DELETE(string nameDelete, int rowDelete)
{
	//Check for out of bounds error
    if (rowDelete < database["nameShow"]->getRowLength())
    {
        //database.erase(database["nameShow"].begin() + rowDelete);
        return 0;
    }
    //If out of bounds, return 1 for failure.
    else
    {
        return 1;
    }
}

//----------------Database queries---------------//

Table* DBsystem::SELECT(string nameShow, vector<string> attributes) {
	
	
}

Table* DBsystem::PROJECT(string t1, string t2)
{
	
	
}

Table* DBsystem::RENAME(string tableName, string replaceName)
{
	
	
}

Table* DBsystem::SET_UNION(string t1, string t2)
{


}

Table* DBsystem::SET_DIFFERENCE(string t1, string t2)
{
	
	
}

Table* DBsystem::CROSS_PRODUCT(string t1, string t2)
{


}

//exits program and deletes everything not saved
void DBsystem::EXIT()
 {
	for(map<String, *Table>::iterator itr = database.begin(); itr != database.end(); itr++){
		delete itr->second; //deletes all *Table pointers
	}
	else{
		quick_exit(EXIT_SUCCESS);
	}
 }


int main()
{
	Table* t;		//Testing some stuff
	
	
	DBsystem db;
	vector<string> header1;
	header1.push_back("test1");
	vector<string> keys1;
	keys1.push_back("test1");
	t = db.CREATE(1,1,"test", header1,keys1);
	//db.CLOSE("test");
	cout << t->getRowLength() << " " << t->getColumnLength() << endl;
	//db.INSERT("testtt", 1, 1);
	db.SHOW("test");
	//t.show_cmd("test");

	cout << "Starting main..." << endl;
	cout << "Enter command: " << endl;


	string mainInput;
	while (true)
	{
		getline(cin, mainInput);
		Parser mainParser(mainInput);
	    mainParser.parse();
		
	}
}