#include <string>
#include <vector>

using namespace std;


struct Container
{
    string functionName; //what to run
    string parserTableName; //table Name
    string updateHeaderName;
	vector<string> parserKeys; //keys
	vector<string> parserHeaders;
	vector<string> parserHeaderTypes;
	vector<int> parserHeaderSizes; //for VARCHAR INTEGERS are -1  
	void clear(); //clear all items in the 
};


void clear()
{
    
}