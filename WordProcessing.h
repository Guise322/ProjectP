#pragma once
#include "FileWritingReading.h"

using namespace std;

class WordProcessing
{
private:

public:

	vector<string> removingEmpty(vector<string> vectorForRemoving)
	{
		for (unsigned int i = 0; i < vectorForRemoving.size(); i++)
		{
			if (vectorForRemoving[i].empty())
			{
				vectorForRemoving.resize(i);
				break;
			}
		}
		return vectorForRemoving;
	}

/*------------------The Working Of The Function WordProcess----------------------------

The function takes a vector containing words has been taken in the file 'text.txt'. It
returns a modified vector to a caller.

Words, readed in the file, are being writed with characters '\n', '\t', '.' into a vector.
Thus the process is distructing the words replacement process. For removing these characters
in the words, the function is created.

The vector that is being given to the function named wordsVector. wordsVector is readed
by a for loop word by word, then the function partitions each word down into characters
and compares a character with the character assigned above. Then writes the word's
character to the word named oldWord. If the function gets one of the assigned characters,
it then creats new vector with two more vector elements and writes remaining characters to
newWord. The got character is contained in the variable searchedLetter. oldWord, newWord,
and searchedLetter are being written into newVector. The function checks next word then.

The function returns the vector, after checking all the words, containing one word within
one vector's element.
*/

	vector<string> wordProcess(vector<string> vectorForProcessing)
	{
		string word = "";
		string oldWord = "";
		string newWord = "";
		char wordLetter = ' ';
		char searchedLetter = ' ';
		vector<string> newVector;
		bool check = false;

		for (unsigned int i = 0; i < vectorForProcessing.size(); i++)
		{
			word = vectorForProcessing[i];

			for (unsigned int j = 0; j < word.size(); j++)
			{
				wordLetter = word[j];
				
				//See ASCII code for encoding an integer to a char symbol
				if ((wordLetter < 65 || wordLetter > 90) && (wordLetter < 97 || wordLetter > 122)
					&& word.size() != 1)
				{
					searchedLetter = wordLetter;

					for (unsigned int k = j + 1; k < word.size(); k++)
					{
						newWord += word[k];
					}
					check = true;
					break;
				}

				oldWord += wordLetter;
			}
			if (check)
			{
				bool emptyWord = false;

				newVector.resize(vectorForProcessing.size() + 2);
				
				for (unsigned int l = 0; l < newVector.size(); l++)
				{
					if (l < i)
					{
						newVector[l] = vectorForProcessing[l];
					}
					else if (l == i)
					{
						if (oldWord.empty())
						{
							newVector[l] = searchedLetter;
							newVector[l + 1] = newWord;
							l++;
							emptyWord = true;
						}
						else
						{
							if (newWord.empty())
							{
								newVector[l] = oldWord;
								newVector[l + 1] = searchedLetter;
								l++;
								emptyWord = true;
							}
							else
							{
								newVector[l] = oldWord;
								newVector[l + 1] = searchedLetter;
								newVector[l + 2] = newWord;

								//This statement is bacause the loop has empty steps 
								//due to writing 2 new words into newVector
								l += 2;

								emptyWord = false;
							}
						}
					}
					else if (l > i + 1)
					{
						if (emptyWord)
						{
							if (l < vectorForProcessing.size())
							{
								newVector[l] = vectorForProcessing[l - 1];
							}
						}
						else
							newVector[l] = vectorForProcessing[l - 2];
					}
				}
				check = false;
				vectorForProcessing = newVector;
				newVector.clear();
			}
			oldWord.clear();
			newWord.clear();
		}
		//wordProcessSize = newVector.size();
		vectorForProcessing = removingEmpty(vectorForProcessing);
		return vectorForProcessing;
	}
};