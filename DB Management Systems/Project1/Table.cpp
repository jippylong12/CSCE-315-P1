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
	tableHeaders = Source.tableHeaders;
	headerTypes = Source.headerTypes;
}

Table& Table::operator= (const Table &Source)
{
	table = Source.table;
	tableName = Source.tableName;
	rowLength = Source.rowLength;
	columnLength = Source.columnLength;
	primaryKeys = Source.primaryKeys;
	tableHeaders = Source.tableHeaders;
	headerTypes = Source.headerTypes;
	return *this;
}

Table::Table(int rows, int columns,string name, vector<string> headers, vector<string> keys, vector<string> types) //constructor
{
	rowLength = rows; //set the number of rows
	columnLength = columns; //set the nubmer of columns	
	tableName = name;
	tableHeaders = headers;
	table.resize(rows, vector<string>(columns)); //resize the table
	for(int i = 0;i<rows;++i) // set the headers
	{
		table[0][i] = tableHeaders[i];
	}
	//need to fiil the rest of the table.
	primaryKeys = keys; //set the primary keys
	headerTypes = types;
}

Table::Table() //defualt constructor
{
	rowLength = 1;
	columnLength = 2;
	tableName = "default";
	table.resize(1,vector<string>(1)); //default size is 1x1 that can be changed. 
	table[0][0] = "default" ; //give header
	tableHeaders.push_back("default"); //set default tableHeaders.
	primaryKeys.push_back("default"); //set primary keys
	headerTypes.push_back("default"); //set table header types.
	
}
Table::~Table(){}
