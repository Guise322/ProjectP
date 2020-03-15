#pragma once
#include <cctype>
#include "FileWriteRead.h"

class FileSearch:
    public FileWriteRead
{
private:
    int amountOfWords = 0;
    string wordForSearching = "";
    string resultOfsearching = "";
    string wordNumber = "";

public:

	void fileSearch()
	{
        cout << "Write word for searching" << endl;
        getline(cin, wordForSearching);

        //This statement converting upper case letters to lower case letters is occured below, because these letters don't equals to each other
        transform(wordForSearching.begin(), wordForSearching.end(), wordForSearching.begin(), ::tolower);

        for (int i = 0; i < cnt; i++)
        {
            if (wordForSearching.compare(word[i]) == 0)
            {
                string comparedWord = to_string(i + 1);
                if (i == (cnt - 1))
                {
                    wordNumber += comparedWord + ".";
                    amountOfWords++;
                }
                else
                {
                    wordNumber += comparedWord + ", ";
                    amountOfWords++;
                }
            }
        }
        if (wordNumber=="")
        {
            cout << "The word number is 0" << endl;
        }
        else
        {
            cout << "The word number is " << wordNumber << endl;
        }
        cout << "Amount of words is " << amountOfWords << endl;
	}
};