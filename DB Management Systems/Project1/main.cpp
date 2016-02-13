#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
#include "DBsystem.h"

using namespace std;



int main()
{	
	string input0;
	
	 while(1)
	 {
	 	DBsystem db;
		
	 	cout<<"What is the command?"<<endl;
	 	getline (cin,input0); //take the command
	 	db.getParser().sendNewInput(input0);
	 	db.execute(); //not implemented yet but will take the command and use switch statement to know what to run
	 	db.getParser().getContainer().clear(); //Not implementted yet but will reset all things in container to 0
		
	 }

	
	// ifstream in("animals.db");
	// stringstream buffer;
	// buffer << in.rdbuf();
	// string fileInput = buffer.str();		//Stores all file input into one string

	//DBsystem db;
	//db.OPEN("animals");
	
	//db.getParser().sendNewInput("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
	// //db.getParser().sendNewInput("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
	// cout<<endl;
	//if(db.getParser().parse_CREATE() == true){
	//	cout << "Creating..." << endl;
	//}
	
	//cout << "Parser in: " << db.getParser().getInput() << endl;
	

	
	// Parser a("UPDATE ass SET asset = \"butt\", asset = \"butt\", asset = \"butt\" WHERE buttSize >= buttLength;");  //Should pass
	// cout << endl;
	
	// Parser ab("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);"); 
	// cout << endl;
	
	// Parser b("OPEN animals;");  		//Should pass
	// cout << endl;
	
	// Parser c("SHOW animals;");
	// cout << endl;
	// Parser d("SAVE animals;");
	// cout << endl;
	// Parser e("sAVe animals;");		//Should fail
	// cout << endl;
	// Parser ef("CLOSE animals;");	
	// cout << endl;
	// Parser f("DELETE FROM animals WHERE age > 0;");
	// cout << endl;
	// Parser g("DELETE fram animalz WHERE age > 0;");	//Should fail
	// cout << endl;
	
	// Parser i("dogs <- select (kind == \"dog\") animals;");
	// cout << endl;
	
	// Parser j("common_names <- project (name) (select (aname == name && akind != kind) animals);");
	// cout << endl;
	
	// Parser k("a <- rename (aname, akind) (project (name, kind) animals);");
	// cout << endl;
	
	// Parser l("a <- a + animals;");
	// cout << endl;
	
	// Parser m("a <- somethingTable - (select (aname == name && akind != kind) animals);");
	// cout << endl;

	// Parser n("b <- (project (name) (select (aname == name && akind != kind) animals)) * (select (aname == name && akind != kind) animals);");
	// cout << endl;
	
	// Parser o("b <- (project (name) (select (aname == name && akind != kind) animals));");
	// cout << endl;

	
}
