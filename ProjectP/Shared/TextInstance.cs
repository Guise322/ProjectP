using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.Shared
{
    public interface ITextInstance
    {
        string Text {get; set;}
        string ProcessedText { get; set; }
        string[] Words { get; set; }
        string[] PreviousWords { get; set; }
    }
    public class TextInstance : ITextInstance
    {
        public string Text { get; set; }
        public string ProcessedText { get; set; }
        public string[] Words { get; set; }
        public string[] PreviousWords { get; set; }
    }
}
