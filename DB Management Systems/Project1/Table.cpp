#include "Table.h"
#include <vector>
#include <string>

using namespace std;


Table::Table(int rows, int columns,string name, vector<string> headers, vector<string> keys) //constructor
{
	rowLength = rows; //set the number of rows
	columnLength = columns; //set the nubmer of columns	
	tableName = name;
	table.resize(rows, vector<string>(columns)); //resize the table
	for(int i = 0;i<rows;++i) // set the headers
	{
		table[0][i] = headers[i];
	}
	primaryKeys = keys; //set the primary keys
}

Table::Table() //defualt constructor
{
	rowLength = 1;
	columnLength = 2;
	tableName = "default";
	table.resize(1,vector<string>(1)); //default size is 10x10 that can be changed. 
	table[0][0] = "default" ; //give header
	primaryKeys.resize(1);//resize to one
	primaryKeys[0] = "default"; //set default primary keys
}

Table* Table::open_cmd(string nameOpen) //bring a table into memory from file 
{
	//read in from the comma seperated text file
	//the numbers of rows and columns should be the first two lines of every file
	//we create a table with those dimensions
	//change the values of the newly created table in memory by reading from file.
	//return 0;  //I just think it's better to return 0 on success rather than 1.
}

int Table::close_cmd(string nameClose) //saves and removes table instance from memory
{
	//create a new txt file with the name of the file
	//read in the rowLength and columnLenght of table first
	//read in row by row into file
	//remove from memory
	//return 0;
}

int Table::save_cmd(string nameSave) //save the table to file keep in memory
{
	//create a new txt file with the name of the file
	//read in the rowLength and columnLenght of table first
	//read in row by row into file
	//close file
	//return 0;
}
	
	
//Don't think that this needs the input of string either.  If it's accessing the current table in memory, I don' think it needs a string argument.
int Table::show_cmd(string nameShow) //print out the table currently in memory
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

Table* Table::create_cmd(int rowCreate, int columnCreate, string nameCreate,vector<string> createHeaders, vector<string> createKeys) //create a new table in memory
{
	//intiliaze new Table
	Table* newTable = new Table(rowCreate, columnCreate,nameCreate,createHeaders, createKeys)
	//return new Table
	return newTable;
	
}

//updates a record in the database given certain criteria
int Table::update_cmd(string nameUpdate, string headerName, string criteria, string replace)
{
	//go to table nameUpdate
	//search first row for headerName to find column
	//search that column for the criteria
	//replace the criteria with replace
	//return 0;
}

//Takes in the input of nameInsert and returns an int for error checking.
int Table::insert_cmd(string nameInsert, int rowInsert, int colInsert)
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
int Table::delete_cmd(string nameDelete, int rowDelete)
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
