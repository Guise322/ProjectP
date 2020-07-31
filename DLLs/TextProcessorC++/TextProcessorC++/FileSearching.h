#pragma once
#include <cctype>
#include "FileWriteAndRead.h"

class FileSearching:
    FileWriteAndRead
{
private:
    string wordForSearching = "";
    string resultOfsearching = "";
    string wordNumber = "";
public:

	void fileSearch()
	{
        cout << "Write a searched word" << endl;

        getline(cin, wordForSearching);


        //This statement converting upper case letters to lower case letters is occured below, because these letters don't equals to each other
        transform(wordForSearching.begin(), wordForSearching.end(), wordForSearching.begin(), ::tolower);
        
        vector<string> wordsToCompare = SplitText("fff");

        for (string i : wordsToCompare)
        {
            transform(i.begin(), i.end(), i.begin(), ::tolower);
        }

        string comparedWord = "";
        bool wordSearched = false;

        for (unsigned int i = 0; i < wordsToCompare.size(); i++)
        {
            if (wordForSearching.compare(wordsToCompare[i]) == 0)
            {
                wordSearched = true;
                amountOfWords++;
                comparedWord = to_string(i + 1);
            }
            if (((i == 0) || (amountOfWords == 1)) && wordSearched)
            {
                wordNumber += comparedWord;
                wordSearched = false;
            }
            else if ((i == 0) && wordSearched)
            {
                wordNumber += comparedWord;
                wordSearched = false;
            }
            else if ((i != 0) && wordSearched)
            {
                wordNumber += ", " + comparedWord;
                wordSearched = false;
            }
            else if (i == (wordsToCompare.size() - 1))
                wordNumber += ".";
        }
        if (wordNumber == ".")
        {
            cout << "The word number is 0." << endl;
        }
        else
        {
            cout << "The word number is " + wordNumber << endl;
        }
        cout << "Amount of words is " + to_string(amountOfWords);
        cout << '.'<< endl;
        wordsToCompare.clear();
	}
};