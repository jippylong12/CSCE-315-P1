//-------Parser

#include "Parser.h"
#include <typeinfo>

Parser::Parser(string in)
{
	input = in;
	parse();
	
	if(isCommand()){}
	else if(isQuery()){}
	else
	{
		cout << "Error: Command or Query not found!" << endl;
	}
	
	
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
		
		return false;
	}
	
	return true;
}

bool Parser::isExpression()
{
	string firstToken = tokens.front();
	
	if(firstToken.compare("select") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_SELECT();
		if (parsedCorrect){ cout << "select - valid command." << endl; } 
		else{ cout << "select - invalid command." << endl; } 	
	}
	else if(firstToken.compare("project") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_PROJECT();
		if (parsedCorrect){ cout << "projection - valid command." << endl; } 
		else{ cout << "projection - invalid command." << endl; } 
		
	}
	else if(firstToken.compare("rename") == 0)
	{
		tokens.pop();
		parsedCorrect = parse_RENAME();
		if (parsedCorrect){ cout << "rename - valid command." << endl; } 
		else{ cout << "rename - invalid command." << endl; } 
	
	}
	else if(isAtomicExpression())
	{
			tokens.pop();
			firstToken = tokens.front();
			
			if(firstToken.compare("+") == 0)
			{
				tokens.pop();
				parsedCorrect = parse_SET_UNION();
				if (parsedCorrect){ cout << "union - valid command." << endl; } 
				else{ cout << "union - invalid command." << endl; } 
				
			}
			else if(firstToken.compare("-") == 0)
			{
				tokens.pop();
				parsedCorrect = parse_SET_DIFFERENCE();
				if (parsedCorrect){ cout << "difference - valid command." << endl; } 
				else{ cout << "difference - invalid command." << endl; } 
				
			}
			else if(firstToken.compare("*") == 0)
			{
				tokens.pop();
				parsedCorrect = parse_CROSS_PRODUCT();
				if (parsedCorrect){ cout << "cross product - valid command." << endl; } 
				else{ cout << "cross product - invalid command." << endl; } 
				
			}
			else if(firstToken.compare(";") != 0)
			{
				return false;
			
			}
	}
	
	
	else{
		cout << "Error: Expression not found!" << endl;
		return false;
	}
	return true;
}

bool Parser::isQuery()
{

	
	//check for relation name
	string firstToken = tokens.front(); //get the name
	if(!isIdentifier(firstToken)) //check 
		return false; //return false if not
	tokens.pop(); //pop it off the top
	
	firstToken = tokens.front(); //check for <-
	if(firstToken.compare("<-") != 0) //check
		return false; //return if false
	tokens.pop(); //remove if passed
		
	//check if expression
	if(!isExpression())
		return false; //return if not
	
	
	if(tokens.front().compare(";") != 0)
		return false;	
	tokens.pop();
	
	return true; //if everything passes return trues
}

bool Parser::isLiteral(string name) //literals
{
	if(name[0] == '\"' )
	{
		for(int i = 1; i < name.length()-1; i++)
		{
			if('A' <= name[i] && name[i] <= 'Z'){}
			else if('a' <= name[i] && name[i] <= 'z'){}
			else if('0' <= name[i] && name[i] <= '9'){}
			else{return false;}
		}
		if(name[name.length()-1] != '\"' ){return false;}
	}
	else
	{

		for(int i = 0; i < name.length()-1; i++)
		{
			if('0' <= name[i] && name[i] <= '9'){}
			else {return false;}
		}
	}
	
	
	
	
	
	return true;
}

bool Parser::isIdentifier(string name) //attribute name and relation name
{
	for(int i = 0; i < name.length(); i++)
	{
		if('A' <= name[i] && name[i] <= 'Z'){}
		else if('a' <= name[i] && name[i] <= 'z'){}
		else if('0' <= name[i] && name[i] <= '9'){}
		else if(name[i] == '_'){}
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

			for(int i = 0; i < type.length()-1; i++)
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
	cout << 1 << endl;
	cout << tokens.front() << endl;
	while(true)
	{
		if(!isIdentifier(tokens.front()))
			return false;
		tokens.pop();
		
		if(tokens.front().compare(",") == 0 )
		{
			tokens.pop();
			continue;
		}
		else
		{
			cout << 2 << endl;
			return true;
		}
		
	}
}
	


bool Parser::isTypedAttributeList()
{
	if(tokens.front().compare("(") != 0)
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


bool Parser::isAtomicExpression() 
{			
	if(isIdentifier(tokens.front())) { }
	else
	{
		if(tokens.front().compare("(") != 0) {return false;}
		tokens.pop();
		
		if(!isExpression()) {return false;}
		
		if(tokens.front().compare(")") != 0) {return false;}
		
	}

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

bool Parser::isComparison() 
{
	if(tokens.front()[0] == '\"')
	{
		if(!isLiteral(tokens.front()))
			return false;
		tokens.pop();
	}
	else
	{
		if(!isIdentifier(tokens.front()))
			return false;
		tokens.pop();
	}
	

	if(!isOP())
		return false;
	tokens.pop();
	
	if(tokens.front()[0] == '\"')
	{
		if(!isLiteral(tokens.front()))
			return false;
		tokens.pop();
	}
	else
	{
		if(!isIdentifier(tokens.front()))
			return false;
		tokens.pop();
	}
	
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
	
	if(tokens.front().compare("(") != 0)
		return false;	
	tokens.pop();
	
	if(!isAttributeList())
		return false;
	
	
	
	cout << tokens.front() << endl;
	if(tokens.front().compare(")") != 0)
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
			if (!isLiteral(tokens.front()))		 {  return false;	}    //literal 
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
	if(tokens.front().compare("INTO") != 0)	 {	return false; 	}	 //"INTO"
		tokens.pop();
	if(!isIdentifier(tokens.front()))		 {	return false;   }	 //relation name
		tokens.pop();
	if(tokens.front().compare("VALUES") != 0)	 {	return false; 	}	 //"VALUES"
		tokens.pop();
	if(tokens.front().compare("FROM") != 0)	 {	return false; 	}	 //"FROM"
		tokens.pop();
	
	
	if(tokens.front().compare("(") == 0)	
	{	
		tokens.pop();
		while(true)
		{
			if (!isLiteral(tokens.front()))		 {  return false;	}    //literal 
				tokens.pop();
				
			if(tokens.front().compare(",") == 0)
			{
				tokens.pop();
				continue;
			}
			else
				break;
		}
		if(tokens.front().compare(")") != 0)	 {	return false; 	}
			tokens.pop();
			
	}
	else if(tokens.front().compare("RELATION") != 0)	
	{	
		//NEED TO ADD LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			
	}
	else
		return false;
		
	if(tokens.front().compare(";") != 0)	 {	return false; 	}
			tokens.pop();
		
	return true;
}

bool Parser::parse_SHOW() //SHOW atomic-expr
{
	if((!isAtomicExpression())) { return false; }
	
	return true;
}

bool Parser::parse_OPEN() //OPEN relation-name
{
	if (!isIdentifier(tokens.front()))		 {  return false;	}    //relation name 
		tokens.pop();
	if(tokens.front().compare(";") != 0)	 {	return false; 	}
		tokens.pop();
				
	return true;
}

bool Parser::parse_SAVE() //SAVE relation-name
{
if (!isIdentifier(tokens.front()))		 {  return false;	}    //relation name 
		tokens.pop();
	if(tokens.front().compare(";") != 0)	 {	return false; 	}
		tokens.pop();
				
	return true;
}

bool Parser::parse_CLOSE()
{ 
	if (!isIdentifier(tokens.front()))		 {  return false;	}    //relation name 
		tokens.pop();
	if(tokens.front().compare(";") != 0)	 {	return false; 	}
		tokens.pop();
				
	return true;
}

bool Parser::parse_DELETE() //DELETE FROM relation-name WHERE condition
{
	
	if(tokens.front().compare("FROM") != 0) { return false; }
		tokens.pop();
	
	
	if(!isIdentifier(tokens.front())) { return false; }
		tokens.pop();
	
	if(tokens.front().compare("WHERE") != 0) { return false; }
		tokens.pop();
		
	if(!isCondition()) { return false; }

	if(tokens.front().compare(";") != 0)	 {	return false; 	}
		tokens.pop();
	
	return true;

}



bool Parser::parse_SELECT()
{ 

	if(tokens.front().compare("(") != 0)	 {	return false; 	}
		tokens.pop();
		
	if(!isCondition()) { return false; }
	
	if(tokens.front().compare(")") != 0)	 {	return false; 	}
		tokens.pop();
	
	if(!isAtomicExpression()) {	return false; }
		tokens.pop();
		
	return true; 
}

bool Parser::parse_PROJECT()
{ 
	if(tokens.front().compare("(") != 0)	 {	return false; 	}
		tokens.pop();
	
	if(!isAttributeList()) { return false; }

	if(tokens.front().compare(")") != 0)	 {	return false; 	}
		tokens.pop();
	
	if(!isAtomicExpression()) {	return false; }
		tokens.pop();
	
	return true; 
}

bool Parser::parse_RENAME()
{ 
	if(tokens.front().compare("(") != 0)	 {	return false; 	}
		tokens.pop();
	
	if(!isAttributeList()) { return false; }
	
	if(tokens.front().compare(")") != 0)	 {	return false; 	}
		tokens.pop();
	
	if(!isAtomicExpression()) {	return false; }
		tokens.pop();
	
	return true; 
} 

bool Parser::parse_SET_UNION()
{ 
	if(!isAtomicExpression()) {return false;}
	tokens.pop();
	
	return true; 
}

bool Parser::parse_SET_DIFFERENCE()
{ 
	if(!isAtomicExpression()) {return false;}
		tokens.pop();
	
	return true; 
}

bool Parser::parse_CROSS_PRODUCT()
{ 
	if(!isAtomicExpression()) {return false;}
	tokens.pop();
	
	return true; 
}



