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
            textFromUser.Words = textFromUser.Text.Split(' ');
            WordProcessor wordProcessor = new WordProcessor();
            TextInstance textWithProcessedWords = wordProcessor.WordProcessing(textFromUser);
            return wordProcessor.WritingText(textWithProcessedWords);
        }
    }
}
