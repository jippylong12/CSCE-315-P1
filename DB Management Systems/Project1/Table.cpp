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
	headerSizes = Source.headerSizes;
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
	headerSizes = Source.headerSizes;
	return *this;
}

Table::Table(int columns,string name, vector<string> headers, vector<string> keys, vector<string> types, vector<int> sizes) //constructor
{
	rowLength = 0; //set the number of rows
	columnLength = columns; //set the nubmer of columns	
	tableName = name;
	tableHeaders = headers;
	//need to fiil the rest of the table.
	primaryKeys = keys; //set the primary keys
	headerTypes = types;
	headerSizes = sizes;
}

Table::Table() //defualt constructor
{
	rowLength = 0;
	columnLength = 1;
	tableName = "default";
	tableHeaders.push_back("default"); //set default tableHeaders.
	primaryKeys.push_back("default"); //set primary keys
	headerTypes.push_back("default"); //set table header types.
	
}
void Table::setHeader(vector<string> newHeader){
    this->tableHeaders = newHeader;
}
Table::~Table(){}
