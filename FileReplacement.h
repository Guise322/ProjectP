#pragma once
#include <vector>
#include "FileWritingReading.h"

using namespace std;

class FileReplacement:
	public FileWritingReading
{
private:
	vector<string> vectorOfReplacement;
	string wordToReplace = "dimon";
	int numberOfWord = 0;

public:
	void replaceWord()
	{
		for (int i = 0; i < cnt; i++)
		{
			if (wordToReplace.compare(wordsVector[i]) == 0)
			{
				wordsVector[i] = "the bear";
				numberOfWord = i + 1;
				cout << numberOfWord;
			}
		}
	}
};