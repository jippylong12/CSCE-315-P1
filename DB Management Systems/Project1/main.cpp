#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
#include "Parser.h"
#include "DBsystem.h"

using namespace std;



int main()
{	
	DBsystem db;

	vector<string> header;
	header.push_back("name");
	header.push_back("kind");
	header.push_back("years");

	vector<string> types;
	types.push_back("VARCHAR(20)");
	types.push_back("VARCHAR(8)");
	types.push_back("INTEGER");

	vector<string> keys;
	keys.push_back("name");
	keys.push_back("kind");




	db.CREATE(header.size(),"animals", header, keys, types);

	vector<string> input;
	input.push_back("Max");
	input.push_back("dog");
	input.push_back("10");
	db.INSERT("animals", input);

	input.clear();
	input.push_back("Snowball");
	input.push_back("cat");
	input.push_back("3");
	db.INSERT("animals", input);


	db.SHOW("animals");
	
	
	/*DBsystem db;
    
	vector<string> header1;
	header1.push_back("test1");
    header1.push_back("test2");
    header1.push_back("test3");
    header1.push_back("test4");
    
    vector<string> keys1;
	keys1.push_back("test1");
	
    vector<string> types1;
	types1.push_back("VARCHAR");
	
    db.CREATE(1,"test", header1,keys1,types1);
	vector<vector<string> > insert1;
	vector<string> insertHelper;
	insertHelper.push_back("hello");
    insertHelper.push_back("hello2");
	insert1.push_back(insertHelper);
	db.INSERT("test",insert1);
	//db.CLOSE("test");
	db.SHOW("test");
    
    vector<string> header2;
    
    header2.push_back("test1HEADERCHANGE");
    header2.push_back("test2HEADERCHANGE");
    header2.push_back("rename3");
    
    vector<string> project_Attributes;
    project_Attributes.push_back("test1HEADERCHANGE");
    project_Attributes.push_back("test2HEADERCHANGE");
    
    db.RENAME("test", header1, header2);    //Rename attributes to header2 vector
    db.SHOW("test");			    //Show the updated table
					    //Grab the tables with project_Attributes header
    vector<Table*> t1 = db.PROJECT("test", project_Attributes);
    for (int i = 0; i < project_Attributes.size(); ++i){
        cout << "PROJECTED HEADER: " << t1[0]->getHeaders()[i] << endl;
    }
	*/

}
