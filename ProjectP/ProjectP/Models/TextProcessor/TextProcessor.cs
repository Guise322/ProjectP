using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Models.TextProcessor
{
    class TextProcessor
    {
        public string[] TextProcessing(string text)
        {
            string[] splitedText = text.Split(' ');
            WordProcessor wordProcessor = new WordProcessor();
        }
    }
}
