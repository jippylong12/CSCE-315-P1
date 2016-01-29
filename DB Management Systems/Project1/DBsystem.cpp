/* _authors_
Marcus Salinas
Brian Ta
Deokman Park
Clifton Sims
Ivan Rupert */

#include <iostream>
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
	Table* OPEN(string);
	int CLOSE(string);
	int SAVE(string);
	int SHOW(string)
	Table* CREATE(int,int,string,vector<string>,vector<string>);
	int UPDATE(string,string,string,string);
	int INSERT(string,int,int);
	int DELETEs(string,int);
	
	//Database queries//
	void SELECT();
	void PROJECT();
	void RENAME();
	void SET_UNION();
	void SET_DIFFERENCE();
	void CROSS_PRODUCT();
	void EXIT();
};


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
}

int DBsystem::SAVE(string nameSave) //save the table to file keep in memory
{
	//create a new txt file with the name of the file
	//read in the rowLength and columnLenght of table first
	//read in row by row into file
	//close file
	//return 0;
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
	for (int i = 0; i<rowLength; ++i)
	{
		for (int j = 0; j<columnLength; ++j)
		{
			cout<<table[i][j]<<"  ";
		}
		cout<<endl;
	}
	return 0;
	
	
}

Table* DBsystem::CREATE(int rowCreate, int columnCreate, string nameCreate,vector<string> createHeaders, vector<string> createKeys) //create a new table in memory
{
	//intiliaze new Table
	Table* newTable = new Table(rowCreate, columnCreate,nameCreate,createHeaders, createKeys)
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
	//return 0;
}

//Takes in the input of nameInsert and returns an int for error checking.
int DBsystem::INSERT(string nameInsert, int rowInsert, int colInsert)
{
	//Check if the rowInsert and colInsert are within the bounds of the table.
    if (rowInsert < rowLength && colInsert < columnLength)
    {
        table[rowInsert][colInsert] = nameInsert;
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
int DBsystem::DELETEs(string nameDelete, int rowDelete)
{
	//Check for out of bounds error
    if (rowDelete < rowLength)
    {
        table.erase(table.begin() + rowDelete);
        return 0;
    }
    //If out of bounds, return 1 for failure.
    else
    {
        return 1;
    }
}


int main()
{
	//DBsystem db;
	vector<string> header1;
	header1.push_back("test1");
	vector<string> keys1;
	keys1.push_back("test1");
	Table t(1,10,"test", header1,keys1);
	t.show_cmd("test");

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
