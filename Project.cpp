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

#import "C:\Users\userHP\Desktop\Code\ProjectP\DLLs\CSharp\PastWrapper\PastWrapper\bin\Debug\PastWrapper.tlb" named_guids raw_interfaces_only

using namespace std;

int FileWritingReading::cnt = 0;
int FileWritingReading::amountOfWords = 0;
//int FileWritingReading::dictVectorSize = 0;
//int WordProcessing::wordProcessSize = 0;

//Below variable being for breaking the code execution
char valueForEnter;

vector<string> FileWritingReading::wordsVector;

enum mode
{
    writingForm, searchingInFile, writingTitleForm, writingIntoDict, idle
};
enum mode currMode;

int main()
{
    string ch = "";
    bool repeatProcess = false;

    do
    {
        ch = "";

        cout << endl << "Choose a mode of work:" << endl << "1 - Replacing particular words in the text;"
            << endl << "2 - Searching a word from the file;" << endl << "3 - Writing the title list form;"
            << endl << "4 - Writing a memorandum template;" << endl << "5 - Write a word into the dictionary" << endl << endl;
        cout << "Write the number of the mode: ";

        char choosenMode;

        cin >> choosenMode;

        if (choosenMode == '1')
        {
            currMode = mode::writingForm;

            FileWritingReading fileWritingReading;
            FileReplacement fileReplacement;

            cout << endl << "Write into the text.txt file" << endl;

            bool repeatOne = false;

                //for (int i = 0; i < 60; i++)
            do
            {
                FileWritingReading::cnt = 0;
                FileWritingReading::wordsVector.resize(0);
                this_thread::sleep_for(1s);

                fileWritingReading.readFromFile();

                fileReplacement.wordReplacement();

                fileWritingReading.writeToFile();

                bool repeatRP = false;

                do
                {
                    cout << endl << "Repeate the process? [y/n]" << endl << endl;
                    
                    cin >> ch;

                    if (ch == "y")
                    {
                        repeatRP = true;
                        repeatOne = false;
                    }
                    else if (ch != "n")
                    {
                        cout << endl << "Error!" << endl << endl << "Repeate the command" << endl;
                        repeatRP = false;
                        repeatOne = false;
                    }
                    else
                    {
                        repeatRP = true;
                        repeatOne = true;
                    }
                } while (!repeatRP);
            } while (!repeatOne);

            //FileSearch fileSearch;

            //fileSearch.fileSearch();
        }

        else if (choosenMode == '3')
        {
            cout << endl;

            currMode = mode::writingTitleForm;

            TitleForm titleForm;

            titleForm.writeTitleForm();
        }

        else if (choosenMode == '4')
        {
            currMode = mode::writingForm;

            TitleForm memoTemp;

            memoTemp.writingMemo();
        }

        else if (choosenMode == '5')
        {
            currMode = mode::writingIntoDict;

            FileWritingReading fileWritingReading;

            fileWritingReading.dictionaryWriting();
        }

        currMode = mode::idle;

        bool repeatCAM = false;

        //The do loop for breaking the execution
        do
        {
            cout << endl << "Chose another mode? [y/n]" << endl << endl;

            cin >> ch;

                if (ch == "y")
                {
                    repeatCAM = true;
                    repeatProcess = false;
                }
                else if (ch != "n")
                {
                    cout << endl << "Error!" << endl << endl << "Repeate the command" << endl;
                    repeatCAM = false;
                    repeatProcess = false;
                }
                else
                {
                    repeatCAM = true;
                    repeatProcess = true;
                }
        } while (!repeatCAM);
    } while (!repeatProcess);

    return 0;
}