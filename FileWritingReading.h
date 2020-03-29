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
            //....getline() and ....get() these functions don't had worked, because of that, prefere next method
            while (!fileIf.eof())
            {
                if ((cnt) == wordsVector.size())
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

    void dictionaryWritting()
    {
        string takenDictWord = "";
        string replacedWord = "";

        ofstream fileOf("Dictionari Data.txt", ios::in);

        if (fileOf.is_open())
        {
            cout << "Write a word to insert it into the dictionary: ";

            getline(cin, takenDictWord);

            cout << "Write a word that is replaced by that word: ";

            getline(cin, replacedWord);

            fileOf << takenDictWord << "\t" << replacedWord << "\t";

            cout << endl << "The words was written" << endl;
        }
        else
            cout << "The file can't be opened";

        fileOf.close();
    }
};