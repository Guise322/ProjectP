using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Models.TextProcessor
{
    class TextProcessor
    {
        public void TextProcessing(TextInstance textFromUser)
        {
            textProcessing(textFromUser);
        }
        void textProcessing(TextInstance textFromUser)
        {
            int wordsNumber = textFromUser.Text.Split(' ').Length;
            char[] с = new char[] { ' '};
            if (wordsNumber != 1)
                textFromUser.Words = textFromUser.Text.Split(с, wordsNumber - 1);
            else
                textFromUser.Words = textFromUser.Text.Split(с);
            WordProcessor wordProcessor = new WordProcessor();
            wordProcessor.WordProcessing(textFromUser);
            wordProcessor.WritingOfText(textFromUser);
        }
    }
}
