/*------------------The Working Of The Function WordProcess----------------------------

The function takes a vector containing words taken in the file 'text.txt'. It returns
modified vector to a caller.

Words, readed in the file, are being writed with characters '\n', '\t', '.' into a vector.
For removing these characters in the words, the function created.

The vector that is being given to the function named wordsVector. WordsVector is readed
by the for cicle word by word, then the function partitions each word down into characters
and compares a character with the character assigned above. There writes the word's 
character to the word named oldWord. If the function gets one of the assigned characters,
it then creats new vector with 1 more a lenght unit and writes remaining characters to 
newWord. oldWord and newWord is being written into newVector. The function checks next 
word then.

After checking all the words, the function writes the size of newVector and returns 
newVector.
*/

#pragma once
#include "FileWritingReading.h"

using namespace std;

class WordProcessing
{
private:

public:
	static int wordProcessSize;

	vector<string> wordProcess(vector<string> wordsVector)
	{
		string word = "";
		string oldWord = "";
		string newWord = "";
		char wordLetter = ' ';
		char comparedLetter = '\t';
		vector<string> newVector;
		int check = 0;

		for (int i = 0; i < wordsVector.size(); i++)
		{
			word = wordsVector[i];

			for (int j = 0; j < word.size(); j++)
			{
				wordLetter = word[j];
				oldWord += wordLetter;

				if (wordLetter == comparedLetter)
				{
					for (int k = j + 1; k < word.size(); k++)
					{
						newWord += word[k];
					}
					check = 1;
					break;
				}
			}
			if (!check == 0)
			{
				newVector.resize(wordsVector.size() + 1);
				for (int l = 0; l < newVector.size(); l++)
				{
					if (l < i)
					{
						newVector[l] = wordsVector[l];
					}
					if (l == i)
					{
						newVector[l] = oldWord;
						newVector[l + 1] = newWord;
					}
					if (l > i + 1)
					{
						newVector[l] = wordsVector[l - 1];
					}
				}
				check = 0;
			}
			oldWord.clear();
		}
		wordProcessSize = newVector.size();

		return newVector;
	}
};