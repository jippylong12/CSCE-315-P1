//-------Parser

#include "Parser.h"

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