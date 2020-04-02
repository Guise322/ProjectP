#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class FileWritingReading
{
private:
    int dictCnt = 0;
    vector<string> dictVector{ "", "" };

public:
    static int amountOfWords;
    static int cnt;
    static vector<string> wordsVector;

    void writeToFile()
    {   
        string writenText = "";

        writenText = "";
        ofstream fileOf;
        
        fileOf.open("text.txt");

        if (fileOf.is_open())
        {
            //cout << "Write some text below" << endl;
            //getline(cin, writenText);
            for (int i = 0; i < cnt; i++)
            {
                writenText += wordsVector[i] + ' ';
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
                cnt++;
            }

            //cout << "Words:" << endl;

            for (int i = 0; i < cnt; i++)
            {
                transform(wordsVector[i].begin(), wordsVector[i].end(), wordsVector[i].begin(), ::tolower);
            //    cout << wordsVector[i] << endl;
            }

            fileIf.close();
        }
        else
            cout << "The file can't be opened" << endl;
    }

    void dictionaryWriting()
    {
        string takenDictWord = "";
        string replacedWord = "";
        
        //dictVector.resize(1);

        ifstream fileIf("Dictionari Data.txt", ios::out);
            
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

        ofstream fileOf("Dictionari Data.txt", ios::in);

        if (fileOf.is_open())
        {
            cout << endl << "Write a word to insert it into the dictionary: ";

            getline(cin, takenDictWord);

            cout << endl << "Write a word that is replaced by that word: ";

            getline(cin, replacedWord);
            
            dictVector[dictVector.size() - 2] = takenDictWord;
            dictVector[dictVector.size() - 1] = replacedWord;

            for (int i = 0; i < dictVector.size(); i += 2)
            {
                fileOf << dictVector[i] << '\t' << dictVector[i + 1] << '\n';
            }

            cout << endl << "The words was written" << endl;
        }
        else
            cout << "The file can't be opened";

        fileOf.close();
    }
};