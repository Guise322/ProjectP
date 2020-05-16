using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace PastWrapper
{
    class PastClass
    {
        [DllImport("user32.dll")]

        public static extern int SetForegroundWindow(IntPtr hWnd);

        public static void Past(string nameOfProcessEXE, string nameOfNeededFile, string dataToPast)
        {
            Process[] processes;
            string[] processesNameList = new string[7];
            int[] processesIDList = new int[6];
            string procName = nameOfProcessEXE;
            int cnt = 0;
            string newLine = Environment.NewLine;

            processes = Process.GetProcessesByName(procName);
            foreach (Process proc in processes)
            {
                processesNameList[cnt] = proc.MainWindowTitle;
                processesIDList[cnt] = proc.Id;
                cnt++;
            }

            string nameOfFileToCompare = nameOfNeededFile;
            int cntOfProcesses = 0;

            Clipboard.SetText(dataToPast);

            foreach (string name in processesNameList)
            {
                if (name != null)
                {
                    if (name.Contains(nameOfFileToCompare))
                    {
                        int procID = processesIDList[cntOfProcesses];
                        Process tempProc = Process.GetProcessById(procID);
                        SetForegroundWindow(tempProc.MainWindowHandle);
                        SendKeys.SendWait("^{a}");
                        SendKeys.SendWait("^{v}");
                        SendKeys.SendWait("^{s}");
                    }
                }
                cntOfProcesses++;
            }
        }
    }
}
