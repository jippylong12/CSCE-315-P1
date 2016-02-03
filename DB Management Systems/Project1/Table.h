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
	
	int getRowLength() { return rowLength;} 
	void setRowLength(int r) { rowLength = r;}
	int getColumnLength() { return columnLength;}
	void setColumnLength(int l) { columnLength = l;}
	void setTable(vector< vector<string> > setTble) { table = setTble;}
	vector< vector<string> > getTable() {return table;}
    //void setRows(vector<string> rows){ for (int i = 0; i < columnLength; ++i) { this->table[i] = rows;  }
	vector<string> getPrimnaryKey() { return primaryKeys;} //return key vector
	void setPrimaryKey(vector<string> setKeys) { primaryKeys = setKeys;} //set any of the values of the primary key
	string getTableName() { return tableName;}
	void setTableName(string tName) { tableName = tName;}
	vector<string> getHeaders() {return tableHeaders;}
    void setHeader(vector<string> tableHeaders);
    vector<string> getHeaderTypes() {return headerTypes;}
    void setHeaderTypes(vector<string> tempHeaderType) { headerTypes = tempHeaderType;}
    
    bool EQUALS(string,string);
    bool NOT_EQUALS(string,string);
    bool LESS_THAN(string,string);
    bool GREATER_THAN(string,string);
    bool LESS_THEN_EQUALS(string,string);
    bool GREATER_THAN_EQUALS(string,string);

	
};



