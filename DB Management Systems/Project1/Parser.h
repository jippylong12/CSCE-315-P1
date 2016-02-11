#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include "Container.h"
using namespace std;



class Parser
{
	string input;
	queue<string> tokens;
	bool parsedCorrect = false;
	Container contain;
	
public:
	Parser(string); //constructor
	Parser() { input = "";} //default
	
	//Parser functions
	void parse();
	void sendNewInput(string);
	string getInput() {return input;}
	
	
	
	
	//Recursive Parser functions
	//Query functions
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
	
	//Command functions
	//merging with the DB
	bool parse_OPEN();			//Parse the OPEN query...etc
	bool parse_SAVE();
	bool parse_CLOSE();
	bool parse_SHOW();
	bool parse_CREATE();
	bool parse_UPDATE();
	bool parse_INSERT();
	bool parse_DELETE();
	bool parse_EXIT();
	bool parse_SELECT();
	bool parse_PROJECT();
	bool parse_RENAME();
	bool parse_SET_UNION();
	bool parse_SET_DIFFERENCE();
	bool parse_CROSS_PRODUCT();

};