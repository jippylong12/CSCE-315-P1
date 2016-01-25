#include <iostream>
#include <cstring>


using namespace std;

class Parser
{
	string input;
public:
	Parser(string);
	char * parse();
	string getInput() {return input;}; 

};