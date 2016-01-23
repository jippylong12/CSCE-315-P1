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
	stringstream input;
public:
	Parser(stringstream);

};

Parser::Parser(stringstream in)
{
	input = in;
}



int main()
{
	cout << "Staring \n" << endl;
	cout << "Enter command: \n" << endl;
	string mainInput;
	stringstream command;
	while (true)
	{
		cin >> mainInput;
		command << mainInput;
		Parser mainParser(command)
	}
}