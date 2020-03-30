#pragma once
#include <vector>
#include <ostream>
#include "FileWritingReading.h"

using namespace std;

class FileReplacement:
	public FileWritingReading
{
private:
	vector<string> vectorToRelace;
	int numberOfWord = 0;

public:
	void replaceWord()
	{
		int cntOfWords = 0;
		ifstream fileIf("Dictionari Data.txt", ios::out);

		if (fileIf.is_open())
		{
			while (!fileIf.eof())
			{
				cntOfWords++;

				vectorToRelace.resize(cntOfWords);
				
				if (cntOfWords % 2 == 1)
				{
					getline(fileIf, vectorToRelace[cntOfWords - 1], '\t');
				}
				else
				{
					getline(fileIf, vectorToRelace[cntOfWords - 1], '\t');
				}
			}

			for (int i = 0; i < cntOfWords; i++)
			{
				transform(vectorToRelace[i].begin(), vectorToRelace[i].end(), vectorToRelace[i].begin(), ::tolower);
			}

			for (int i = 0; i < cnt; i++)
			{
				for (int j = 1; j < cntOfWords; j += 2)
				{
					if (vectorToRelace[j].compare(wordsVector[i]) == 0)
					{
						wordsVector[i] = vectorToRelace[j - 1];
					}
				}
				numberOfWord = i + 1;
			}
			cout << numberOfWord;
		}
		else
			cout << "The file can't be opened";
	}
};