#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Table
{
    vector< vector<string> > table; //represents one table
    string tableName;
    int rowLength; //number of rows
    int columnLength; //number of columns
 	vector<string> primaryKeys; //primary keys
    
public:
	//-------Database command functions-------//

	/*command ::= ( open-cmd | close-cmd | save-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd );*/
	//Table Constructor
	Table(int,int,string, vector<string>, vector<string>); //constructor	
	Table(); 			//default
	Table(const Table &Source); //copy constructor
	Table& operator= (const Table &Source); //overloading
	int getRowLength() { return rowLength;} 
	int getColumnLength() { return columnLength;}
	vector<string> getPrimnaryKey() { return primaryKeys;} //return key vector
	void setPrimaryKey(vector<string> setKeys) { primaryKeys = setKeys;} //set any of the values of the primary key
	string getTableName() { return tableName;}
	vector< vector<string> > getTable() {return table;}
	
};



