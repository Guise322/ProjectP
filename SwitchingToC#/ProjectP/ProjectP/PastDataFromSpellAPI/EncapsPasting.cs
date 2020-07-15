using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ProjectP.PastDataFromSpellAPI;

namespace Encapsulate
{
    class EncapsPasting
    {
        public EncapsPasting(int mode)
        {
            ModesOfWork modeOfWork = new ModesOfWork();
            modeOfWork.ModeNumber = mode;
            List<string> FileParameters = new List<string>(3) { "Notepad", "text", modeOfWork.WorkResult};
            new PastingIntoFile(FileParameters[0], FileParameters[1], FileParameters[2]);
        }
    }
}
