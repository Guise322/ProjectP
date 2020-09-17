using System;
using System.Collections.Generic;
using System.Configuration;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Models.TextProcessor
{
    enum LetterCondition
    {
        tab, newString, spaceAndUpper, spaceBefore, spaceAfter,
        noSpace, idle, number, nospace, upper, whiteSpace, error
    };
    enum SurroundingCondition
    {
        surroundingProcess, surroundingIdle
    };

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
            bool wordLetterCheckedBefore = false;
            string leftWord = null;
            List<string> wordsList = new List<string>();
            foreach (var word in textFromUser.Words)
            {
                foreach (var wordLetter in word)
                {
                    if ((wordLetter < 65 || wordLetter > 90) && (wordLetter < 97 || wordLetter > 122)
                            && word.Length != 1)
                    {
                        if (wordLetterCheckedBefore)
                            wordsList[wordsList.Count - 1] += wordLetter;
                        else
                        {
                            if (leftWord != null)
                                wordsList.Add(leftWord);
                            wordsList.Add(wordLetter.ToString());
                            leftWord = null;
                            wordLetterCheckedBefore = true;
                        }
                    }
                    else
                    {
                        leftWord += wordLetter;
                        wordLetterCheckedBefore = false;
                    }
                }
                if (leftWord != null)
                {
                    wordsList.Add(leftWord);
                    leftWord = null;
                }
            }
            //for (int i = 0; i < wordsQueue.Count - 1; i++)
            //{
            //    wordsQueue[i] += ' ';
            //}
            textFromUser.Words = wordsList.ToArray();
            return textFromUser;
        }

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

            textFromUser.LetterState = LetterCondition.idle;
        textFromUser.SurroundState = SurroundingCondition.surroundingIdle;

            string writenText = "";

            //ofstream fileOf;

            //fileOf.open("text.txt");

            //if (fileOf.is_open())
            //{
            //cout << "Write some text below" << endl;
            //getline(cin, writenText);

            for (int i = 0; i < textFromUser.Words.Length; i++)
            {
                int result = checkingWord(textFromUser.Words[i].First(predicate =>
                {
                    if (predicate == 32)
                    {
                        if (i < (textFromUser.Words.Length - 1) && textFromUser.Words[i].Length != 1)
                        {
                            textFromUser.Words[i] = textFromUser.Words[i].Substring(1);
                            return false;
                        }
                        else
                            return true;
                    }
                    else if (i < (textFromUser.Words.Length - 1))
                    {
                        textFromUser.Words[i] = textFromUser.Words[i].Trim();
                        return true;
                    }
                    else
                        return true;
                }));

                //----------------------------------The Pipeline Of Writing Words Into A File---------------------------------------------
                if (i == 0)
                {
                    writenText += textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                    if (result == 9)
                        textFromUser.LetterState = LetterCondition.number;
                    else
                        textFromUser.LetterState = LetterCondition.idle;
                }
                else
                {
                    switch (result)
                    {
                        case 0:
                            if (textFromUser.LetterState == LetterCondition.spaceAndUpper)
                            {
                                writenText += ' ' + textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                                textFromUser.LetterState = LetterCondition.idle;
                            }
                            else if (textFromUser.LetterState == LetterCondition.newString || textFromUser.LetterState == LetterCondition.upper)
                            {
                                writenText += textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                                textFromUser.LetterState = LetterCondition.idle;
                            }
                            else if (textFromUser.LetterState == LetterCondition.tab || textFromUser.LetterState == LetterCondition.whiteSpace)
                            {
                                writenText += textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.idle;
                            }
                            else if (textFromUser.LetterState == LetterCondition.spaceAfter || textFromUser.LetterState == LetterCondition.number || textFromUser.LetterState == LetterCondition.idle)
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.idle;
                            }
                            else if (textFromUser.LetterState == LetterCondition.spaceBefore || textFromUser.LetterState == LetterCondition.noSpace)
                            {
                                writenText += textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.idle;
                            }
                            break;
                        case 1:
                            writenText += textFromUser.Words[i];
                            textFromUser.LetterState = LetterCondition.tab;
                            break;
                        case 2:
                            writenText += textFromUser.Words[i];
                            textFromUser.LetterState = LetterCondition.newString;
                            break;
                        case 3:
                            writenText += textFromUser.Words[i];
                            textFromUser.LetterState = LetterCondition.spaceAndUpper;
                            break;
                        case 4:
                            break;
                        case 5:
                            writenText += ' ' + textFromUser.Words[i];
                            textFromUser.LetterState = LetterCondition.spaceBefore;
                            break;
                        case 6:
                            writenText += textFromUser.Words[i];
                            textFromUser.LetterState = LetterCondition.spaceAfter;
                            break;
                        case 7:
                            if (textFromUser.SurroundState == SurroundingCondition.surroundingIdle && (textFromUser.LetterState == LetterCondition.tab || textFromUser.LetterState == LetterCondition.newString))
                            {
                                writenText += textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.spaceBefore;
                                textFromUser.SurroundState = SurroundingCondition.surroundingProcess;
                            }
                            else if (textFromUser.SurroundState == SurroundingCondition.surroundingIdle)
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.spaceBefore;
                                textFromUser.SurroundState = SurroundingCondition.surroundingProcess;
                            }
                            else
                            {
                                writenText += textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.spaceAfter;
                                textFromUser.SurroundState = SurroundingCondition.surroundingIdle;
                            }
                            break;
                        case 8:
                            writenText += textFromUser.Words[i];
                            textFromUser.LetterState = LetterCondition.noSpace;
                            break;
                        case 9:
                            /*if (textFromUser.LetterState != number && textFromUser.LetterState != spaceBefore && textFromUser.SurroundState != surroundingProcess)
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                textFromUser.LetterState = number;
                            }
                            else
                            {*/
                            if (textFromUser.LetterState == LetterCondition.whiteSpace || textFromUser.LetterState == LetterCondition.number)
                            {
                                writenText += textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.number;
                            }
                            else
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                textFromUser.LetterState = LetterCondition.number;
                            }
                            //}
                            break;
                        case 10:
                            writenText += textFromUser.Words[i];
                            textFromUser.SurroundState = SurroundingCondition.surroundingIdle;
                            textFromUser.LetterState = LetterCondition.whiteSpace;
                            //if (textFromUser.LetterState == LetterCondition.spaceAfter)
                            //    textFromUser.LetterState = LetterCondition.spaceBefore;
                            //else if (textFromUser.LetterState == LetterCondition.idle || textFromUser.LetterState == LetterCondition.noSpace)
                            //    textFromUser.LetterState = LetterCondition.spaceBefore;
                            //else if (textFromUser.LetterState == LetterCondition.spaceAndUpper)
                            //    textFromUser.LetterState = LetterCondition.upper;
                            //else //if (textFromUser.LetterState == spaceBefore || textFromUser.LetterState == number)
                            //    textFromUser.LetterState = LetterCondition.idle;
                            break;
                        default:
                            textFromUser.LetterState = LetterCondition.error;
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
