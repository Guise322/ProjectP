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
		public void WordProcessing(TextInstance textFromUser)
        {
			wordProcessing(textFromUser);
        }
        public void WritingOfText(TextInstance textFromUser)
        {
            writingOfText(textFromUser);
        }
        public void wordProcessing(TextInstance textFromUser)
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
            textFromUser.Words = wordsList.ToArray();
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
        void writingOfText (TextInstance textFromUser)
        {

            LetterCondition LetterState = LetterCondition.idle;
            SurroundingCondition SurroundState = SurroundingCondition.surroundingIdle;

            string writenText = "";

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
                        LetterState = LetterCondition.number;
                    else
                        LetterState = LetterCondition.idle;
                }
                else
                {
                    switch (result)
                    {
                        case 0:
                            if (LetterState == LetterCondition.spaceAndUpper)
                            {
                                writenText += ' ' + textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                                LetterState = LetterCondition.idle;
                            }
                            else if (LetterState == LetterCondition.newString || LetterState == LetterCondition.upper)
                            {
                                writenText += textFromUser.Words[i].First().ToString().ToUpper() + textFromUser.Words[i].Substring(1);
                                LetterState = LetterCondition.idle;
                            }
                            else if (LetterState == LetterCondition.tab || LetterState == LetterCondition.whiteSpace)
                            {
                                writenText += textFromUser.Words[i];
                                LetterState = LetterCondition.idle;
                            }
                            else if (LetterState == LetterCondition.spaceAfter || LetterState == LetterCondition.number || LetterState == LetterCondition.idle)
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                LetterState = LetterCondition.idle;
                            }
                            else if (LetterState == LetterCondition.spaceBefore || LetterState == LetterCondition.noSpace)
                            {
                                writenText += textFromUser.Words[i];
                                LetterState = LetterCondition.idle;
                            }
                            break;
                        case 1:
                            writenText += textFromUser.Words[i];
                            LetterState = LetterCondition.tab;
                            break;
                        case 2:
                            writenText += textFromUser.Words[i];
                            LetterState = LetterCondition.newString;
                            break;
                        case 3:
                            writenText += textFromUser.Words[i];
                            LetterState = LetterCondition.spaceAndUpper;
                            break;
                        case 4:
                            break;
                        case 5:
                            writenText += ' ' + textFromUser.Words[i];
                            LetterState = LetterCondition.spaceBefore;
                            break;
                        case 6:
                            writenText += textFromUser.Words[i];
                            LetterState = LetterCondition.spaceAfter;
                            break;
                        case 7:
                            if (SurroundState == SurroundingCondition.surroundingIdle && (LetterState == LetterCondition.tab || LetterState == LetterCondition.newString))
                            {
                                writenText += textFromUser.Words[i];
                                LetterState = LetterCondition.spaceBefore;
                                SurroundState = SurroundingCondition.surroundingProcess;
                            }
                            else if (SurroundState == SurroundingCondition.surroundingIdle)
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                LetterState = LetterCondition.spaceBefore;
                                SurroundState = SurroundingCondition.surroundingProcess;
                            }
                            else
                            {
                                writenText += textFromUser.Words[i];
                                LetterState = LetterCondition.spaceAfter;
                                SurroundState = SurroundingCondition.surroundingIdle;
                            }
                            break;
                        case 8:
                            writenText += textFromUser.Words[i];
                            LetterState = LetterCondition.noSpace;
                            break;
                        case 9:
                            /*if (LetterState != number && LetterState != spaceBefore && SurroundState != surroundingProcess)
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                LetterState = number;
                            }
                            else
                            {*/
                            if (LetterState == LetterCondition.whiteSpace || LetterState == LetterCondition.number)
                            {
                                writenText += textFromUser.Words[i];
                                LetterState = LetterCondition.number;
                            }
                            else
                            {
                                writenText += ' ' + textFromUser.Words[i];
                                LetterState = LetterCondition.number;
                            }
                            //}
                            break;
                        case 10:
                            writenText += textFromUser.Words[i];
                            SurroundState = SurroundingCondition.surroundingIdle;
                            LetterState = LetterCondition.whiteSpace;
                            //if (LetterState == LetterCondition.spaceAfter)
                            //    LetterState = LetterCondition.spaceBefore;
                            //else if (LetterState == LetterCondition.idle || LetterState == LetterCondition.noSpace)
                            //    LetterState = LetterCondition.spaceBefore;
                            //else if (LetterState == LetterCondition.spaceAndUpper)
                            //    LetterState = LetterCondition.upper;
                            //else //if (LetterState == spaceBefore || LetterState == number)
                            //    LetterState = LetterCondition.idle;
                            break;
                        default:
                            LetterState = LetterCondition.error;
                            break;
                    }
                }
            }
            //-------------------------------------the end of The Pipeline-----------------------------------------------------------
            textFromUser.ProcessedText = writenText;
        }
    }
}
