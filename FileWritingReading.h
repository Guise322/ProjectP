#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <comutil.h>
#include "WordProcessing.h"

#import "D:\Code\ProjectP\DLLs\CSharp\PastWrapper\PastWrapper\bin\Debug\PastWrapper.tlb" named_guids raw_interfaces_only

using namespace std;

class FileWritingReading
{
private:
    enum letterCondition
    {
        tab, newString, spaceAndUpper, spaceBefore, spaceAfter,
        noSpace, idle, number, error
    };

    enum surroundingCondition
    {
        surroundingProcess, surroundingIdle
    };

    letterCondition letterState = idle;
    surroundingCondition surroundState = surroundingIdle;

public:
    //static int dictVectorSize;
    static int amountOfWords;
    static int cnt;
    static vector<string> wordsVector;

    /*This function returns values defined by table 1:
                                                                     table 1
        |---|---------------------------------------------------------------|
        | N |                         Defining                              |
        |---|---------------------------------------------------------------|
        | 0 |  A written letter is not a defined symbol                     |
        |---|---------------------------------------------------------------|
        | 1 |  A written letter is a tabulation symbol                      |
        |---|---------------------------------------------------------------|
        | 2 |  A written letter is a new string symbol                      |
        |---|---------------------------------------------------------------|
        | 3 |  The written letter is the symbol needs to write a space after|
        |   | that and transform first letter of the next word to the upper |
        |   | letter                                                        |
        |---|---------------------------------------------------------------|
        | 4 |  The written letter is empty                                  |
        |---|---------------------------------------------------------------|
        | 5 |  The written letter is the symbol doesn't need to write       |
        |   | a space after that but needs to write before                  |
        |---|---------------------------------------------------------------|
        | 6 |  The written letter is the symbol needs to write a space after| 
        |   | that but doesn't need to write before                         |
        |---|---------------------------------------------------------------|
        | 7 |  The written letter is the symbol that 'surrounds' words      |
        |   | (e.g. ", ', (, *).                                            |
        |---|---------------------------------------------------------------|
        | 8 |  The written letter is the symbol that doesn't to write       |
        |   | a space after and before that                                 |
        |---|---------------------------------------------------------------|
        | 9 |  The written letter is a number                               |
        |---|---------------------------------------------------------------|
        */
    int checkingWord(char wordLetter)
    {
        //See ASCII code for encoding an integer number to a char symbol

        if (wordLetter == 9)
            return 1;
        
        if (wordLetter == 10)
            return 2;

        else if (wordLetter == 33 || wordLetter == 46 || wordLetter == 63)
            return 3;

        else if (wordLetter == 0)
            return 4;

        else if (wordLetter == 35 || wordLetter == 36)
            return 5;

        else if (wordLetter == 37 || wordLetter == 58 || wordLetter == 59 || wordLetter == 44)
            return 6;

        else if (wordLetter == 34 || (wordLetter > 38 && wordLetter < 42) || wordLetter == 91
            || wordLetter == 93 || wordLetter == 123 || wordLetter == 125)
            return 7;

        else if (wordLetter == 45 || wordLetter == 47 || wordLetter == 92 || wordLetter == 95 
            || wordLetter == 96)
            return 8;

        else if (wordLetter > 48 && wordLetter < 58)
            return 9;

        else
            return 0;
    }

    void writeToFile()
    {   
        string writenText = "";

        //ofstream fileOf;
        
        //fileOf.open("text.txt");

        //if (fileOf.is_open())
        //{
            //cout << "Write some text below" << endl;
            //getline(cin, writenText);
            for (unsigned int i = 0; i < wordsVector.size(); i++)
            {
                string word = wordsVector[i];

//----------------------------------The Pipeline Of Writing Words Into A File---------------------------------------------
                if (checkingWord(word[0]) == 0 && i == 0)
                {
                    wordsVector[i][0] = toupper(wordsVector[i][0]);
                    writenText += wordsVector[i];
                }
                else if (checkingWord(word[0]) == 0 && (letterState == idle || letterState == spaceAfter))
                {
                    writenText += ' ' + wordsVector[i];
                    letterState = idle;
                }
                //This if statement and next similar statements don't have the condition 'check == edle'
                //because 'check' may have the condition 'dot' after a dot being in text for instance 
                else if (checkingWord(word[0]) == 1)
                {
                    writenText += wordsVector[i];
                    letterState = tab;
                }
                else if (checkingWord(word[0]) == 0 && letterState == tab)
                {
                    writenText += wordsVector[i];
                    letterState = idle;
                }
                else if (checkingWord(word[0]) == 2)
                {
                    writenText += wordsVector[i];
                    letterState = newString;
                }
                else if (checkingWord(word[0]) == 0 && letterState == newString)
                {
                    wordsVector[i][0] = toupper(wordsVector[i][0]);
                    writenText += wordsVector[i];
                    letterState = idle;
                }
                else if (checkingWord(word[0]) == 3)
                {
                    writenText += wordsVector[i];
                    letterState = spaceAndUpper;
                }
                else if (checkingWord(word[0]) == 0 && letterState == spaceAndUpper)
                {
                    wordsVector[i][0] = toupper(wordsVector[i][0]);
                    writenText += ' ' + wordsVector[i];
                    letterState = idle;
                }
                else if (checkingWord(word[0]) == 4)
                {
                    continue;
                }
                else if (checkingWord(word[0]) == 5)
                {
                    writenText += ' ' + wordsVector[i];
                    letterState = spaceBefore;
                }
                else if (checkingWord(word[0]) == 0 && (letterState == spaceBefore || letterState == noSpace))
                {
                    writenText += wordsVector[i];
                    letterState = idle;
                }
                else if (checkingWord(word[0]) == 6)
                {
                    writenText += wordsVector[i];
                    letterState = spaceAfter;
                }
                else if (checkingWord(word[0]) == 7)
                {
                    if (surroundState == surroundingIdle && (letterState == tab || letterState == newString))
                    {
                        writenText += wordsVector[i];
                        letterState = spaceBefore;
                        surroundState = surroundingProcess;
                    }
                    else if (surroundState == surroundingIdle)
                    {
                        writenText += ' ' + wordsVector[i];
                        letterState = spaceBefore;
                        surroundState = surroundingProcess;
                    }
                    else
                    {
                        writenText += wordsVector[i];
                        letterState = spaceAfter;
                        surroundState = surroundingIdle;
                    }
                }
                else if (checkingWord(word[0]) == 8)
                {
                    writenText += wordsVector[i];
                    letterState = noSpace;
                }
                else if (checkingWord(word[0] == 9) && letterState != number && surroundState != surroundingProcess)
                {
                    writenText += ' ' + wordsVector[i];
                    letterState = number;
                }
                else if (checkingWord(word[0] == 9) && letterState != number && surroundState == surroundingProcess)
                {
                    writenText += wordsVector[i];
                    letterState = number;
                }
                else if (checkingWord(word[0] == 9) && letterState == number)
                {
                    writenText += wordsVector[i];
                }
                else
                {
                    letterState = error;
                }
            }
//-------------------------------------the end of The Pipeline-----------------------------------------------------------
            CoInitialize(NULL);

            PastWrapper::IPastWrapperInterfacePtr iPastInterfacePtr;

            HRESULT hRes = iPastInterfacePtr.CreateInstance(PastWrapper::CLSID_PastWrapper);

            BSTR str;
            BSTR nameOfProcessEXE = SysAllocString(L"Notepad");
            BSTR nameOfNeededFile = SysAllocString(L"text");

            const char* cstr = writenText.c_str();
            BSTR dataToPast = _com_util::ConvertStringToBSTR(cstr);
            iPastInterfacePtr->PastWr(nameOfProcessEXE, nameOfNeededFile, dataToPast);

            CoUninitialize();
            //fileOf << writenText;
            //fileOf.close();
        //}
        //else
            //cout << "The file can't be opened";
    }
    vector<string> readFromFile()
    {
        ifstream fileIf;
        //fileIf.open("text.txt");

        fileIf.open("text.txt");

        if (fileIf.is_open())
        {            
            while (!fileIf.eof())
            {
                if (cnt == wordsVector.size())
                {
                    wordsVector.resize(cnt + 10);
                }
                getline(fileIf, wordsVector[cnt], ' ');

                !wordsVector[cnt].empty() ? cnt++ : cnt = cnt;
            }

            WordProcessing wordProcessing;

            wordsVector = wordProcessing.wordProcess(wordsVector);
            //cout << "Words:" << endl;
            /*for (unsigned int i = 0; i < wordsVector.size(); i++)
            {
                transform(wordsVector[i].begin(), wordsVector[i].end(), wordsVector[i].begin(), ::tolower);
            //    cout << wordsVector[i] << endl;
            }*/

            fileIf.close();
        }
        else
            cout << "The file can't be opened" << endl;
        
        return wordsVector;
    }

    vector<string> dictionaryReading()
    {
        int dictCnt = 0;
        vector<string> dictVector{ "", "" };

        ifstream fileIf("Dictionary Data.txt", ios::out);

        if (fileIf.is_open())
        {
            while (!fileIf.eof())
            {
                if (dictCnt >= dictVector.size())
                {
                    dictVector.resize(dictVector.size() + 2);
                }

                for (int i = 0; i < 2; i++)
                {
                    getline(fileIf, dictVector[dictCnt + i], (dictCnt + i) % 2 == 0 ? '\t' : '\n');
                }

                dictCnt += 2;
            }
        }
        else
            cout << "The file can't be opened";

        fileIf.close();

        //dictVectorSize = dictVector.size();

        return dictVector;
    }

    void dictionaryWriting()
    {
        string takenDictWord = "";
        string replacedWord = "";
        vector<string> dictWordsVector;

        //dictWordsVector.resize(dictVectorSize);
        dictWordsVector = dictionaryReading();

        ofstream fileOf("Dictionary Data.txt", ios::in);

        if (fileOf.is_open())
        {
            cout << endl << "Write a word to insert it into the dictionary: ";

            getline(cin, takenDictWord);

            cout << endl << "Write a word that is replaced by that word: ";

            getline(cin, replacedWord);
            
            dictWordsVector[dictWordsVector.size() - 2] = takenDictWord;
            dictWordsVector[dictWordsVector.size() - 1] = replacedWord;

            for (unsigned int i = 0; i < dictWordsVector.size(); i += 2)
            {
                fileOf << dictWordsVector[i] << '\t' << dictWordsVector[i + 1] << '\n';
            }

            cout << endl << "The words was written" << endl;
        }
        else
            cout << "The file can't be opened";

        fileOf.close();
    }
};