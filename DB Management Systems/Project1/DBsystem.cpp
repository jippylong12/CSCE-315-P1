/* _authors_
Marcus Salinas
Brian Ta
Deokman Park
Clifton Sims
Ivan Rupert */

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include "Parser.h"
#include "Table.h"

using namespace std;


class DBsystem
{
	vector<Table> database;

public:
	//-------Database queries--------//
	void SELECT();
	void PROJECT();
	void RENAME();
	void SET_UNION();
	void SET_DIFFERENCE();
	void CROSS_PRODUCT();
	void EXIT();
};



int main()
{
	//DBsystem db;
	vector<string> header1;
	header1.push_back("test1");
	vector<string> keys1;
	keys1.push_back("test1");
	Table t(1,10,"test", header1,keys1);
	t.show_cmd("test");

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