/* _authors_
Marcus Salinas
Brian Ta
Paul Park
Clifton Sims */


#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Parser
{
	string input;
public:
	Parser(string);
	string parse();

};

Parser::Parser(string in)
{
	cout<<"The in is: " << in <<endl;
	string input = in;
	cout<<"The input is " <<input<<endl;
}

string Parser::parse()
{
	cout <<"The input is: "<< input << endl;
}



int main()
{
	cout << "Staring.." << endl;
	cout << "Enter command: " << endl;
	string mainInput;
	while (true)
	{
		getline(cin, mainInput);
		cout<<"The mainInput is "<<mainInput<< endl;
		Parser mainParser(mainInput);
		mainParser.parse();
	}
}