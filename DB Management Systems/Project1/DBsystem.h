#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>

#include "Parser.h"

class DBsystem
{
public:
	DBsystem();
	
	void execute(); //connect Parser containers to DB functions
	map<string, Table*> getDB() { return database; }
	map<string, Table*> database;
	Table* temp;
	bool tempDeclared =0;
	//Parser
	Parser DBParser;
	
	//-------Database commands--------//
	Table* OPEN(string); //bring a table into memory from file
	int CLOSE(string);
	int SAVE(string);
	int SHOW(string);    	//::== SHOW atomic-expr 
	Table* CREATE(int,string,vector<string>,vector<string>,vector<string>,vector<int>); //::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
	int UPDATE(string, vector<string>, vector<string>,vector<string>,vector<string>,vector<string>);	//::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
	int INSERT(string, vector<string> );	//::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) | INSERT INTO relation-name VALUES FROM RELATION expr
	int DELETE(string , vector<string>, vector<string>,vector<string> );	//::= DELETE FROM relation-name WHERE condition
	void EXIT();
	//-------Database queries (need definitions)-------//
	Table* SELECT(string,string, vector<string>, vector<string>, vector<string>);    //select table with certain criteria
	vector<Table*>  PROJECT(string, vector<string>);
	Table* RENAME(string, vector<string>, vector<string>);			
	Table* SET_UNION(string, string, string);			//Take the union of 2 tables
	Table* SET_DIFFERENCE(string, string,string);		//2 table names
	Table* CROSS_PRODUCT(string, string,string);		//2 table names used to perform cross product
	void addTable(Table* newTable) { database[newTable->getTableName()] = newTable; }
	
	
};
