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
    static vector<string> wordsVector;

    void writeToFile()
    {   
        writenText = "";
        ofstream fileOf("text.txt", ios::in);
        
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
            cout << "File could not opened";
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
            cout << "File could not opened" << endl;
    }
};