using ProjectP.Shared;

namespace ProjectP.Server.Models.TextProcessor
{
    public interface ITextProcessor
    {
        void textProcessing(ITextInstance textInstance);        
    }
}