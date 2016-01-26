#include "vector"

class Table
{
    vector< vector<string> > table;
    
public:
//-------Database command functions-------//

/*command ::= ( open-cmd | close-cmd | save-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd );*/
	Table(int,int); //constructor
	Table() { ; //default
	void open_cmd();  	//::== OPEN relation-name 
	void close_cmd(); 	//::== CLOSE relation-name 
	void save_cmd();  	//::== SAVE relation-name 
	void exit_cmd();	//::== EXIT 
	void show_cmd();    	//::== SHOW atomic-expr 
	void create_cmd();	//::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
	void update_cmd();	//::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
	void insert_cmd(string);	//::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) | INSERT INTO relation-name VALUES FROM RELATION expr
	void delete_cmd();	//::= DELETE FROM relation-name WHERE condition
	}
};