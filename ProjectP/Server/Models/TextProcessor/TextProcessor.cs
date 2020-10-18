using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ProjectP.Shared;

namespace ProjectP.Server.Models.TextProcessor
{
    class TextProcessor : ITextProcessor
    {
        public void textProcessing(ITextInstance textInstance)
        {
            int wordsNumber = textInstance.text.Split(' ').Length;
            char[] с = new char[] { ' '};
            if (wordsNumber != 1)
                textInstance.Words = textInstance.text.Split(с, wordsNumber - 1);
            else
                textInstance.Words = textInstance.text.Split(с);
            WordProcessor wordProcessor = new WordProcessor(textInstance);
            wordProcessor.WordProcessing();
            wordProcessor.WritingOfText();
        }
    }
}
