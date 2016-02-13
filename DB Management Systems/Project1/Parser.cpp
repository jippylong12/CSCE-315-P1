//-------Parser

#include "Parser.h"
#include <typeinfo>

Parser::Parser(string in)
{
	input = in;
	parse();
	
	
}

void Parser::sendNewInput(string in)
{
	input = in;
	parse();
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
	
	//begin parsing
	if(isCommand()){}
	else if(isQuery()){}
	else
	{
		cout << "Error: Command or Query not found!" << endl;
	}
}

bool Parser::isCommand()
{
	string firstToken = tokens.front();
	
	if(firstToken.compare("CREATE") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's CREATE
		tokens.pop();
		parsedCorrect = parse_CREATE();
		if (parsedCorrect){ cout << "CREATE - valid command." << endl; } 
		else{ cout << "CREATE - invalid command." << endl; } 
	}
	else if(firstToken.compare("UPDATE") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's UPDATE
		tokens.pop();
		parsedCorrect = parse_UPDATE();
		if (parsedCorrect){ cout << "UPDATE - valid command." << endl; } 
		else{ cout << "UPDATE - invalid command." << endl; } 
	}
	else if(firstToken.compare("INSERT") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's INSERT
		tokens.pop();
		parsedCorrect = parse_INSERT();
		if (parsedCorrect){ cout << "INSERT - valid command." << endl; } 
		else{ cout << "INSERT - invalid command." << endl; } 
	}
	else if(firstToken.compare("SHOW") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's SHOW
		tokens.pop();
		parsedCorrect = parse_SHOW();
		if (parsedCorrect){ cout << "SHOW - valid command." << endl; } 
		else{ cout << "SHOW - invalid command." << endl; } 
	}
	else if(firstToken.compare("OPEN") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's OPEN
		tokens.pop();
		parsedCorrect = parse_OPEN();
		if (parsedCorrect){ cout << "OPEN - valid command." << endl; } 
		else{ cout << "OPEN - invalid command." << endl; } 
	}
	else if(firstToken.compare("SAVE") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's SAVE
		tokens.pop();
		parsedCorrect = parse_SAVE();
		if (parsedCorrect){ cout << "SAVE - valid command." << endl; } 
		else{ cout << "SAVE - invalid command." << endl; } 
	}
	else if(firstToken.compare("CLOSE") == 0)
    {   
		contain.functionName = tokens.front(); //so we know it's CLOSE
		tokens.pop();
		parsedCorrect = parse_CLOSE();
        
		if (parsedCorrect){ 
			cout << "CLOSE - valid command." << endl; 
		} 
		else{ cout << "CLOSE - invalid command." << endl; }
        
        
	}
	else if(firstToken.compare("DELETE") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's DELETE
		tokens.pop();
		parsedCorrect = parse_DELETE();
		if (parsedCorrect){ cout << "DELETE - valid command." << endl; } 
		else{ cout << "DELETE - invalid command." << endl; } 
		
    }else if(firstToken.compare("EXIT") == 0){   //so we know it's EXIT
        contain.functionName = tokens.front();
        tokens.pop();
        parsedCorrect = parse_EXIT();
        if(parsedCorrect) { cout << "EXIT - valid command." << endl; }
        else {cout << "EXIT - invalid command." << endl; }
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
		contain.functionName = tokens.front(); //so we know it's select
		tokens.pop();
		parsedCorrect = parse_SELECT();
		if (parsedCorrect){ cout << "select - valid command." << endl; } 
		else{ cout << "select - invalid command." << endl; } 	
	}
	else if(firstToken.compare("project") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's project
		tokens.pop();
		parsedCorrect = parse_PROJECT();
		if (parsedCorrect){ cout << "projection - valid command." << endl; } 
		else{ cout << "projection - invalid command." << endl; } 
		
	}
	else if(firstToken.compare("rename") == 0)
	{
		contain.functionName = tokens.front(); //so we know it's rename
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

//only used by CREATE
bool Parser::isType(string type) //checks if INTEGER or VARCHAR
{
	if(type.compare("INTEGER") == 0)
	{
		contain.parserHeaderTypes.push_back(tokens.front()); //add the type
		contain.parserHeaderSizes.push_back(-1); //-1 because int
		tokens.pop(); //remove it
		return true;
	}
	else if(type.compare("VARCHAR") == 0)
	{
		contain.parserHeaderTypes.push_back(tokens.front()); //add the type
		tokens.pop();
		type = tokens.front();
		if(type.compare("(") == 0)
		{
			tokens.pop(); //remove (
			type = tokens.front();
			
			//check if it is a digit
			for(int i = 0; i < type.length()-1; i++)
			{
				if('0' <= type[i] && type[i] <= '9'){}
				else {return false;}
			}
			
			int varcharLength = stoi(type); //make it an int
			contain.parserHeaderSizes.push_back(varcharLength); //push back value
			tokens.pop(); //we don't need it anymore
			type = tokens.front(); //check for )
			if(type.compare(")") == 0)
			{
				//remove the ) from queue
				tokens.pop();
				return true; //go back
			}
				
		}
	
	}
	 
	return false;
		
}

bool Parser::isAttributeList()
{
	while(true)
	{
		if(!isIdentifier(tokens.front())) //check if valid name
			return false;
		contain.parserKeys = tokens.front(); //get the key
		tokens.pop(); //remove that key
		
		//check if there is another key
		if(tokens.front().compare(",") == 0 )
		{
			tokens.pop(); //remove the ,
			continue; //look for the next key
		}
		else //no more keys
		{
			return true;
		}
		
	}
}
	


bool Parser::isTypedAttributeList() //only used by CREATE apparently
{
	if(tokens.front().compare("(") != 0)
		return false;
	while(true)
	{
		tokens.pop(); //remove (
		
		if(!isIdentifier(tokens.front())) //looking for Headers
			return false;
		contain.parserHeaders.push_back(tokens.front()); //pushback header name
		tokens.pop(); //remove header from queue
		

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
	if(isIdentifier(tokens.front())) //just a table
	{
		container.parserTableName = tokens.front(); //get the name for SHOW
	}
	else
	{
		if(tokens.front().compare("(") != 0) {return false;}
		tokens.pop(); //get rid of (
		
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





//------------------------------Commands and Queries--------------------------------//





bool Parser::parse_CREATE()
{
	if(tokens.front().compare("TABLE") != 0)
		return false;
	tokens.pop(); // at this point we should check relation names
	//which is isIdentifier()
	
	
	if(!isIdentifier(tokens.front()))
		return false;
	//this should be the table name
	contain.parserTableName = tokens.front(); //assing it
	tokens.pop();
	
	if(!isTypedAttributeList()) //adds type and headerSize
		return false;
	tokens.pop();	
	
	if(tokens.front().compare("PRIMARY") != 0) //get rid of that
		return false;
	tokens.pop();
	
	if(tokens.front().compare("KEY") != 0) //get rid of that
		return false;	
	tokens.pop();
	
	if(tokens.front().compare("(") != 0)
		return false;	
	tokens.pop();
	
	if(!isAttributeList()) // check this
		return false;
	
	
	
	cout << tokens.front() << endl;
	if(tokens.front().compare(")") != 0)
		return false;	
	tokens.pop(); //get rid of )
	
	if(tokens.front().compare(";") != 0)
		return false;	
	tokens.pop(); //get rid of ;
	
	return true; //done
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
		

	
	if(tokens.front().compare("(") == 0) { //Checking for literals
		
	
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
	else if(tokens.front().compare("RELATION") == 0) //Check for RELATION
	//Should be true for other INSERT command ^ we had a !=
	{	
		tokens.pop();
		
		if(!isExpression()) return false;
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
		contain.parserTableName = tokens.front(); 
		tokens.pop();
	if(tokens.front().compare(";") != 0)	 {	return false; 	}
		tokens.pop();
				
	return true;
}

bool Parser::parse_SAVE() //SAVE relation-name
{
	if (!isIdentifier(tokens.front()))		 {  return false;	}    //relation name 
	contain.parserTableName = tokens.front(); //get the table name
	tokens.pop();
	if(tokens.front().compare(";") != 0)	 {	return false; 	}
		tokens.pop();
				
	return true;
}

bool Parser::parse_CLOSE()
{ 
	if (!isIdentifier(tokens.front())){
        tokens.pop(); // we may not need this. Not a big deal either way 
        return false;                       //relation name
		
    }
    else {
        contain.parserTableName = tokens.front();  //Give the container the relation name
        tokens.pop();
    }
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
bool Parser::parse_EXIT(){
    
    if(tokens.front().compare(";") != 0) { return false; }
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



