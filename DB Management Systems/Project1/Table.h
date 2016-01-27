#include "vector"
#include <string>
#include <iostream>

using namespace std;

class Table
{
    vector< vector<string> > table; //represents one table
    int rowLength; //number of rows
    int columnLength; //number of columns
 	vector<string> primaryKeys; //primary keys
    
public:
	//-------Database command functions-------//

	/*command ::= ( open-cmd | close-cmd | save-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd );*/
	//Table Constructor

	Table(int,int, vector<string>, vector<string>); //constructor	
	Table(); 			//default
	Table* open_cmd(string);  	//::== OPEN relation-name 
	int close_cmd(string); 	//::== CLOSE relation-name 
	int save_cmd(string);  	//::== SAVE relation-name 
	int show_cmd(string);    	//::== SHOW atomic-expr 
	Table* create_cmd(string, vector<string>);	//::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
	int update_cmd(string, string, string, string);	//::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
	int insert_cmd(string, int , int );	//::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) | INSERT INTO relation-name VALUES FROM RELATION expr
	int delete_cmd(string , int );	//::= DELETE FROM relation-name WHERE condition
	int getRowLength() { return rowLength;}; 
	int getColumnLength() { return columnLength;};
	vector<string> getPrimnaryKey(); //return key vector
	void setPrimaryKey(); //set any of the values of the primary key
	
	
};

Table::Table(int rows, int columns,vector<string> headers, vector<string> keys) //constructor
{
	rowLength = rows; //set the number of rows
	columnLength = columns; //set the nubmer of columns	
	table.resize(rows, vector<string>(columns)); //resize the table
	for(i = 0;i<rows;++i) // set the headers
	{
		table[0][i] = headers[i];
	}
	primaryKeys = keys; //set the primary keys
}

Table::Table() //defualt constructor
{
	rowLength = 1;
	columnLength = 2;
	table.resize(1,vector<string>(1)); //default size is 10x10 that can be changed. 
	table[0][0] = "default" ; //give header
	primaryKeys.resize(1);//resize to one
	primaryKeys[0] = "default"; //set default primary keys
}

Table* Table::open_cmd(string nameOpen); //bring a table into memory from file 
{
	//read in from the comma seperated text file
	//the numbers of rows and columns should be the first two lines of every file
	//we create a table with those dimensions
	//change the values of the newly created table in memory by reading from file.
	//return 1;
}

int Table::close_cmd(string nameClosy) //saves and removes table instance from memory
{
	//create a new txt file with the name of the file
	//read in the rowLength and columnLenght of table first
	//read in row by row into file
	//remove from memory
	//return 1;
}

int Table:save_cmd(string nameSave) //save the table to file keep in memory
{
	//create a new txt file with the name of the file
	//read in the rowLength and columnLenght of table first
	//read in row by row into file
	//close file
	//return 1;
}
	
int Table::show_cmd(string nameShow) //print out the table currently in memory
{
	//nested for loop
	//print each cell in the table
	//return 1;
}

Table* Table::create_cmd(string nameCreate,vector<string> attributeList) //create a new table in memory
{
	//intiliaze new Table
	//use attributeList for header and values of table(row and column length, keys)
	//return new Table
}

//updates a record in the database given certain criteria
int Table::update_cmd(string nameUpdate, string headerName, string criteria, string replace)
{
	//go to table nameUpdate
	//search first row for headerName to find column
	//search that column for the criteria
	//replace the criteria with replace
	//return 1;
}

