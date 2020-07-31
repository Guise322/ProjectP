#pragma once
#include <vector>
#include <ostream>
#include "FileWriteAndRead.h"

class FileReplace
{
public:
	string wordReplacement(string text)
	{
		int numberOfWord = 0;
		vector<string> vectorToReplace;
		vector<string> wordsVector;
		FileWriteAndRead fileWriteRead;
		//vectorToReplace.resize(dictVectorSize);
		vectorToReplace = fileWriteRead.readDict();
		wordsVector = fileWriteRead.SplitText(text);

		for (auto word : vectorToReplace)
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower);
		}

		vector<string> vectorToCompare = wordsVector;

		for (auto word : vectorToCompare)
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower);
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
		string d = fileWriteRead.writeToFile(wordsVector);
		return d;
	}
};