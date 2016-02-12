#include <string>
#include <vector>
#include <iostream>

using namespace std;


struct Container
{
	//items
    string functionName; //what to run
    string parserTableName; //table Name
    string updateHeaderName;
	
	
	
	vector<string> parserKeys; //keys
	vector<string> parserHeaders;
	vector<string> parserHeaderTypes;
	
	vector<int> parserHeaderSizes; //for VARCHAR INTEGERS are -1  

	void clear() // this well erase all the vectors to empty again. s
	{
		cout<<"I am working"<<endl;
	}

};

