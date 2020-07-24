using System.Collections.Generic;
using System.Runtime.InteropServices;

using ProjectP.PastDataFromSpellAPI;

namespace ProjectP.Requests
{
    class RequestsFormer
    {
        public void PastIntoFileReq(int mode)
        {
            PastingIntoFile past = new PastingIntoFile();
            //string result = Marshal.PtrToStringAnsi(ImportNativeCode.DllCpp(mode));
            //List<string> FileParameters = new List<string>(3) { "Notepad", "text", result};
            //past.PastIntoFile(FileParameters[0], FileParameters[1], FileParameters[2]);
        }
    }
}
