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
#include "RepeatProcess.h"

#import "C:\Users\userHP\Desktop\Code\ProjectP\DLLs\CSharp\PastWrapper\PastWrapper\bin\Debug\PastWrapper.tlb" named_guids raw_interfaces_only

RepeatProcess repeatProcess;

using namespace std;

int FileWritingReading::cnt = 0;
int FileWritingReading::amountOfWords = 0;
//int FileWritingReading::dictVectorSize = 0;
//int WordProcessing::wordProcessSize = 0;

bool repeatChoice = false;

vector<string> FileWritingReading::wordsVector;

enum mode
{
    writingForm, searchingInFile, writingTitleForm, writingIntoDict, idle
};
enum mode currMode;

int main()
{
    do
    {
        cout << endl << "Choose a mode of the program work:" << endl << "1 - Replacing particular words in the text;"
            << endl << "2 - Searching a word in the file;" << endl << "3 - Writing the title list form;"
            << endl << "4 - Writing a memorandum template;" << endl << "5 - Write a word into the dictionary" << endl << endl;
        cout << "Write the number of the mode: ";

        char choosenMode = ' ';

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

                repeatOne = repeatProcess.repeat("Repeat the process?");
                
            } while (!repeatOne);

            //FileSearch fileSearch;

            //fileSearch.fileSearch();
        }

        else if (choosenMode == '2')
        {
            currMode = mode::searchingInFile;

            bool repeatTwo = false;

            do
            {
                FileSearching fileSearching;

                fileSearching.fileSearch();

                repeatTwo = repeatProcess.repeat("Search a word again?");

            } while (!repeatTwo);
        }

        else if (choosenMode == '3')
        {
            cout << endl;

            currMode = mode::writingTitleForm;

            bool repeatThree = false;

            do
            {
                TitleForm titleForm;

                titleForm.writeTitleForm();

                repeatThree = repeatProcess.repeat("Wrirte a title form again?");

            } while (!repeatThree);
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

        repeatChoice = repeatProcess.repeat("Choose another mode?");

    } while (!repeatChoice);

    return 0;
}