#include <iostream>
#include "FileWriteRead.h"
#include "FileSearch.h"


using namespace std;
int FileWriteRead::cnt = 0;
string FileWriteRead::word[5000] = {};

int main()
{
    
    int valueForEnter;

    FileWriteRead fileWriteRead;

    fileWriteRead.writeToFile();

    fileWriteRead.readFromFile();
    
    FileSearch fileSearch;

    fileSearch.fileSearch();

    //Statement for breaking the execution
    cout << "Press any kay and then Enter for exit";
    cin >> valueForEnter;

    return 0;
}