#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;



class Parser
{
	string input;
	queue<string> tokens;
	bool parsedCorrect = false;
public:
	Parser(string);
	void parse();
	string getInput() {return input;}; 
	
	//Adding possible functions for the parser
	
	
	void lexer(string input);	//LEX the input string into tokens
	
	//checking syntax
	bool isCommand();
	bool isQuery(); 
	bool isExpression();
	bool isCondition();
	bool isConjunction();
	bool isComparison();
	bool isOP();
	bool isType(string);
	bool isLiteral(string);
	bool isIdentifier(string);
	bool isAttributeList();
	bool isTypedAttributeList();
	bool isAtomicExpression();
	bool isSelection();
	bool isProjection();
	bool isRenaming();
	bool isSetUnion();
	bool isSetDifference();
	bool isCrossProduct();
	
	//merging with the DB
	bool parse_OPEN();			//Parse the OPEN query...etc
	bool parse_SAVE();
	bool parse_CLOSE();
	bool parse_SHOW();
	bool parse_CREATE();
	bool parse_UPDATE();
	bool parse_INSERT();
	bool parse_DELETE();
	//merging with the DB
	bool parse_SELECT();
	bool parse_PROJECT();
	bool parse_RENAME();
	bool parse_SET_UNION();
	bool parse_SET_DIFFERENCE();
	bool parse_CROSS_PRODUCT();

};