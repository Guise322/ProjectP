using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ProjectP
{
    public class Import
    {
            [DllImport("TextProcessorC++.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
            public static extern IntPtr dllCpp(int mode);
    }
}
