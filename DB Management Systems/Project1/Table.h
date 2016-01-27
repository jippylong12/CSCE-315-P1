#include <vector>
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
	int getRowLength() { return rowLength;} 
	int getColumnLength() { return columnLength;}
	vector<string> getPrimnaryKey() { return primaryKeys;} //return key vector
	void setPrimaryKey(vector<string> setKeys) { primaryKeys = setKeys;} //set any of the values of the primary key
	
	
};



