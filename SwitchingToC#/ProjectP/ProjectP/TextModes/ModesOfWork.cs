using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ProjectP.TextModes
{
    class ModesOfWork
    {

        public int Mode { get; set; }
        public string WorkResult
        {
            get
            {
                return Marshal.PtrToStringAnsi(Import.dllCpp(Mode));
            }
        }
        public List<string> FileToPast { get; set; }
    }
}
