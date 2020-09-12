using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Models.TextProcessor
{
    class TextProcessor
    {
        public TextInstance TextProcessing(TextInstance textFromUser)
        {
            return textProcessing(textFromUser);
        }
        TextInstance textProcessing(TextInstance textFromUser)
        {
            int wordsNumber = textFromUser.Text.Split(' ').Length;
            char[] p = new char[] { ' '};
            if (wordsNumber != 1)
                textFromUser.Words = textFromUser.Text.Split(p, wordsNumber - 1);
            else
                textFromUser.Words = textFromUser.Text.Split(p);
            WordProcessor wordProcessor = new WordProcessor();
            TextInstance textWithProcessedWords = wordProcessor.WordProcessing(textFromUser);
            return wordProcessor.WritingText(textWithProcessedWords);
        }
    }
}
