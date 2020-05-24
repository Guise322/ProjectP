#pragma once
#include <cctype>
#include "FileWritingReading.h"

class FileSearching:
    FileWritingReading
{
private:
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
        
        vector<string> wordsToCompare = wordsVector;

        for (string i : wordsToCompare)
        {
            transform(i.begin(), i.end(), i.begin(), ::tolower);
        }

        string comparedWord = "";

        for (int i = 0; i < cnt; i++)
        {
            if (wordForSearching.compare(wordsToCompare[i]) == 0)
            {
                amountOfWords++;
                comparedWord = to_string(i + 1);
            }
            if ((i == (cnt - 1)) || (i == 0))
            {
                wordNumber += comparedWord + ".";
            }
            else
            {
                wordNumber += comparedWord + ", ";
            }
        }
        if (wordNumber == "")
        {
            cout << "The word number is 0" << endl;
        }
        else
        {
            cout << "The word number is " << wordNumber << endl;
        }
        cout << "Amount of words is " << amountOfWords << endl;
        wordsToCompare.clear();
	}
};