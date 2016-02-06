#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;



class Parser
{
	string input;
	queue<string> tokens;
	bool parsedCorrect = false;
public:
	Parser(string);
	char * parse();
	string getInput() {return input;}; 
	
	//Adding possible functions for the parser
	
	
	void lexer(string input);	//LEX the input string into tokens
	
	bool isOP();
	bool isType(string);
	bool isIdentifier(string);
	bool isTypedAttributeList();
	bool isAtomicExpression();
	
	bool parse_OPEN();			//Parse the OPEN query...etc
	bool parse_SAVE();
	bool parse_SHOW();
	bool parse_CREATE();
	bool parse_UPDATE();
	bool parse_INSERT();
	bool parse_DELETE();

	bool parse_SELECT();
	bool parse_PROJECT();
	bool parse_RENAME();
	bool parse_SET_UNION();
	bool parse_SET_DIFFERENCE();
	bool parse_CROSS_PRODUCT();

};