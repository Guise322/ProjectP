using ProjectP.Shared;
using ProjectP.Server.Models.TextProcessor;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;

namespace ProjectP.Server.Controllers
{
    [ApiController]
    [Route("GText")]
    public class GetTextController : ControllerBase
    {

        private ITextInstance _textInstance;
        private ITextProcessor _textProcessor;

        public GetTextController(ITextProcessor textProcessor)
        {
            _textProcessor = textProcessor;
        }
        // To run the app with a secure connection, type the --urls http://localhost:5000 command
        [HttpPost]
        public TextInstance PostTextInstance(TextInstance textInstance)
        {
            _textInstance = textInstance;
            _textInstance.text += "ff";
            return _textInstance as TextInstance;
            //_textProcessor.textProcessing(_textInstance);
        }
    }
}
