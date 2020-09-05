using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Models.TextProcessor
{
    class TextProcessor
    {
        public string[] TextProcessing(TextInstance textFromUser)
        {
            return textProcessing(textFromUser);
        }
        string[] textProcessing(TextInstance textFromUser)
        {
            textFromUser.Words = textFromUser.Text.Split(' ');
            WordProcessor wordProcessor = new WordProcessor();
            List<string> s = wordProcessor.WordProcessing(textFromUser);
            return s.ToArray();
        }
    }
}
