using System;
using System.Collections.Generic;
using System.Configuration;
using System.Globalization;
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
            string leftWord = null;
            List<string> wordsQueue = new List<string>();
            foreach (var word in textFromUser.Words)
            {
                foreach (var wordLetter in word)
                {
                    if ((wordLetter < 65 || wordLetter > 90) && (wordLetter < 97 || wordLetter > 122)
                            && word.Length != 1)
                    {
                        if (leftWord != null)
                            wordsQueue.Add(leftWord);
                        wordsQueue.Add(wordLetter.ToString());
                        leftWord = null;
                    }
                    else
                        leftWord += wordLetter;
                }
                if (leftWord != null)
                    wordsQueue.Add(leftWord);
                leftWord = null;
            }
            //for (int i = 0; i < wordsQueue.Count - 1; i++)
            //{
            //    wordsQueue[i] += ' ';
            //}
            textFromUser.Words = wordsQueue.ToArray();
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
                else
                {
                  switch (result)
                    {
                        case 0:
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
                            else if (letterState == LetterCondition.tab)
                            {
                                writenText += textFromUser.Words[i];
                                letterState = LetterCondition.idle;
                            }
                            else if (letterState == LetterCondition.spaceAfter || letterState == LetterCondition.number || letterState == LetterCondition.idle)
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                letterState = LetterCondition.idle;
                            }
                            else if (letterState == LetterCondition.spaceBefore || letterState == LetterCondition.noSpace)
                            {
                                writenText += textFromUser.Words[i];
                                letterState = LetterCondition.idle;
                            }
                            break;
                        //This if statement and next similar statements don't have the condition 'check == edle'
                        //because 'check' may have the condition 'dot' after a dot being in text for instance 
                        case 1:
                            writenText += textFromUser.Words[i];
                            letterState = LetterCondition.tab;
                            break;
                        case 2:
                            writenText += textFromUser.Words[i];
                            letterState = LetterCondition.newString;
                            break;
                        case 3:
                            writenText += textFromUser.Words[i];
                            letterState = LetterCondition.spaceAndUpper;
                            break;
                        case 4:
                            break;
                        case 5:
                            writenText += ' ' + textFromUser.Words[i];
                            letterState = LetterCondition.spaceBefore;
                            break;
                        case 6:
                            writenText += textFromUser.Words[i];
                            letterState = LetterCondition.spaceAfter;
                            break;
                        case 7:
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
                            break;
                        case 8:
                            writenText += textFromUser.Words[i];
                            letterState = LetterCondition.noSpace;
                            break;
                        case 9:
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
                            break;
                        case 10:
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
                            break;
                        default:
                            letterState = LetterCondition.error;
                            break;
                    }
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
