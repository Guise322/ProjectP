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
    char ch;

    do
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

        bool repeat = false;

        while (!repeat)
        //for (int i = 0; i < 60; i++)
        {
            
            FileWritingReading::cnt = 0;
            FileWritingReading::wordsVector.resize(0);
            this_thread::sleep_for(1s);

            fileWritingReading.readFromFile();

            fileReplacement.wordReplacement();

            fileWritingReading.writeToFile();

            while (true)
            {
                cout << endl << "Repeate the process? [Y/n]\n";
         
                cin.get(ch);

                if (ch == 'y' || ch == 'Y' || ch == '\n')
                {
                    repeat = false;
                    //Use this statement for clearing a cin buffer because next cin.get() takes a char '\n'
                    cin.ignore(INT_MAX, '\n');
                    break;
                }
                /*else if (ch == '\n')
                {
                    repeat = false;
                    break;
                }*/
                else if (ch != 'n')
                {
                    cin.ignore(INT_MAX, '\n');
                    cout << "\nError!\n\nRepeate the command\n";
                    repeat = false;
                }
                else
                {
                    cin.ignore(INT_MAX, '\n');
                    repeat = true;
                    break;
                }
            }
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

    //Statements for breaking the execution
        cout << endl << "Press the Enter key to exit or any key to choose another mode\n";
        cin.get(ch);
        //cin.ignore(INT_MAX, '\n');
    } while (ch != '\n');

    return 0;
}