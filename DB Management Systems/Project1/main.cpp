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
	
	
	ifstream in("animals.db");
	stringstream buffer;
	buffer << in.rdbuf();
	string fileInput = buffer.str();		//Store all file input into one string
	//Parser p(fileInput);					//Parse on "animals.db"
	
	//Test the CREATE query
	
	


	Parser p("CREATE TABLE animals (name VARCHAR(20), years INTEGER, kind VARCHAR(8)) PRIMARY KEY (name);");
	cout << endl;

	
	Parser a("UPDATE ass SET asset = \"butt\", asset = \"butt\", asset = \"butt\" WHERE buttSize >= buttLength;");  //Should pass
	cout << endl;
	
	Parser ab("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);"); 
	cout << endl;
	
	Parser b("OPEN animals;");  		//Should pass
	cout << endl;
	
	Parser c("SHOW animals;");
	cout << endl;
	Parser d("SAVE animals;");
	cout << endl;
	Parser e("sAVe animals;");		//Should fail
	cout << endl;
	Parser ef("CLOSE animals;");	
	cout << endl;
	Parser f("DELETE FROM animals WHERE age > 0;");
	cout << endl;
	Parser g("DELETE fram animalz WHERE age > 0;");	//Should fail
	cout << endl;
	
	Parser i("dogs <- select (kind == \"dog\") animals;");
	cout << endl;
	
	Parser j("common_names <- project (name) (select (aname == name && akind != kind) animals);");
	cout << endl;
	
	Parser k("a <- rename (aname, akind) (project (name, kind) animals);");
	cout << endl;
	
	Parser l("a <- a + animals;");
	cout << endl;
	
	Parser m("a <- somethingTable - (select (aname == name && akind != kind) animals);");
	cout << endl;

	Parser n("b <- (project (name) (select (aname == name && akind != kind) animals)) * (select (aname == name && akind != kind) animals);");
	cout << endl;
	
	Parser o("b <- (project (name) (select (aname == name && akind != kind) animals));");
	cout << endl;

	
	

	
	
	
	
	
	/*vector<string> header;
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

	cout<<"Testing Create \n\n";
	db.CREATE(header.size(),"animals", header, keys, types);
	

	vector<string> input;
	input.push_back("Max");
	input.push_back("dog");
	input.push_back("10");
	
	cout<<"Testing Insert \n\n";
	
	db.INSERT("animals", input);
	
	cout << "CREATE table animals with 1 item inserted:" << endl;
	db.SHOW("animals");

	input.clear();
	input.push_back("Snowball");
	input.push_back("dog");
	input.push_back("3");
	db.INSERT("animals", input);

	cout << "INSERT 1 more item:" << endl;
	db.SHOW("animals");
	
	cout<<"Testing Update \n\n";
	
	db.UPDATE("animals","kind", "dog", "cat");

	cout << "UPDATE item 2:" << endl;
	db.SHOW("animals");

	db.UPDATE("animals", "name", "Max", "Spot");
	
	cout << "Update item 3:\n";
	db.UPDATE("animals", "years", "10", "12");
	db.SHOW("animals");
	
	cout<<"Save database: \n\n";
	
	db.SAVE("animals");
	

	cout << "INSERT 2 more items:" << endl;
	input.clear();
	input.push_back("Max");
	input.push_back("dog");
	input.push_back("9000");
	db.INSERT("animals", input);
	
	input.clear();
	input.push_back("Spot");
	input.push_back("dog");
	input.push_back("5000");
	db.INSERT("animals", input);

	
	
	cout<<"Testing SELECT\n";


	

	cout << "SELETE only dogs: \n";
	Table* newTable = db.SELECT("dogs","animals", "kind", "=", "dog");
	db.addTable(newTable);

	db.SHOW("dogs");
	
        //----RENAME test----//
    	input.clear();
    	cout << "RENAME attributes of \"dogs\": \n";
    	input.push_back("NEWname");
    	input.push_back("NEWkind");
    	input.push_back("NEWage");
    	db.RENAME("dogs", header, input);
    	db.SHOW("dogs");
        //------------------//
    
      vector<string> attr;
      attr.push_back("NEWname");
      attr.push_back("N");
      attr.push_back("NEWage");
      db.PROJECT("dogs", attr);
      db.SHOW("dogs");
    
	db.SHOW("dogs");
	cout<<"Removing Max\n\n";
	db.DELETE("dogs", "NEWname", "Max");
	db.SHOW("dogs");
	db.SHOW("animals");
    //db.SET_UNION("dogs", "animals");
    db.CROSS_PRODUCT("animals", "dogs");
    db.SHOW("animals");

	db.SET_DIFFERENCE("animals", "dogs");	
	db.SHOW("animals");
	
	cout<<"Testing EXIT\n\n";
	db.EXIT();*/

}
