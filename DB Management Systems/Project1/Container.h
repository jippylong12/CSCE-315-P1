#include <string>
#include <vector>
#include <iostream>

using namespace std;


struct Container
{
	
    //items
    string functionName; //what to run
    string parserTableName; //table Name
    string secondTableName; //for functions with two tables
    
    //create	
	vector<string> parserKeys; //keys
	vector<string> parserHeaders;
	vector<string> parserHeaderTypes;
	vector<int> parserHeaderSizes; //for VARCHAR INTEGERS are -1  
    
    //update
    string updateHeaderName;
    string updateCriteria;
    string updateReplace;
    
    //insert
	vector<string> insertInput;
	
	//delete
	string deleteCompareHeader;
	string deleteCompareTo;
	
	//select
	string selectHeader;
	string selectComparator;
	string selectCondition;
	
	//project
	vector<string> projectAttributes;
	
	//rename
	vector<string> renameTableAttributes;
	vector<string> renameReplaceAttributes;
	
	//queries
	bool isSetUnion;
	bool isSetDifference;
	bool isCrossProduct;
	
	
	
	


	//I don't know how to declare this outside the struct
	//it will say its redeclared
	void clear() // this well erase all the vectors to empty again. 
	{
		parserKeys.clear();
		parserHeaders.clear();
		parserHeaderTypes.clear();
		parserHeaderSizes.clear();
		insertInput.clear();
		projectAttributes.clear();
		renameTableAttributes.clear();
		renameReplaceAttributes.clear();
		
		//I think we need to set the functionName to "" because for a query 
		//there is no function
		functionName = "";
		
		//reset bool values just in case. 
		isSetUnion = 0;
		isSetDifference = 0;
		isCrossProduct = 0;
	}

};

