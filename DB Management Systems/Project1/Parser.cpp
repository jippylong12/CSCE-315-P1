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



char * Parser::parse()
{
	
	char * cstring = new char [input.length()+1];
	strcpy(cstring, input.c_str());
	char * parsing = strtok(cstring," ");
	while(parsing!=0)
	{
		tokens.push(parsing);
		cout<<parsing <<endl;
		parsing = strtok(NULL," ");
	}
	return cstring;
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
	
	if(firstToken.compare("select") == 0)
	{
		cout << 1 << endl;
		tokens.pop();
		
	}
	else if(firstToken.compare("PROJECT") == 0)
	{
		tokens.pop();
		
	}
	else if(firstToken.compare("RENAME") == 0)
	{
		tokens.pop();
	
	}
	else if(firstToken.compare("SET_UNION") == 0)
	{
		tokens.pop();
		
	}
	else if(firstToken.compare("SET_DIFFERENCE") == 0)
	{
		tokens.pop();
		
	}
	else if(firstToken.compare("CROSS_PRODUCT") == 0)
	{
		tokens.pop();
		
	}
	
	else{
		cout << "Error: Query not found!" << endl;
		return false;
	}
	
	return true;
}

bool Parser::isQuery()
{
	string firstToken = tokens.front();
	if(!isIdentifier(firstToken))
		return false;
	tokens.pop();
	
	firstToken = tokens.front();
	if(firstToken.compare("<-"))
		return false;
	tokens.pop();
	
	if(!isExpression())
		return false;
	
	return true;
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
		return true;
	else if(type.compare(0,7,"VARCHAR") == 0)
	{
		if(type.compare(7,1,"(") == 0 && type.compare(type.length()-1,1,")") == 0)
		{
			for(int i = 8; i < type.length()-1; i++)
			{
				if('0' <= type[i] && type[i] <= '9'){}
				else {return false;}
			}
				
		}
		return true;
	}
	
	return false;
		
}

bool Parser::isAttributeList()
{
	if(tokens.front()[0] != '(')
		return false;
	
	while(true)
	{
		string t =  tokens.front();
		char first = t[0];
		char last = t[t.length()-1];
		
		if(first == '(')
		{
			t = t.erase(0,1);
		}
			

		if(last == ';')
		{
			t = t.erase(t.length()-1,1);
			last = t[t.length()-1];
			
			if(last == ')')
			{
				
				t = t.erase(t.length()-1,1);
				if(!isIdentifier(t))
					return false;
					
				break;
			}
			else
				return false;
		}
		else if(last == ',')
		{
			t = t.erase(t.length()-1,1);
			if(!isIdentifier(t))
					return false;
					
			tokens.pop();
		}
	}


	return true;
}
	


bool Parser::isTypedAttributeList()
{
	if(tokens.front()[0] != '(')
		return false;
	while(true)
	{
		string t =  tokens.front();
		char first = t[0];
		char last = t[t.length()-1];
		
		if(first == '(')
		{
			if(!isIdentifier(t.erase(0,1)))
				return false;
		}
		else if(!isIdentifier(tokens.front()))
				return false;
		
		tokens.pop();
		
		
		t =  tokens.front();
		first = t[0];
		last = t[t.length()-1];

		if(!isType(t.erase(t.length()-1,1)))
			return false;
				
		if(last == ',')
		{	
			tokens.pop();
			continue;
		}
		else if(last == ')')
		{
			break;
		}
		else
			return false;
	}
	
	return true;
}


bool Parser::isAtomicExpression() //checks if selection, projection, renaming, union, difference, or product
{								  //Can also be a relation name (which is an identifier)
				
	// if(tokens.front().compare("selection") == 0){return true;}
	// else if(tokens.front().compare("projection") == 0){return true;}
	// else if(tokens.front().compare("renaming") == 0){return true;}
	// else if(tokens.front().compare("union") == 0){return true;}
	// else if(tokens.front().compare("difference") == 0){return true;}
	// else if(tokens.front().compare("product") == 0){return true;}
	// else if(isIdentifier(tokens.front()) || tokens.front()[tokens.front().size()-1] == ';'){ return true; }
	// else{ 
	// 	cout << "error in syntax, not an atomic expression" << endl; 
	// 	return false;
	// }
	
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


bool Parser::isComparison() 
{
	string operand = tokens.front();
	if(!isIdentifier(operand))
		return false;
	tokens.pop();
	
	string op = tokens.front();
	if(!isOP(op))
		return false;
	tokens.pop();
		
	
	return true;
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
	
	return true;
}

bool Parser::parse_UPDATE()
{
	 //update-cmd 
	 //cout << "front: " << tokens.front() << endl;

		if(!isIdentifier(tokens.front()))		 {	return false;   }	 //relation name
			tokens.pop();
		if(tokens.front().compare("SET") != 0)	 {	return false; 	}	 //"SET"
			tokens.pop();
			
	//------------- Needs to be able to do multiple of these--------------//
	//------------- This will update Attribute name(s)--------------------//
		if(!isIdentifier(tokens.front()))		 {  return false;   }	 //Attribute name 
			tokens.pop();
		if (tokens.front().compare("=") != 0)	 {  return false;   }	 //"="
			tokens.pop();
		if (!isIdentifier(tokens.front()))		 {  return false;	}    //literal 
			tokens.pop();
	//--------------------------------------------------------------------//
	
		if(tokens.front().compare("WHERE") != 0) {	return false;	}    //WHERE
			tokens.pop();
		if (!isIdentifier(tokens.front()))		 {  return false;   }    //Conditon: operand 1
			tokens.pop();
		if(!isOP())								 {  return false;   }    //operator
			tokens.pop();
		if(!isIdentifier(tokens.front()) && tokens.front()[tokens.front().size()-1] != ';' )		 {  return false;  	}    //operand 2
			tokens.pop();
		
	//::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
		
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



