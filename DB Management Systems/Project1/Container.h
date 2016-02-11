struct Container
{
    string functionName; //what to run
    string parserTableName; //table Name
    string updateHeaderName;
	vector<string> parserKeys; //keys
	vector<string> parserHeaders;
	vector<string> parserHeaderTypes;
	vector<int> parserHeaderSizes; //for VARCHAR INTEGERS are -1  
};