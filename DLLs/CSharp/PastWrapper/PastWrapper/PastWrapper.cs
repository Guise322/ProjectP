using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace PastWrapper
{
    [Guid("68BC5EA5-B364-456F-A9B7-F20905CFD00F")]
    public interface IPastWrapperInterface
    {
        void PastWr(string nameOfProcessEXEWrap, string nameOfNeededFileWrap, string dataToPastWrap);
    }

    [ClassInterface(ClassInterfaceType.None)]
    [Guid("881E627C-F74B-4A1A-937A-00FAFFB18A69")]
    public class PastWrapper : IPastWrapperInterface
    {
        public void PastWr(string nameOfProcessEXEWrap, string nameOfNeededFileWrap ,string dataToPastWrap)
        {
            Console.Beep();
            PastClass.Past(nameOfProcessEXEWrap, nameOfNeededFileWrap, dataToPastWrap);
        }
    }
}
