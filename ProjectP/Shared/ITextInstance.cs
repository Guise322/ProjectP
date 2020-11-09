namespace ProjectP.Shared
{
 public interface ITextInstance
    {
        string Text {get; set;}
        string ProcessedText { get; set; }
        string[] Words { get; set; }
        string[] PreviousWords { get; set; }
    }   
}