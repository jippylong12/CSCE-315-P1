#include "Table.h"
#include <vector>
#include <string>

using namespace std;


Table::Table(const Table &Source)
{
	table = Source.table;
	tableName = Source.tableName;
	rowLength = Source.rowLength;
	columnLength = Source.columnLength;
	primaryKeys = Source.primaryKeys;
}

Table& Table::operator= (const Table &Source)
{
	table = Source.table;
	tableName = Source.tableName;
	rowLength = Source.rowLength;
	columnLength = Source.columnLength;
	primaryKeys = Source.primaryKeys;
	return *this;
}

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
//Table::~Table(){}
