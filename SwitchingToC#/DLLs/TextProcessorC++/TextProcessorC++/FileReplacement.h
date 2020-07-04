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
	void wordReplacement()
	{
		//vectorToReplace.resize(dictVectorSize);
		vectorToReplace = dictionaryReading();

		for (unsigned int i = 0; i < vectorToReplace.size(); i++)
		{
			transform(vectorToReplace[i].begin(), vectorToReplace[i].end(), vectorToReplace[i].begin(), ::tolower);
		}

		vector<string> vectorToCompare = wordsVector;

		for (unsigned int i = 0; i < vectorToCompare.size(); i++)
		{
			transform(vectorToCompare[i].begin(), vectorToCompare[i].end(), vectorToCompare[i].begin(), ::tolower);
		}
		
			vector<int> wordNumbers;

		for (unsigned int i = 0; i < vectorToCompare.size(); i++)
		{
			for (unsigned int j = 1; j < vectorToReplace.size(); j += 2)
			{
				if (vectorToReplace[j].compare(vectorToCompare[i]) == 0)
				{
					vectorToCompare[i] = vectorToReplace[j - 1];
					wordNumbers.resize(wordNumbers.size() + 1);
					wordNumbers[wordNumbers.size() - 1] = i;
				}
			}
		}

		for (int i : wordNumbers)
		{
			//write checking an upper letter case and then transforming the letter of a word in vectorToCompare to the upper letter
			wordsVector[i] = vectorToCompare[i];
		}
	}
};