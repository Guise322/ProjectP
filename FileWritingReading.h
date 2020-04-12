#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "WordProcessing.h"

using namespace std;

class FileWritingReading
{
private:

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
        | 0 | The written letter is not a defined symbol of the vector      |
        |---|---------------------------------------------------------------|
        | 1 | The written letter is the tabulation or next string symbol    |
        |---|---------------------------------------------------------------|
        | 2 | The written letter is the dot symbol                          |
        |---|---------------------------------------------------------------|
        | 3 | The written letter is empty                                   |
        |---|---------------------------------------------------------------|
    */       
    int checkingWord(char wordLetter)
    {
        char symbols [] = { '\t', '\n' };

        for (unsigned int i = 0; i < sizeof(symbols); i++)
        {
            if (wordLetter == symbols[i])
                return 1;

            else if (wordLetter == '.')
                return 2;

            else if (wordLetter == '\0')
                return 3;

            else
                return 0;
        }
    }

    void writeToFile()
    {   
        enum letterCondition
        {
            whiteSpace, dot, idle
        };

        string writenText = "";

        writenText = "";
        ofstream fileOf;
        
        fileOf.open("text.txt");

        if (fileOf.is_open())
        {
            letterCondition check = idle;
            //cout << "Write some text below" << endl;
            //getline(cin, writenText);
            for (unsigned int i = 0; i < wordsVector.size(); i++)
            {
                string word = wordsVector[i];

                //Take a letter because the charaters have the char type
                //Completely need only first character got from the word
                char letter = word[0];

                if (checkingWord(word[0]) != 1 && i == 0)
                {
                    wordsVector[i][0] = toupper(wordsVector[i][0]);
                    writenText += wordsVector[i];
                }
                else if (checkingWord(word[0]) == 0 && check == idle)
                {
                    writenText += ' ' + wordsVector[i];
                }
                else if (checkingWord(word[0]) == 0 && check == whiteSpace)
                {
                    writenText += wordsVector[i];
                    check = idle;
                }
                else if (checkingWord(word[0]) == 2 && check == idle)
                {
                    writenText += wordsVector[i];
                    check = dot;
                }
                else if (checkingWord(word[0]) == 2 && check == dot)
                {
                    wordsVector[i][0] = toupper(wordsVector[i][0]);
                    writenText += wordsVector[i];
                    check = idle;
                }
                else if (checkingWord(word[0]) == 3)
                {
                    continue;
                }
                else
                {
                    writenText += wordsVector[i];
                    check = whiteSpace;
                }
            }
            fileOf << writenText;
            fileOf.close();
        }
        else
            cout << "The file can't be opened";
    }
    void readFromFile()
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

            for (unsigned int i = 0; i < wordsVector.size(); i++)
            {
                transform(wordsVector[i].begin(), wordsVector[i].end(), wordsVector[i].begin(), ::tolower);
            //    cout << wordsVector[i] << endl;
            }

            fileIf.close();
        }
        else
            cout << "The file can't be opened" << endl;
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
                if (dictCnt == dictVector.size())
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