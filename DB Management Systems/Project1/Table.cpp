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

Table::Table(int columns,string name, vector<string> headers, vector<string> keys, vector<string> types) //constructor
{
	rowLength = 0; //set the number of rows
	columnLength = columns; //set the nubmer of columns	
	tableName = name;
	tableHeaders = headers;
	//need to fiil the rest of the table.
	primaryKeys = keys; //set the primary keys
	headerTypes = types;
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

//************Comparators***************//
    bool EQUALS(string field1,string field2)
    {
    	if (field1.compare(field2) == 0)
    	{
    		return 1;
    	}
    	else return 0;
    	
    }
    bool NOT_EQUALS(string field1,string field2)
    {
    	 if (field1.compare(field2) != 0)
    	{
    		return 1;
    	}
    	else return 0;
    }
    bool LESS_THAN(string field1,string field2)
    {
    	if (field1.compare(field2) < 0)
    	{
    		return 1;
    	}
    	else return 0;
    }
    bool GREATER_THAN(string field1,string field2) //field1 greateer than field 2
    {
    	if (field1.compare(field2) > 0)
    	{
    		return 1;
    	}
    	else return 0;
    }
    bool LESS_THEN_EQUALS(string field1,string field2)
    {
      	if (field1.compare(field2) == 0 || field1.compare(field2) < 0)
    	{
    		return 1;
    	}
    	else return 0;
    }
    bool GREATER_THAN_EQUALS(string field1,string field2)
    {
        if (field1.compare(field2) > 0 || field1.compare(field2) == 0)
    	{
    		return 1;
    	}
    	else return 0;	
    }
    
