using System.Runtime.InteropServices;
using ProjectP;

namespace Encapsulate
{
    class ModesOfWork
    {
        public int ModeNumber { get; set; }
        public string WorkResult
        {
            get
            {
                return Marshal.PtrToStringAnsi(Import.dllCpp(ModeNumber));
            }
        }
    }
}
