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
	
	//Adding possible functions for the parser
	
	
	void lexer(string input);	//LEX
	
	bool parse_Open();			//Parse the OPEN query...etc
	bool parse_Save();
	bool parse_Show();
	bool parse_Create();
	bool parse_Update();
	bool parse_Insert();
	bool parse_Delete();

	bool parse_SELECT();
	bool parse_PROJECT();
	bool parse_RENAME();
	bool parse_SET_UNION();
	bool parse_SET_DIFFERENCE();
	bool parse_CROSS_PRODUCT();

};