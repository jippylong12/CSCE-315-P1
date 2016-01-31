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
    db.SHOW("test");
    
    vector<Table*> t1 = db.PROJECT("test", project_Attributes);
    for (int i = 0; i < project_Attributes.size(); ++i){
        cout << "PROJECTED HEADER: " << t1[0]->getHeaders()[i] << endl;
    }


}