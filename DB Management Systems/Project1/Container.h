#include <string>
#include <vector>
#include <stack>
#include <iostream>

#include "Table.h"
using namespace std;


struct Container
{

    Table* tableState = new Table();
    stack<string> functionName;
    
    
    //OPEN
    string nameOpen;
    
    //CLOSE
    string nameClose;
   
   	//SAVE
   	string nameSave;
   	
   	//SHOW
   	string nameShow;
   	
   	//CREATE
   	string nameCreate;
   	vector<string> createHeaders;
   	vector<string> createKeys;
   	vector<string> createTypes;
   	vector<int> sizes;
    
    //update
    string nameUpdate;
    vector<string> updateHeaderName; //vector of header names
    vector<string> updateReplace;	 //replace with
    //WHERE condition
    vector<string> updateOperand1;
    vector<string> updateOperand2;
    vector<string> updateOP;


    //insert 
    string nameInsert;
	vector<string> insertInput;	//vector of inputs
	
	//delete
	string nameDelete;
	vector<string> deleteOperand1; //lhs
	vector<string> deleteOperand2; //rhs
	vector<string> deleteOP;
	
	//select
	//new Table Name should either be the newQueryName or a temp name
	string nameSelect;
	vector<string> selectHeader; //lhs
	vector<string> selectOP;
	vector<string> selectCondition; //rhs
	
	//project
	string nameProject;
	vector<string> projectAttributes;
	
	//rename
	string nameRename;
	//tableAttributes can be grabbed by using nameRename on the DB
	vector<string> renameReplaceAttributes;
	
	//SET_UNION
	string nameUnion1;
	string nameUnion2;
	//newName should be what's afer the <- or a tempName
	string newNameUnion;
	
	//SET_DIFFERENCE
	string nameDifference1;
	string nameDifference2;
	//newName should be what's before the <- or a tempName
	
	//CROSS_PRODUCT
	string nameCrossProduct1;
	string nameCrossProduct2;
	//newName should be what's afer the <- or a tempName
	
	
	
	    //query
    string lhsQuery; //lhs of query
	string rhsQuery;
	
	
	


	//I don't know how to declare this outside the struct
	//it will say its redeclared
	void clear() // this well erase all the vectors to empty again. 
	{
		while(functionName.size() > 0 )
		{
			functionName.pop();
		}
		//create
	   	createHeaders.clear();
	   	createKeys.clear();
	   	createTypes.clear();
	   	sizes.clear();	
	   	//insert
	   	insertInput.clear();
		//project
	   	projectAttributes.clear();
		//rename
	   	renameReplaceAttributes.clear();
	   	//UPDATE
	    updateHeaderName.clear();
	   	updateReplace.clear();
	   	updateOperand1.clear();
	   	updateOperand2.clear();
	   	updateOP.clear();
	   	//delete
	   	deleteOperand1.clear();
	   	deleteOperand2.clear();
	   	deleteOP.clear();
	   	//select
	   	selectHeader.clear();
	   	selectOP.clear();
	   	selectCondition.clear();
	   	
	}

};

