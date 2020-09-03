using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Models.TextProcessor
{
	class WordProcessor
	{ 
		List<string> wordProcessing(string[] words)
		{
			/*------------------The Working Of The WordProcessing Function----------------------------

The function takes a vector containing words has been taken in the file 'text.txt'. It
returns a modified vector to a caller.

Words, readed in the file, are being writed with not-letter characters into a vector.
Thus the not-letter characters is destroying the words replacement process. For removing
these characters in the words, the function was created.

The vector that is being given to the function named wordsVector. wordsVector is readed
word by word by a for loop, then the function partitions each word down into characters
and compares a character with the character assigned above. Then writes the word's
character to the word named oldWord. If the function gets one of the assigned characters,
it then creats new vector with two more vector elements and writes remaining characters to
newWord. The got character is contained in the variable searchedLetter. oldWord, newWord,
and searchedLetter are being written into wordsSet. The function checks next word then.

The function returns the vector, after checking all the words, containing one word/symbol
within one vector's element.
*/


			string word = "";
			string oldWord = "";
			string newWord = "";
			char wordLetter = ' ';
			char searchedLetter = ' ';
			string[] wordsSet = new string[1];
			bool check = false;

			for (int i = 0; i < words.Length; i++)
			{
				word = words[i];

				for (int j = 0; j < word.Length; j++)
				{
					wordLetter = word[j];

					//See ASCII code for encoding an integer to a char symbol
					if ((wordLetter < 65 || wordLetter > 90) && (wordLetter < 97 || wordLetter > 122)
						&& word.Length != 1)
					{
						searchedLetter = wordLetter;

						for (int k = j + 1; k < word.Length; k++)
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

					Array.Resize(ref wordsSet, wordsSet.Length + 2);

					for (int l = 0; l < wordsSet.Length; l++)
					{
						if (l < i)
						{
							wordsSet[l] = words[l];
						}
						else if (l == i)
						{
							if (oldWord == "")
							{
								wordsSet[l] += searchedLetter;
								wordsSet[l + 1] = newWord;
								l++;
								emptyWord = true;
							}
							else
							{
								if (newWord == "")
								{
									wordsSet[l] = oldWord;
									wordsSet[l + 1] += searchedLetter;
									l++;
									emptyWord = true;
								}
								else
								{
									wordsSet[l] = oldWord;
									wordsSet[l + 1] += searchedLetter;
									wordsSet[l + 2] = newWord;

									//This statement is bacause the loop has empty steps 
									//due to writing 2 new words into wordsSet
									l += 2;

									emptyWord = false;
								}
							}
						}
						else if (l > i + 1)
						{
							if (emptyWord)
							{
								if (l <= words.Length)
								{
									wordsSet[l] = words[l - 1];
								}
							}
							else
								wordsSet[l] = words[l - 2];
						}
					}
					check = false;
					words = wordsSet;
					wordsSet = new string[1];
				}
				oldWord = null;
				newWord = null;
			}
			//wordProcessSize = wordsSet.size();
			List<string> wordsList = words.TakeWhile(p => p != "").ToList();

			return wordsList;
		}
	}
}
