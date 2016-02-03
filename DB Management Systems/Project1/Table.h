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
 	vector<string> tableHeaders;
 	vector<string> headerTypes;
    
public:
    
    
	//-------Database command functions-------//

	/*command ::= ( open-cmd | close-cmd | save-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd );*/
	//Table Constructor
	Table(int,string, vector<string>, vector<string>, vector<string>); //constructor	
	Table(); 			//default
	~Table();
	Table(const Table &Source); //copy constructor
	Table& operator= (const Table &Source); //overloading
	void setTableName(string tName) { tableName = tName;}
	int getRowLength() { return rowLength;} 
	int getColumnLength() { return columnLength;}
	void setRowLength(int r) { rowLength =r;}
	void setColumnLength(int l) { columnLength = l;}
	void setTable(vector< vector<string> > setTble) { table = setTble;}
	vector<string> getPrimnaryKey() { return primaryKeys;} //return key vector
    //void setRows(vector<string> rows){ for (int i = 0; i < columnLength; ++i) { this->table[i] = rows;  }
	void setPrimaryKeys(vector<string> setKeys) { primaryKeys = setKeys;} //set any of the values of the primary key
	vector<string> getPrimaryKeys() {return primaryKeys;}
	string getTableName() { return tableName;}
	vector< vector<string> > getTable() {return table;}
	vector<string> getHeaders() {return tableHeaders;}
    void setHeader(vector<string> tableHeaders);
    vector<string> getHeaderTypes() {return headerTypes;}
    void setHeaderTypes(vector<string> tempHeaderType) { headerTypes = tempHeaderType;}

	
};



