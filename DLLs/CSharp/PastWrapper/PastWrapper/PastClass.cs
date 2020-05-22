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
            string[] processesNameList = new string[12];
            int[] processesIDList = new int[12];
            string procName = nameOfProcessEXE;
            int cnt = 0;

            processes = Process.GetProcessesByName(procName);
            foreach (Process proc in processes)
            {
                processesNameList[cnt++] = proc.MainWindowTitle;
                processesIDList[cnt] = proc.Id;
            }

            string nameOfFileToCompare = nameOfNeededFile;
            int cntOfProcesses = 0;

            dataToPast = dataToPast.Replace("\n", "\r\n");
            dataToPast = dataToPast.Replace("\t", "\r\t");

            Clipboard.SetText(dataToPast);

            foreach (string name in processesNameList)
            {
                if (name != null)
                {
                    if (name.Contains(nameOfFileToCompare))
                    {
                        int procID = processesIDList[cntOfProcesses++];
                        Process tempProc = Process.GetProcessById(procID);
                        SetForegroundWindow(tempProc.MainWindowHandle);
                        SendKeys.SendWait("^{a}");
                        SendKeys.SendWait("^{v}");
                        SendKeys.SendWait("^{s}");
                    }
                }
            }
            //Below statements get the window of ProjectP as the main window
            Process[] processesP;
            string[] processesNameListP = new string[12];
            int[] processesIDListP = new int[12];
            string procNameP = "Console";
            int cntP = 0;

            processesP = Process.GetProcessesByName(procNameP);
            foreach (Process proc in processesP)
            {
                processesNameListP[cntP++] = proc.MainWindowTitle;
                processesIDListP[cntP] = proc.Id;
            }

            string nameOfFileToCompareP = "ProjectP";
            int cntOfProcessesP = 0;

            foreach (string name in processesNameListP)
            {
                if (name != null)
                {
                    if (name.Contains(nameOfFileToCompareP))
                    {
                        int procIDP = processesIDListP[cntOfProcessesP++];
                        Process tempProcP = Process.GetProcessById(procIDP);
                        SetForegroundWindow(tempProcP.MainWindowHandle);
                    }
                }
            }
        }
    }
}
