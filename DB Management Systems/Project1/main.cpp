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
	vector<string> header1;
	header1.push_back("test1");
	vector<string> keys1;
	keys1.push_back("test1");
	vector<string> types1;
	types1.push_back("VARCHAR");
	db.CREATE(1,"test", header1,keys1,types1);
	vector<vector<string> > insert1;
	vector<string> insertHelper;
	insertHelper.push_back("hello");
	insert1.push_back(insertHelper);
	db.INSERT("test",insert1);
	//db.CLOSE("test");
	db.SHOW("test");

	cout << "Starting main..." << endl;
	cout << "Enter command: " << endl;


	string mainInput;
	while (true)
	{
		getline(cin, mainInput);
		Parser mainParser(mainInput);
	    mainParser.parse();
		
	}
}