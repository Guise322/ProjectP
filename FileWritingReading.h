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
    int cntOfWords = 0;
    string writenText = "";
    string takenText = "";

public:
    static int amountOfWords;
    static int cnt;
    static vector<string> word;

    void writeToFile()
    {   
        ofstream fileOf("text.txt", ios::in | ios::trunc);
        //fileOf.open("text.txt");

        if (fileOf.is_open())
        {
            cout << "Write some text below" << endl;
            getline(cin, writenText);
            fileOf << writenText;
            fileOf.close();
        }
        else
            cout << "File could not open";
    }
    void readFromFile()
    {
        ifstream fileIf("text.txt",ios::out);
        //fileIf.open("text.txt");

        if (fileIf.is_open())
        {            
            //....getline() and ....get() these functions don't had worked, because of that, prefere next method
            while (!fileIf.eof())
            {
                if ((cnt) == word.size())
                {
                    word.resize(cnt + 10);
                }
                getline(fileIf, word[cnt], ' ');
                cnt++;
            }

            cout << "Words:" << endl;

            for (int i = 0; i < cnt; i++)
            {
                transform(word[i].begin(), word[i].end(), word[i].begin(), ::tolower);
                cout << word[i] << endl;
            }
            fileIf.close();
        }
        else
            cout << "File could not open" << endl;
    }
};