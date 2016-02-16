#include <string>
#include <vector>
#include <stack>
#include <iostream>

#include "Table.h"
using namespace std;


struct Container
{

    Table* tableState = new Table();
    
    //items
    stack<string> functionName; //what to run
    string parserTableName; //table Name
    string secondTableName; //for functions with two tables
    
    //query
    string newQueryName; 
    //create	
	vector<string> parserKeys; //keys
	vector<string> parserHeaders;
	vector<string> parserHeaderTypes;
	vector<int> parserHeaderSizes; //for VARCHAR INTEGERS are -1  
    
    //update
    vector<string> updateHeaderName; //vector of header names
    string updateCriteria;			 //WHERE condition
    vector<string> updateReplace;	 //replace with
    
    string updateCompareHeader;
    string updateOP;        //Operator for update
    string updateCompareTo; //get other side
    
    //insert
	vector<string> insertInput;	//vector of inputs
	string insertExpr;			//expr for relation
	
	//delete
	string deleteCompareHeader;
	string deleteCompareTo;
	string deleteOP;
	
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
		while(functionName.size() > 0 )
		{
			functionName.pop();
		}
		
		parserKeys.clear();
		parserHeaders.clear();
		parserHeaderTypes.clear();
		parserHeaderSizes.clear();
		insertInput.clear();
		projectAttributes.clear();
		renameTableAttributes.clear();
		renameReplaceAttributes.clear();
		
		while(functionName.size() > 0)
		{
			functionName.pop();
		}
		parserTableName = ""; //table Name
    	secondTableName = ""; //for functions with two tables
		
		
		//reset bool values just in case. 
		isSetUnion = 0;
		isSetDifference = 0;
		isCrossProduct = 0;
	}

};

