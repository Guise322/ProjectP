/*------------------The Working Of The Function WordProcess----------------------------

The function takes a vector containing words has been taken in the file 'text.txt'. It 
returns modified vector to a caller.

Words, readed in the file, are being writed with characters '\n', '\t', '.' into a vector.
That distruct a words replacement process. For removing these characters in the words, 
the function is created.

The vector that is being given to the function named wordsVector. wordsVector is readed
by a for loop word by word, then the function partitions each word down into characters
and compares a character with the character assigned above. Then writes the word's 
character to the word named oldWord. If the function gets one of the assigned characters,
it then creats new vector with 1 more a lenght unit and writes remaining characters to 
newWord. oldWord and newWord are being written into newVector. The function checks next 
word then.

After checking all the words, the function returns 
newVector.
*/

#pragma once
#include "FileWritingReading.h"

using namespace std;

class WordProcessing
{
private:

public:
	//static int wordProcessSize;

	vector<string> wordProcess(vector<string> wordsVector)
	{
		string word = "";
		string oldWord = "";
		string newWord = "";
		char wordLetter = ' ';
		char searchedLetter = ' ';
		vector<string> newVector;
		int check = 0;

		for (unsigned int i = 0; i < wordsVector.size(); i++)
		{
			word = wordsVector[i];

			for (unsigned int j = 0; j < word.size(); j++)
			{
				wordLetter = word[j];
				
				if ((wordLetter == '\t' || wordLetter == '\n' || wordLetter == '.')
					&& word.size() != 1)
				{
					searchedLetter = wordLetter;

					for (unsigned int k = j + 1; k < word.size(); k++)
					{
						newWord += word[k];
					}
					check = 1;
					break;
				}

				oldWord += wordLetter;
			}
			if (check == 1)
			{
				newVector.resize(wordsVector.size() + 2);
				for (unsigned int l = 0; l < newVector.size(); l++)
				{
					if (l < i)
					{
						newVector[l] = wordsVector[l];
					}
					if (l == i)
					{
						if (oldWord.empty())
						{
							newVector[l] = searchedLetter;
							newVector[l + 1] = newWord;
							l++;
						}
						else
						{
							newVector[l] = oldWord;
							newVector[l + 1] = searchedLetter;
							newVector[l + 2] = newWord;

							//This statement is bacause the loop has empty steps 
							//due to writing 2 new words into newVector
							l += 2;
						}
					}
					if (l > i + 2 && l < wordsVector.size())
					{
						newVector[l] = wordsVector[l - 1];
					}
				}
				check = 0;
				wordsVector = newVector;
			}
			oldWord.clear();
			newWord.clear();
			newVector.clear();
		}
		//wordProcessSize = newVector.size();

		return wordsVector;
	}
};