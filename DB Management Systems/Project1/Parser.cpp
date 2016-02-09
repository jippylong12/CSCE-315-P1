//-------Parser

#include "Parser.h"
#include <typeinfo>

Parser::Parser(string in)
{
	input = in;
	parse();
	
	if(isCommand()){ }
	else { isQuery(); }
	
	
}



void Parser::parse()
{
	
	int stringCount = 0;
	int splitStart = 0;
	int splitEnd = 0;
	string subString;
	
	char * cstring = new char [input.length()+1];
	strcpy(cstring, input.c_str());
	
	istringstream iss(cstring);
	while(iss.get() != -1)
	{
		if(input[stringCount] == ' ' || input[stringCount] == '(' 
			|| input[stringCount] == ')' || input[stringCount] == ','  || input[stringCount] == ';')
		{
			if (input[stringCount] != ' ')
			{
				if (subString != "")
				{
					tokens.push(subString);
				}
				subString = input[stringCount];
				tokens.push(subString);
				subString = "";
			}
			else
			{
				tokens.push(subString);
				subString = "";
			}

		}
		else
		{
			subString.push_back(input[stringCount]);
		}
		++stringCount;		
	}
	
	queue<string> temp;
	int tokenSize = tokens.size();
	for(int i = 0; i<tokenSize; ++i)
	{
		if(tokens.front() == ", ")
		{
			temp.push(",");
			tokens.pop();
			
		}
		else if(tokens.front() != "")
		{
			temp.push(tokens.front());
			cout<<tokens.front()<<endl;
			tokens.pop();
		}
		else
		{
			
			tokens.pop();
		}
	}
	
	tokens = temp;
	// for (int i = 0; i < tokens.size(); ++i)
	// {
	// 	if (tokens[i] == "")
	// 		tokens.erase(tokens.begin() + i);
	// }
}

bool Parser::isCommand()
{
	string firstToken = tokens.front();
	
	if(firstToken.compare("CREATE") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_CREATE();
		if (parsedCorrect){ cout << "CREATE - valid command." << endl; } 
		else{ cout << "CREATE - invalid command." << endl; } 
	}
	else if(firstToken.compare("UPDATE") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_UPDATE();
		if (parsedCorrect){ cout << "UPDATE - valid command." << endl; } 
		else{ cout << "UPDATE - invalid command." << endl; } 
	}
	else if(firstToken.compare("INSERT") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_INSERT();
		if (parsedCorrect){ cout << "INSERT - valid command." << endl; } 
		else{ cout << "INSERT - invalid command." << endl; } 
	}
	else if(firstToken.compare("SHOW") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_SHOW();
		if (parsedCorrect){ cout << "SHOW - valid command." << endl; } 
		else{ cout << "SHOW - invalid command." << endl; } 
	}
	else if(firstToken.compare("OPEN") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_OPEN();
		if (parsedCorrect){ cout << "OPEN - valid command." << endl; } 
		else{ cout << "OPEN - invalid command." << endl; } 
	}
	else if(firstToken.compare("SAVE") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_SAVE();
		if (parsedCorrect){ cout << "SAVE - valid command." << endl; } 
		else{ cout << "SAVE - invalid command." << endl; } 
	}
	else if(firstToken.compare("CLOSE") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_CLOSE();	
		if (parsedCorrect){ cout << "CLOSE - valid command." << endl; } 
		else{ cout << "CLOSE - invalid command." << endl; } 
	}
	else if(firstToken.compare("DELETE") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_DELETE();
		if (parsedCorrect){ cout << "DELETE - valid command." << endl; } 
		else{ cout << "DELETE - invalid command." << endl; } 
		
	}
	else{
		cout << "Error: Command not found!" << endl;
		return false;
	}
	
	return true;
}

bool Parser::isExpression()
{
	string firstToken = tokens.front();
	
	if(isSelection(firstToken))
	{
		return true;	
	}
	else if(isProjection(firstToken))
	{
		return true;
		
	}
	else if(isRenaming(firstToken))
	{
		return true;
	
	}
	else if(isSetUnion())
	{
		return true;
		
	}
	else if(isSetDifference())
	{
		return true;
		
	}
	else if(isCrossProduct())
	{
		return true;
		
	}
	else if(isAtomicExpression())
	{
		return true;
	}
	
	else{
		cout << "Error: Query not found!" << endl;
		return false;
	}
}

bool Parser::isQuery()
{
	//check for relation name
	string firstToken = tokens.front(); //get the name
	if(!isIdentifier(firstToken)) //check 
		return false; //return false if not
	tokens.pop(); //pop it off the top
	
	firstToken = tokens.front(); //check for <-
	if(firstToken.compare("<-")) //check
		return false; //return if false
	tokens.pop(); //remove if passed
	
	//check if expression
	if(!isExpression())
		return false; //return if not
	
	return true; //if everything passes return trues
}

bool Parser::isIdentifier(string name) //attribute name and relation name
{
	for(int i = 0; i < name.length(); i++)
	{
		if('A' <= name[i] && name[i] <= 'Z'){}
		else if('a' <= name[i] && name[i] <= 'z'){}
		else if('0' <= name[i] && name[i] <= '9'){}
		else{return false;}
	}
	return true;
}

bool Parser::isType(string type) //checks if INTEGER or VARCHAR
{
	if(type.compare("INTEGER") == 0)
	{
		tokens.pop();
		return true;
	}
	else if(type.compare("VARCHAR") == 0)
	{
		tokens.pop();
		type = tokens.front();
		if(type.compare("(") == 0)
		{
			tokens.pop();
			type = tokens.front();

			for(int i = 8; i < type.length()-1; i++)
			{
				if('0' <= type[i] && type[i] <= '9'){}
				else {return false;}
			}
			
			
			tokens.pop();
			type = tokens.front();
			if(type.compare(")") == 0)
			{
				tokens.pop();
				return true;
			}
				
		}
	
	}
	 
	return false;
		
}

bool Parser::isAttributeList()
{
	if(tokens.front().compare("("))
		return false;
	while(true)
	{
		tokens.pop();
		
		if(!isIdentifier(tokens.front()))
			return false;
		tokens.pop();

		if(tokens.front().compare(",") == 0 )
		{
			continue;
		}
		else if(tokens.front().compare(")") == 0)
		{
			return true;
		}
		
	}
}
	


bool Parser::isTypedAttributeList()
{
	if(tokens.front().compare("("))
		return false;
	while(true)
	{
		tokens.pop();
		
		if(!isIdentifier(tokens.front()))
			return false;
		tokens.pop();
		

		if(!isType(tokens.front()))
			return false;
		
		if(tokens.front().compare(",") == 0 )
		{
			continue;
		}
		else if(tokens.front().compare(")") == 0)
		{
			return true;
		}
		
	}
	

}


bool Parser::isAtomicExpression() //checks if selection, projection, renaming, union, difference, or product
{								  //Can also be a relation name (which is an identifier)
	
	string next = tokens.front(); //get the next input
	if(isIdentifier(next)) //if it is a relation name
	{
		return true;
	}
	else if(tokens.front()[0] == '(') //it is an expression
	{
		tokens.pop(); //remove the (
		if(isExpression()) //test to see if expression
		{
			tokens.pop(); //remove the )
			return true;
		}
	}
	else //if ti's not an expression or a relation name it's improper syntax 
	{
		return false;
	}
	
}





bool Parser::isOP() //checks if == | != | < | > | <= | >=
{
	
	if(tokens.front().compare("==")==0){return true;}
	else if(tokens.front().compare("!=")==0){return true;}	
	else if(tokens.front().compare("<")==0){return true;}
	else if(tokens.front().compare(">") ==0){return true;}
	else if(tokens.front().compare("<=")==0){return true;}
	else if(tokens.front().compare(">=")==0){return true;}
	else{ cout << "error in syntax, not an OP" << endl; return false;}
	
	return true;
}

bool Parser::isComparison() 
{
	
	if(!isIdentifier(tokens.front()))
		return false;
	tokens.pop();
	
	
	if(!isOP())
		return false;
	tokens.pop();
	
	if(!isIdentifier(tokens.front()))
		return false;
	tokens.pop();
	return true;
}

bool Parser::isConjunction()
{
	while(true)
	{
		if(!isComparison())
			return false;
			
		if(tokens.front().compare("&&")==0)
		{
			tokens.pop();
			continue;
		}
		else
			break;
	}
		
	return true;
}


bool Parser::isCondition()
{
	while(true)
	{
		if(!isConjunction())
			return false;
			
		if(tokens.front().compare("||")==0)
		{
			tokens.pop();
			continue;
		}
		else
			break;
	}
	
	return true;
}

bool Parser::isSelection(string tok)
{
	//checking to see what tok is.
	if(tok.compare("select") != 0) return false;
	//if it is pop off and check for (
	tokens.pop();
	//the next token should be a parenthesis. 
	if(tokens.front() != "(") return false;
	else // it is open
	{
		tokens.pop(); //get rid of (
		if(!isCondition()) return false; //if this doesn't pass return false
		if(tokens.front() != ")") return false; //there should be a panrenthesis
		else
		{
			tokens.pop(); //get rid of )
			if(!isAtomicExpression()) return false;
			else return true; //return true if we passed all these things
		}
	}
}

bool Parser::isProjection(string tok)
{
	return true;
}
bool Parser::isRenaming(string tok)
{
	return true;
}
bool Parser::isSetUnion()
{
	return true;
}
bool Parser::isSetDifference()
{
	return true;
}
bool Parser::isCrossProduct()
{
	return true;
}



bool Parser::parse_CREATE()
{
	if(tokens.front().compare("TABLE") != 0)
		return false;
	tokens.pop();
	
	
	if(!isIdentifier(tokens.front()))
		return false;
	tokens.pop();
	
	if(!isTypedAttributeList())
		return false;
	tokens.pop();	
	
	if(tokens.front().compare("PRIMARY") != 0)
		return false;
	tokens.pop();
	
	if(tokens.front().compare("KEY") != 0)
		return false;	
	tokens.pop();
	

	if(!isAttributeList())
		return false;
	tokens.pop();
	
	if(tokens.front().compare(";") != 0)
		return false;	
	tokens.pop();
	
	return true;
}

bool Parser::parse_UPDATE()
{

		if(!isIdentifier(tokens.front()))		 {	return false;   }	 //relation name
			tokens.pop();
		if(tokens.front().compare("SET") != 0)	 {	return false; 	}	 //"SET"
			tokens.pop();
			
	//------------- This will update Attribute name(s)--------------------//
	
		while(true)
		{
			if(!isIdentifier(tokens.front()))		 {  return false;   }	 //Attribute name 
				tokens.pop();
			if (tokens.front().compare("=") != 0)	 {  return false;   }	 //"="
				tokens.pop();
			if (!isIdentifier(tokens.front()))		 {  return false;	}    //literal 
				tokens.pop();
				
			if(tokens.front().compare(",") == 0)
			{
				tokens.pop();
				continue;
			}
			else
				break;
		}
	//--------------------------------------------------------------------//
	
		if(tokens.front().compare("WHERE") != 0) {	return false;	}    //WHERE
			tokens.pop();
	
		if(!isCondition())
			return false;
			
		if(tokens.front().compare(";") != 0)
			return false;	
		tokens.pop();
		

		return true;		
}

bool Parser::parse_INSERT()
{

	return true;
}

bool Parser::parse_SHOW() //SHOW atomic-expr
{
		//cout << tokens.front() << endl;
		//tokens.pop();
		//cout << "here" << endl;
		
		if(isAtomicExpression())
		{
			//cout << "SHOW - parsed correctly" << endl;
			return true;
		}
		else
		{
			//cout << "SHOW - error in syntax " << endl;
			return false;
		}

	return true;
}

bool Parser::parse_OPEN() //OPEN relation-name
{
		//tokens.pop(); -- This pop eliminates the token after OPEN
		//cout << tokens.front() << endl;
		string z; //z is the string before the ';'
		for (int i = 0; i < tokens.front().size()-1; ++i){
			z += tokens.front().at(i);
		}
		//cout << "z:" << z << endl;
		if(isIdentifier(z))
		{
			//cout << "OPEN - parsed correctly" << endl;
			return true;
		}
		else
		{
			//cout << "OPEN - error in syntax " << endl; 
			return false;
		}
		
	return true;
}

bool Parser::parse_SAVE() //SAVE relation-name
{
	/*
	if(tokens.front().compare("SAVE") == 0)
	{
		tokens.pop();
		cout << "here" << endl;
		if(isIdentifier(tokens.front()))
		{
			cout << "Parsed correctly" << endl;
			return true;
		}
	}
	else{cout << "error in syntax, should be 'SAVE' " << endl; return false;}
	*/
	//return true;
		
		string z;  //z is the string before the ';'
		for (int i = 0; i < tokens.front().size()-1; ++i){
			z += tokens.front().at(i);
		}
	   //	cout << "z:" << z << endl;
		if(isIdentifier(z))
		{
			//cout << "SAVE - parsed correctly" << endl;
			return true;
		}
		else
		{
			//cout << "SAVE - error in syntax " << endl; 
			return false;
		}
		
	return true;
}
bool Parser::parse_CLOSE(){ //CLOSE relation-name
		string z;  //z is the string before the ';'
		for (int i = 0; i < tokens.front().size()-1; ++i){
			z += tokens.front().at(i);
		}
	   //	cout << "z:" << z << endl;
		if(isIdentifier(z))
		{
			//cout << "CLOSE - parsed correctly" << endl;
			return true;
		}
		else
		{
			//cout << "CLOSE - error in syntax " << endl; 
			return false;
		}
		
	return true;
}
bool Parser::parse_DELETE() //DELETE FROM relation-name WHERE condition
{
	
	
	
		//cout << "here" << endl;
			if(tokens.front().compare("FROM") != 0) { return false; }
				tokens.pop();
			
			
			if(!isIdentifier(tokens.front())) { return false; }
				tokens.pop();
			
			if(tokens.front().compare("WHERE") != 0) { return false; }
				tokens.pop();
				
	
			if (!isIdentifier(tokens.front()))		 {  return false;   }    //Conditon: operand 1
				tokens.pop();
	
			if(!isOP())								 {  return false;   }    //operator
				tokens.pop();
	
			string z;
			for (int i = 0; i < tokens.front().size()-1; ++i){
				z += tokens.front().at(i);
			}
			if(!isIdentifier(z))		 {  return false;  	}    //operand 2
				tokens.pop();
					
					/*
					else{cout << "error in syntax, should be a condition" << endl; return false;}
				}
				else{cout << "error in syntax, should be 'WHERE' " << endl; return false;}
			}
			else{cout << "error in syntax, should be a relation-name" << endl; return false;}
		}
		else {cout << "error in syntax, should be 'FROM' " << endl; return false;}
	*/
	
	
	return true;

}



bool Parser::parse_SELECT()
{ 
	/*
		if(isExp)
	
	
	*/	
	return true; 
}

bool Parser::parse_PROJECT()
{ 
	
	return true; 
}

bool Parser::parse_RENAME()
{ 
	
	return true; 
} 

bool Parser::parse_SET_UNION()
{ 
/*	if(isAtomicExpression(tokens.front()))
	{
		tokens.pop();
		if(isAtomicExpression(tokens.front()))
		{
			//add the functions
			return true;
		}
		else{cout << "not two atomic-expressions" << endl; return false;}
	}
	else{cout << "not two atomic-expressions" << endl; return false;}*/
	
	return true; 
}

bool Parser::parse_SET_DIFFERENCE()
{ 
/*	if(isAtomicExpression(tokens.front()))
	{
		tokens.pop();
		if(isAtomicExpression(tokens.front())
		{
			//subtract the functions
			return true;
		}
		else{cout << "not two atomic-expressions" << endl; return false;}
	}
	else{cout << "not two atomic-expressions" << endl; return false;}*/

	return true; 
}

bool Parser::parse_CROSS_PRODUCT()
{ 
	/*if(isAtomicExpression(tokens.front()))
	{
		tokens.pop();
		if(isAtomicExpression(tokens.front()))
		{
			//multiply the functions
			return true;
		}
		else{cout << "not two atomic-expressions" << endl; return false;}
	}
	else{cout << "not two atomic-expressions" << endl; return false;}*/

	return true; 
}



