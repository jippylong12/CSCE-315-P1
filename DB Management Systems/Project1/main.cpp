#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
#include "Parser.h"
#include "DBsystem.h"

using namespace std;



int main()
{	
	DBsystem db;

	vector<string> header;
	header.push_back("name");
	header.push_back("kind");
	header.push_back("years");

	vector<string> types;
	types.push_back("VARCHAR(20)");
	types.push_back("VARCHAR(8)");
	types.push_back("INTEGER");

	vector<string> keys;
	keys.push_back("name");
	keys.push_back("kind");

	cout<<"Testing Create \n\n";
	db.CREATE(header.size(),"animals", header, keys, types);
	

	vector<string> input;
	input.push_back("Max");
	input.push_back("dog");
	input.push_back("10");
	
	cout<<"Testing Insert \n\n";
	
	db.INSERT("animals", input);
	
	cout << "CREATE table animals with 1 item inserted:" << endl;
	db.SHOW("animals");

	input.clear();
	input.push_back("Snowball");
	input.push_back("dog");
	input.push_back("3");
	db.INSERT("animals", input);

	cout << "INSERT 1 more item:" << endl;
	db.SHOW("animals");
	
	cout<<"Testing Update \n\n";
	
	db.UPDATE("animals","kind", "dog", "cat");

	cout << "UPDATE item 2:" << endl;
	db.SHOW("animals");

	db.UPDATE("animals", "name", "Max", "Spot");

	cout << "UPDATE item 1:" << endl;
	db.SHOW("animals");
	
	cout << "Update item 3:\n";
	db.UPDATE("animals", "years", "10", "12");
	db.SHOW("animals");
	
	cout<<"Save database: \n\n";
	
	db.SAVE("animals");
	

	
	input.clear();
	input.push_back("Max");
	input.push_back("dog");
	input.push_back("10");
	db.INSERT("animals", input);
	
	input.clear();
	input.push_back("Spot");
	input.push_back("dog");
	input.push_back("5");
	db.INSERT("animals", input);

	db.SHOW("animals");


	cout << "SELETE only dogs: \n";
	Table* newTable = db.SELECT("dogs","animals", "kind", "=", "dog");
	db.addTable(newTable);

	db.SHOW("dogs");



}
