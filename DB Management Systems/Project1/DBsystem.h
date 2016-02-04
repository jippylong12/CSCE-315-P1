#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
#include "Table.h"

class DBsystem
{
	map<string,Table*> database;

public:
	DBsystem();
	
	//-------Database queries--------//
	Table* OPEN(string); //bring a table into memory from file 
	int CLOSE(string);
	int SAVE(string);
	int SHOW(string);    	//::== SHOW atomic-expr 
	Table* CREATE(int,string,vector<string>,vector<string>,vector<string>); //::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
	int UPDATE(string, string, string, string);	//::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
	int INSERT(string, vector<string> );	//::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) | INSERT INTO relation-name VALUES FROM RELATION expr
	int DELETE(string , int );	//::= DELETE FROM relation-name WHERE condition
	void EXIT();
	//-------Database commands (need definitions)-------//
	Table* SELECT(string, string, string, string);    //select table with certain criteria
	vector<Table*>  PROJECT(string, vector<string>);
	Table* RENAME(string, vector<string>, vector<string>);			
	Table* SET_UNION(string, string);			//Take the union of 2 tables
	Table* SET_DIFFERENCE(string, string);		//2 table names
	Table* CROSS_PRODUCT(string, string);		//2 table names used to perform cross product
	map<string,Table*> getDB() {return database;}
	
};
