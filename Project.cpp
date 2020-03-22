#include <iostream>
#include "FileWritingReading.h"
#include "FileSearching.h"
#include "FileReplacement.h"
#include <chrono>
#include <thread>


using namespace std;

int FileWritingReading::cnt = 0;
int FileWritingReading::amountOfWords = 0;
vector<string> FileWritingReading::wordsVector;
string choosenMode = "";
enum mode
{
    writeForm, searchInFile
};
enum mode currMode;

int main()
{
    cout << "Choose a mode of work:" << endl << "1 - Writting the form of a title list;"
        << endl << "2 - Searching a word from the file" << endl << endl;
    cout << "Write the number of the mode:";
    getline(cin, choosenMode);
    if (choosenMode == "1")
    {
        currMode = writeForm;

        FileWritingReading fileWriteRead;
        FileReplacement fileReplacement;

        while (true)
        //for (int i = 0; i < 60; i++)
        {
            FileWritingReading::cnt = 0;
            FileWritingReading::wordsVector.resize(0);
            this_thread::sleep_for(1s);

            fileWriteRead.readFromFile();

            fileReplacement.replaceWord();

            fileWriteRead.writeToFile();
        }

        int valueForEnter;

        //FileSearch fileSearch;

        //fileSearch.fileSearch();

        //Statement for breaking the execution
        cout << "Press any key and then Enter for exit";
        cin >> valueForEnter;
    }
    
    return 0;
}