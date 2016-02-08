//-------Parser

#include "Parser.h"


Parser::Parser(string in)
{
	input = in;
	parse();
	
	string firstToken = tokens.front();
	tokens.pop();
	if(firstToken.compare("CREATE") == 0)
	{
		parsedCorrect = parse_CREATE();
	}
	else if(firstToken.compare("UPDATE") == 0)
	{
		parsedCorrect = parse_UPDATE();
	}
	else if(firstToken.compare("INSERT") == 0)
	{
		parsedCorrect = parse_INSERT();
	}
	else if(firstToken.compare("SHOW") == 0)
	{
		parsedCorrect = parse_SHOW();
	}
	else if(firstToken.compare("OPEN") == 0)
	{
		parsedCorrect = parse_OPEN();
	}
	else if(firstToken.compare("SAVE") == 0)
	{
		parsedCorrect = parse_SAVE();
	}
	else if(firstToken.compare("DELETE") == 0)
	{
		parsedCorrect = parse_DELETE();
	}
	
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

bool Parser::isType(string type)
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


bool Parser::isAtomicExpression()
{
	/*
	if(tokens.front().compare("selection") == 0){return true;}
	else if(tokens.front().compare("projection") == 0){return true;}
	else if(tokens.front().compare("renaming") == 0){return true;}
	else if(tokens.front().compare("union") == 0){return true;}
	else if(tokens.front().compare("difference") == 0){return true;}
	else if(tokens.front().compare("product") == 0){return true;}
	else{ cout << "error in syntax, not an atomic expression" << endl; return false;}
	*/
	return true;
}


bool Parser::isOP()
{
	/*
	if(tokens.front().compare("==")==0){return true;}
	else if(tokens.front().compare("!=")==0){return true;}	
	else if(tokens.front().compare("<")==0){return true;}
	else if(tokens.front().compare(">") ==0){return true;}
	else if(tokens.front().compare("<=")==0){return true;}
	else if(tokens.front().compare(">=")==0){return true;}
	else{ cout << "error in syntax, not an OP" << endl; return false;}
	*/
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
	//update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition 
	
	/*
	
	if (tokens.front().compare("UPDATE") == 0){
		tokens.pop();
		
		if(isIdentifier(tokens.front()){		//See if next Token is a Relation Name
			tokens.pop()
			
			if(tokens.front().compare("SET") == 0){
				tokens.pop();
				
				if(isIdentifier(tokens.front())){ //Undefined function
					tokens.pop();
					
					if(tokens.front().compare("WHERE") == 0){
						tokens.pop();
						
						if(isOP(){					//Undefined function
							return true;
						}
					}
				}
			}
		}
	}else { return false; }
	
	*/
}

bool Parser::parse_INSERT()
{

	return true;
}

bool Parser::parse_SHOW()
{
	
	/*if(tokens.front().compare("SHOW") == 0)
	{
		tokens.pop();
		if(isAtomicExpression(tokens.front()))
		{
			return true;
		}
	}
	else{return false;}
	*/
	return true;
}

bool Parser::parse_OPEN()
{
	/*
	if(tokens.front().compare("OPEN") == 0)
	{
		tokens.pop();
		if(isIdentifier(tokens.front()))
		{
			return true;
		}
	}
	else{return false;}
	*/
	return true;
}

bool Parser::parse_SAVE()
{
	/*
	if(tokens.front().compare("SAVE") == 0)
	{
		tokens.pop();
		if(isIdentifier(tokens.front()))
		{
			return true;
		}
	}
	else{return false;}
	*/
	return true;
}

bool Parser::parse_DELETE()
{
	/*
	if(tokens.front().compare("DELETE") == 0)
	{
		tokens.pop();
		if(tokens.front().compare("FROM") == 0)
		{
			tokens.pop();
			if(isIdentifier(tokens.front()) == 0)
			{
				if(tokens.front().compare("WHERE" == 0))
				{
					tokens.pop();
					if(tokens.front().compare(**whatever condtion function is) == 0)
					{
						return true;
					}
					else{cout << "error in syntax, should be a condition" << endl;}
				}
				else{ << "error in syntax, should be 'WHERE' " << endl;}
			}
			else{cout << "error in syntax, should be a relation-name" << endl;}
		}
		else {cout << "error in syntax, should be 'FROM' " << endl;}
	}
	*/
	
	return true;
}


/*	

	bool Parser::parse_SELECT(){ 
		
		return true; 
	}
	
	bool Parser::parse_PROJECT(){ 
		
		return true; 
	}

	bool Parser::parse_RENAME(){ 
		
		return true; 
	} 
	
	bool Parser::parse_SET_UNION(){ 
		
		return true; 
	}

	bool Parser::parse_SET_DIFFERENCE(){ 
	
		return true; 
	}

	bool Parser::parse_CROSS_PRODUCT(){ 
	
		return true; 
	}

*/

