/* _authors_
Marcus Salinas
Brian Ta
Deokman Park
Clifton Sims */


#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class Parser
{
	string input;
public:
	Parser(string);
	char * parse();
	string getInput() {return input;}; 

};

Parser::Parser(string in)
{
	input = in;
}

char * Parser::parse()
{
	char * cstring = new char [input.length()+1];
	strcpy(cstring, input.c_str());
	char * parsing = strtok(cstring," ");
	while(parsing!=0)
	{
		cout<<parsing <<endl;
		parsing = strtok(NULL," ");
	}
	return cstring;
}



int main()
{
	cout << "Staring.." << endl;
	cout << "Enter command: " << endl;
	string mainInput;
	while (true)
	{
		getline(cin, mainInput);
		Parser mainParser(mainInput);
		mainParser.parse();
	}
}