using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ProjectP.Models.ImportNativeCode
{
    public class ImportNativeCode
    {
            //[DllImport("TextProcessorC++.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
            //public static extern IntPtr DllCpp(string text, int mode);
            public string DllCpp(string text, int mode)
        {
            return text + mode;
        }
    }
}
