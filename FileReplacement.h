#pragma once
#include <vector>
#include <ostream>
#include "FileWritingReading.h"

using namespace std;

class FileReplacement:
	public FileWritingReading
{
private:
	vector<string> vectorToReplace;
	int numberOfWord = 0;

public:
	void replaceWord()
	{
		//vectorToReplace.resize(dictVectorSize);
		vectorToReplace = dictionaryReading();

		for (unsigned int i = 0; i < vectorToReplace.size(); i++)
		{
			transform(vectorToReplace[i].begin(), vectorToReplace[i].end(), vectorToReplace[i].begin(), ::tolower);
		}

		for (unsigned int i = 0; i < wordsVector.size(); i++)
		{
			for (unsigned int j = 1; j < vectorToReplace.size(); j += 2)
			{
				if (vectorToReplace[j].compare(wordsVector[i]) == 0)
				{
					wordsVector[i] = vectorToReplace[j - 1];
					numberOfWord = i + 1;
				}
			}
		}
		cout << numberOfWord;
	}
};