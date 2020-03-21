#pragma once
#include <vector>
#include "FileWritingReading.h"

using namespace std;

class FileReplacement:
	public FileWritingReading
{
private:
	vector<string> vectorOfReplacement;
	string wordToReplace = "ddd";
	int numberOfWord = 0;

public:
	void replaceWord()
	{
		for (int i = 0; i < cnt; i++)
		{
			if (wordToReplace.compare(word[i]) == 0)
			{
				word[i] = "word";
				numberOfWord = i;
			}
		}
		cout << numberOfWord << endl;
	}
};