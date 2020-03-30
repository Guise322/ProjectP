#include <iostream>
#include "FileWritingReading.h"
#include "FileSearching.h"
#include "FileReplacement.h"
#include "TitleForm.h"
#include <thread>


using namespace std;

int FileWritingReading::cnt = 0;
int FileWritingReading::amountOfWords = 0;

//Below variable being for breaking the code execution
int valueForEnter;

vector<string> FileWritingReading::wordsVector;
string choosenMode = "";
enum mode
{
    writtingForm, searchingInFile, writtingTitleForm, writtingIntoDict, idle
};
enum mode currMode;

int main()
{
    cout << "Choose a mode of work:" << endl << "1 - Replacing particular words in the text;"
        << endl << "2 - Searching a word from the file;" << endl << "3 - Writting the title list form;"
        << endl <<"4 - Write a word into the dictionary" << endl << endl;
    cout << "Write the number of the mode: ";
    
    getline(cin, choosenMode);

    if (choosenMode == "1")
    {
        currMode = mode::writtingForm;

        FileWritingReading fileWrittingReading;
        FileReplacement fileReplacement;

        cout << "Write into the text.txt file" << endl;

        while (true)
        //for (int i = 0; i < 60; i++)
        {
            
            FileWritingReading::cnt = 0;
            FileWritingReading::wordsVector.resize(0);
            this_thread::sleep_for(1s);

            fileWrittingReading.readFromFile();

            fileReplacement.replaceWord();

            fileWrittingReading.writeToFile();
        }

        //FileSearch fileSearch;

        //fileSearch.fileSearch();
    }

    else if (choosenMode == "3")
    {
        cout << endl;

        currMode = mode::writtingTitleForm;

        TitleForm titleForm;

        titleForm.writeTitleForm();

        ~titleForm.writeTitleForm();
    }

    else if (choosenMode == "4")
    {
        currMode = mode::writtingIntoDict;

        FileWritingReading fileWrittingReading;

        fileWrittingReading.dictionaryWritting();
    }

    currMode = mode::idle;

    //Statement for breaking the execution
    cout << endl << "Press any key and then Enter for exit" << endl;
    cin >> valueForEnter;

    return 0;
}