#pragma once

#include <iostream>
#include <thread>
#include <conio.h>
#include "FileWriteAndRead.h"
#include "FileSearching.h"
#include "FileReplace.h"
#include "WriteTitleForm.h"
#include "WordProcessing.h"

using namespace std;

int FileWriteAndRead::cnt = 0;
int FileWriteAndRead::amountOfWords = 0;
//int FileWritingReading::dictVectorSize = 0;
//int WordProcessing::wordProcessSize = 0;

vector<string> FileWriteAndRead::wordsVector;

enum mode
{
    writeText = 1, searchInFile, writeTitleForm, writeMemo,writeIntoDict, idle
};

string textProcessor(string text, int mode)
{
    //do
    //{
    //    cout << endl << "Choose a mode of the program work:" << endl << "1 - replacing particular words and spell checking in text;"
    //        << endl << "2 - searching a word in text;" << endl << "3 - writing a title list form;"
    //        << endl << "4 - writing a memorandum template;" << endl << "5 - writing a word into the dictionary" << endl << endl;
    //    cout << "Write the mode number: ";

    //    string modeNumber = "";

    //    getline(cin, modeNumber);

    if (mode == mode::writeText)
    {
        FileReplace fileReplace;
        
        return fileReplace.wordReplacement(text);
    }

        else if (mode == mode::searchInFile)
        {
            //bool repeatTwo = false;

            //do
            //{
                FileSearching fileSearching;

                fileSearching.fileSearch();

                //repeatTwo = repeatProcess.repeat("Search a word again?");

            //} while (!repeatTwo);
        }

        else if (mode == mode::writeTitleForm)
        {
            cout << endl;

            bool repeatThree = false;

            //do
            //{
                WriteTitleForm writeTitleForm;

                writeTitleForm.writeTitleForm();

                //repeatThree = repeatProcess.repeat("Write a title form again?");

            //} while (!repeatThree);
        }

        else if (mode == mode::writeMemo)
        {
            //bool repeatFour = false;

            //do
            //{
                WriteTitleForm memoTemp;

                memoTemp.writeMemo();

                //repeatFour = repeatProcess.repeat("Write a memorandum template again?");

            //} while (!repeatFour);
        }

        else if (mode == mode::writeIntoDict)
        {
            //bool repeatFive = false;

            //do
            //{
                FileWriteAndRead fileWriteAndRead;

                fileWriteAndRead.writeIntoDict();

                //repeatFive = repeatProcess.repeat("Write another word into the dictionary?");

            //} while (!repeatFive);
        }

        //else
        //{
        //    cout << "This mode does not exist!" << endl;
        //}


        //repeatChoice = repeatProcess.repeat("Choose another mode?");

    //} while (!repeatChoice);

    //return 0;
}