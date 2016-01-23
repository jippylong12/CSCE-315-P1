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

};

Parser::Parser(string in)
{
	string input = in;
}



int main()
{
	cout << "Staring \n" << endl;
	cout << "Enter command: \n" << endl;
	string mainInput;
	while (true)
	{
		getline(cin, mainInput);
		Parser mainParser(mainInput);
	}
}