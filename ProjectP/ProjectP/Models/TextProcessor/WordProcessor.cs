using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Models.TextProcessor
{
	class WordProcessor
	{ 
		public TextInstance WordProcessing(TextInstance textFromUser)
        {
			return wordProcessing(textFromUser);
        }
        public TextInstance WritingText(TextInstance textFromUser)
        {
            return writingOfText(textFromUser);
        }
		TextInstance wordProcessing(TextInstance textFromUser)
		{
/*------------------The Working Of The WordProcessing Function----------------------------

The function takes a vector containing words has been taken in the file 'text.txt'. It
returns a modified vector to a caller.

Words, readed in the file, are being writed with not-letter characters into a vector.
Thus the not-letter characters is destroying the words replacement process. For removing
these characters in the words, the function was created.

The vector that is being given to the function named textFromUser.Words. textFromUser.Words is readed
word by word by a for loop, then the function partitions each word down into characters
and compares a character with the character assigned above. Then writes the word's
character to the word named oldWord. If the function gets one of the assigned characters,
it then creats new vector with two more vector elements and writes remaining characters to
newWord. The got character is contained in the variable searchedLetter. oldWord, newWord,
and searchedLetter are being written into wordsSet. The function checks next word then.

The function returns the vector, after checking all the words, containing one word/symbol
within one vector's element.*/


			string word = "";
			string oldWord = "";
			string newWord = "";
			char wordLetter = ' ';
			char searchedLetter = ' ';
			string[] wordsSet = new string[1];
			bool check = false;

			for (int i = 0; i < textFromUser.Words.Length; i++)
			{
				word = textFromUser.Words[i];
                if (word != null)
                {
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
                }
				if (check)
				{
					bool emptyWord = false;

					Array.Resize(ref wordsSet, wordsSet.Length + 2);

                    for (int l = 0; l < wordsSet.Length; l++)
                    {
                        if (l < i)
                        {
                            wordsSet[l] = textFromUser.Words[l];
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
                                    wordsSet[l + 1] = searchedLetter.ToString();
                                    l++;
                                    emptyWord = true;
                                }
                                else
                                {
                                    if (oldWord == null)
                                    {
                                        wordsSet[l] = searchedLetter.ToString();
                                        wordsSet[l + 1] = newWord;
                                    }
                                    else
                                    {
                                        wordsSet[l] = oldWord;
                                        wordsSet[l + 1] += searchedLetter;
                                        Array.Resize(ref wordsSet, wordsSet.Length + 2);
                                        if (newWord != null)
                                        {
                                            wordsSet[l + 2] = newWord;

                                            //This statement is bacause the loop has empty steps 
                                            //due to writing 2 new words into wordsSet
                                            l += 2;
                                        }
                                    }
                                    emptyWord = false;
                                }
                            }
                        }
                        else if (l > i + 1)
                        {
                            if (emptyWord)
                            {
                                if (l <= textFromUser.Words.Length)
                                {
                                    wordsSet[l] = textFromUser.Words[l - 1];
                                }
                            }
                        }
                    }
					check = false;
                    textFromUser.Words = wordsSet;
				}
				oldWord = null;
				newWord = null;
			}
            //wordProcessSize = wordsSet.size();
            textFromUser.Words = textFromUser.Words.TakeWhile(p => p != null).ToArray();
            return textFromUser;
		}

        enum LetterCondition
        {
            tab, newString, spaceAndUpper, spaceBefore, spaceAfter,
            noSpace, idle, number, nospace, upper, error
        };

        enum SurroundingCondition
        {
            surroundingProcess, surroundingIdle
        };

        LetterCondition letterState = LetterCondition.idle;
        SurroundingCondition surroundState = SurroundingCondition.surroundingIdle;
        /*This function returns values defined by table 1:
                                                                    table 1
       |---|---------------------------------------------------------------|
       | N |                         Defining                              |
       |---|---------------------------------------------------------------|
       | 0 |  A written letter is not a defined symbol                     |
       |---|---------------------------------------------------------------|
       | 1 |  A written letter is a tabulation symbol                      |
       |---|---------------------------------------------------------------|
       | 2 |  A written letter is a new string symbol                      |
       |---|---------------------------------------------------------------|
       | 3 |  The written letter is the symbol needs to write a space after|
       |   | that and transform first letter of the next word to the upper |
       |   | letter                                                        |
       |---|---------------------------------------------------------------|
       | 4 |  The written letter is empty                                  |
       |---|---------------------------------------------------------------|
       | 5 |  The written letter is the symbol doesn't need to write       |
       |   | a space after that but needs to write before                  |
       |---|---------------------------------------------------------------|
       | 6 |  The written letter is the symbol needs to write a space after| 
       |   | that but doesn't need to write before                         |
       |---|---------------------------------------------------------------|
       | 7 |  The written letter is the symbol that 'surrounds' words      |
       |   | (e.g. ", ', (, *).                                            |
       |---|---------------------------------------------------------------|
       | 8 |  The written letter is the symbol that doesn't to write       |
       |   | a space after and before that                                 |
       |---|---------------------------------------------------------------|
       | 9 |  The written letter is a number                               |
       |---|---------------------------------------------------------------|
       | 10|  The written letter is a white spice                          |
       |---|---------------------------------------------------------------|
       */
        int checkingWord(char wordLetter)
        {
            //See ASCII code for encoding an integer number to a char symbol

            if (wordLetter == 9)
                return 1;

            if (wordLetter == 10)
                return 2;

            else if (wordLetter == 33 || wordLetter == 46 || wordLetter == 63)
                return 3;

            else if (wordLetter == 0)
                return 4;

            else if (wordLetter == 35 || wordLetter == 36)
                return 5;

            else if (wordLetter == 37 || wordLetter == 58 || wordLetter == 59 || wordLetter == 44)
                return 6;

            else if (wordLetter == 34 || (wordLetter > 38 && wordLetter < 42) || wordLetter == 91
                || wordLetter == 93 || wordLetter == 123 || wordLetter == 125)
                return 7;

            else if (wordLetter == 45 || wordLetter == 47 || wordLetter == 92 || wordLetter == 95
                || wordLetter == 96)
                return 8;

            else if (wordLetter > 48 && wordLetter < 58)
                return 9;

            else if (wordLetter == 32)
                return 10;

            else
                return 0;
        }
        TextInstance writingOfText (TextInstance textFromUser)
        {
            string writenText = "";

            //ofstream fileOf;

            //fileOf.open("text.txt");

            //if (fileOf.is_open())
            //{
            //cout << "Write some text below" << endl;
            //getline(cin, writenText);

            for (int i = 0; i < textFromUser.Words.Length; i++)
            {
                int result = checkingWord(textFromUser.Words[i].First());
                //----------------------------------The Pipeline Of Writing Words Into A File---------------------------------------------
                if (i == 0)
                {
                    writenText += textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                    if (result == 9)
                        letterState = LetterCondition.number;
                    else
                        letterState = LetterCondition.idle;
                }
                else if (result == 0)
                {
                    if (letterState == LetterCondition.spaceAndUpper)
                    {
                        writenText += ' ' + textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                        letterState = LetterCondition.idle;
                    }
                    else if (letterState == LetterCondition.newString || letterState == LetterCondition.upper)
                    {
                        writenText += textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                        letterState = LetterCondition.idle;
                    }
                    else if (letterState == LetterCondition.tab || letterState == LetterCondition.idle)
                    {
                        writenText += textFromUser.Words[i];
                        letterState = LetterCondition.idle;
                    }
                    else if (letterState == LetterCondition.spaceAfter || letterState == LetterCondition.number)
                    {
                        writenText += ' ' + textFromUser.Words[i];
                        letterState = LetterCondition.idle;
                    }
                    else if (letterState == LetterCondition.spaceBefore || letterState == LetterCondition.noSpace)
                    {
                        writenText += textFromUser.Words[i];
                        letterState = LetterCondition.idle;
                    }
                }
                //This if statement and next similar statements don't have the condition 'check == edle'
                //because 'check' may have the condition 'dot' after a dot being in text for instance 
                else if (result == 1)
                {
                    writenText += textFromUser.Words[i];
                    letterState = LetterCondition.tab;
                }
                else if (result == 2)
                {
                    writenText += textFromUser.Words[i];
                    letterState = LetterCondition.newString;
                }
                else if (result == 3)
                {
                    writenText += textFromUser.Words[i];
                    letterState = LetterCondition.spaceAndUpper;
                }
                else if (result == 4)
                {
                    continue;
                }
                else if (result == 5)
                {
                    writenText += ' ' + textFromUser.Words[i];
                    letterState = LetterCondition.spaceBefore;
                }
                else if (result == 6)
                {
                    writenText += textFromUser.Words[i];
                    letterState = LetterCondition.spaceAfter;
                }
                else if (result == 7)
                {
                    if (surroundState == SurroundingCondition.surroundingIdle && (letterState == LetterCondition.tab || letterState == LetterCondition.newString))
                    {
                        writenText += textFromUser.Words[i];
                        letterState = LetterCondition.spaceBefore;
                        surroundState = SurroundingCondition.surroundingProcess;
                    }
                    else if (surroundState == SurroundingCondition.surroundingIdle)
                    {
                        writenText += textFromUser.Words[i];
                        letterState = LetterCondition.spaceBefore;
                        surroundState = SurroundingCondition.surroundingProcess;
                    }
                    else
                    {
                        writenText += textFromUser.Words[i];
                        letterState = LetterCondition.spaceAfter;
                        surroundState = SurroundingCondition.surroundingIdle;
                    }
                }
                else if (result == 8)
                {
                    writenText += textFromUser.Words[i];
                    letterState = LetterCondition.noSpace;
                }
                else if (result == 9)
                {
                    /*if (letterState != number && letterState != spaceBefore && surroundState != surroundingProcess)
                    {
                        writenText += ' ' + textFromUser.Words[i];
                        letterState = number;
                    }
                    else
                    {*/
                    writenText += textFromUser.Words[i];
                    letterState = LetterCondition.number;
                    //}
                }
                else if (result == 10) //&& (letterState == idle || letterState == spaceAfter || letterState == number ||
                                       //letterState == spaceAndUpper || letterState == upper))
                {
                    writenText += textFromUser.Words[i];
                    surroundState = SurroundingCondition.surroundingIdle;
                    if (letterState == LetterCondition.spaceAfter)
                        letterState = LetterCondition.spaceBefore;
                    else if (letterState == LetterCondition.idle || letterState == LetterCondition.noSpace)
                        letterState = LetterCondition.spaceBefore;
                    else if (letterState == LetterCondition.spaceAndUpper)
                        letterState = LetterCondition.upper;
                    else //if (letterState == spaceBefore || letterState == number)
                        letterState = LetterCondition.idle;
                }
                else
                {
                    letterState = LetterCondition.error;
                }
            }
            //-------------------------------------the end of The Pipeline-----------------------------------------------------------
            /*CoInitialize(NULL);

            PastWrapper::IPastWrapperInterfacePtr iPastInterfacePtr;

            HRESULT hRes = iPastInterfacePtr.CreateInstance(PastWrapper::CLSID_PastWrapper);

            BSTR str;
            BSTR nameOfProcessEXE = SysAllocString(L"Notepad");
            BSTR nameOfNeededFile = SysAllocString(L"text");

            const char* cstr = writenText.c_str();
            BSTR dataToPast = _com_util::ConvertStringToBSTR(cstr);
            iPastInterfacePtr->PastWr(nameOfProcessEXE, nameOfNeededFile, dataToPast);

            CoUninitialize();*/
            //fileOf << writenText;
            //fileOf.close();
            //}
            //else
            //cout << "The file can't be opened";
            textFromUser.Text = writenText;
            return textFromUser;
        }
    }
}
