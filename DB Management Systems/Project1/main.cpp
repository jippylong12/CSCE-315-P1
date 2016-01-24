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


//-------Database queries--------//
	void SELECT();
	void PROJECT();
	void RENAME();
	void SET_UNION();
	void SET_DIFFERENCE();
	void CROSS_PRODUCT();
//-------Database command functions-------//

/*command ::= ( open-cmd | close-cmd | save-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd );*/
	void open_cmd();  	//::== OPEN relation-name 
	void close_cmd(); 	//::== CLOSE relation-name 
	void save_cmd();  	//::== SAVE relation-name 
	void exit_cmd();	//::== EXIT 
	void show_cmd();    	//::== SHOW atomic-expr 
	void create_cmd();	//::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
	void update_cmd();	//::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
	void insert_cmd();	//::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) | INSERT INTO relation-name VALUES FROM RELATION expr
	void delete_cmd();	//::= DELETE FROM relation-name WHERE condition

//-------Parser

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
	cout << "Starting..." << endl;
	cout << "Enter command: " << endl;
	string mainInput;
	while (true)
	{
		getline(cin, mainInput);
		Parser mainParser(mainInput);
		mainParser.parse();
	}
}
