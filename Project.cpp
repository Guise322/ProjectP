//Use this preprocessor statement because of getting the 'localtime' error in TitleForm.h
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>
#include <conio.h>
#include "FileWritingReading.h"
#include "FileSearching.h"
#include "FileReplacement.h"
#include "TitleForm.h"
#include "WordProcessing.h"

using namespace std;

int FileWritingReading::cnt = 0;
int FileWritingReading::amountOfWords = 0;
//int FileWritingReading::dictVectorSize = 0;
//int WordProcessing::wordProcessSize = 0;

//Below variable being for breaking the code execution
char valueForEnter;

vector<string> FileWritingReading::wordsVector;
string choosenMode = "";
enum mode
{
    writingForm, searchingInFile, writingTitleForm, writingIntoDict, idle
};
enum mode currMode;

int main()
{
    cout << "Choose a mode of work:" << endl << "1 - Replacing particular words in the text;"
        << endl << "2 - Searching a word from the file;" << endl << "3 - Writing the title list form;"
        <<endl<<"4 - Writing a memorandum template;"<< endl <<"5 - Write a word into the dictionary" << endl << endl;
    cout << "Write the number of the mode: ";
    
    getline(cin, choosenMode);

    if (choosenMode == "1")
    {
        currMode = mode::writingForm;

        FileWritingReading fileWritingReading;
        FileReplacement fileReplacement;

        cout << "Write into the text.txt file" << endl;

        while (true)
        //for (int i = 0; i < 60; i++)
        {
            
            FileWritingReading::cnt = 0;
            FileWritingReading::wordsVector.resize(0);
            this_thread::sleep_for(1s);

            fileWritingReading.readFromFile();

            fileReplacement.wordReplacement();

            fileWritingReading.writeToFile();
        }

        //FileSearch fileSearch;

        //fileSearch.fileSearch();
    }

    else if (choosenMode == "3")
    {
        cout << endl;

        currMode = mode::writingTitleForm;

        TitleForm titleForm;

        titleForm.writeTitleForm();
    }

    else if (choosenMode == "4")
    {
        currMode = mode::writingForm;

        TitleForm memoTemp;

        memoTemp.writingMemo();
    }

    else if (choosenMode == "5")
    {
        currMode = mode::writingIntoDict;

        FileWritingReading fileWritingReading;

        fileWritingReading.dictionaryWriting();
    }

    currMode = mode::idle;

    //Statement for breaking the execution
    do
    {
        cout << endl << "Press any key for exit";
    } while (cin.get() != '\n');

    return 0;
}