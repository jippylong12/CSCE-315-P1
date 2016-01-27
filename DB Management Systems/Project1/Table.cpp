#include "Table.h"
using namespace std;
//insert into the table at a specific element location
   int rowLength = 2;   //Default test values
   int columnLength = 10;
   vector< vector<string> > table;  //@table is a 2-D Vetor.
int insert_cmd(std::string s, int row, int col)
{
   
    if (row < rowLength && col < columnLength)
    {
        table[row][col] = s;
        return 0;
    }
    else
    {
        return 1;
    }
}

int delete_cmd(std::string s, int row)
{
    if (row < rowLength)
    {
        table.erase(table.begin() + row);
        return 0;
    }
    else
    {
        return 1;
    }
}