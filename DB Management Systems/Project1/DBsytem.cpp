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
	cout << "Starting..." << endl;
	cout << "Enter command: " << endl;
	string mainInput;
	DBsystem db;
	Table t(2,10);
	while (true)
	{
		getline(cin, mainInput);
		Parser mainParser(mainInput);
	    mainParser.parse();
		
	}
}