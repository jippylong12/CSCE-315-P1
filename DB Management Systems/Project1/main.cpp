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
	db.CREATE(1,1,"test", header1,keys1,types1);
	//db.CLOSE("test");
	//db.INSERT("testtt", 1, 1);
	db.SHOW("test");
	//t.show_cmd("test");

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