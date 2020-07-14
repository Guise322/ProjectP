using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ProjectP.PastDataFromSpellAPI
{
    class PastingIntoFile
    {
        [DllImport("user32.dll")]

        public static extern int SetForegroundWindow(IntPtr hWnd);

        public PastingIntoFile(string nameOfProcessEXE, string nameOfNeededFile, string dataToPast)
        {
            Process[] processes;
            string[] processesNameList = new string[12];
            int[] processesIDList = new int[12];
            string procName = nameOfProcessEXE;
            int cnt = 0;

            processes = Process.GetProcessesByName(procName);
            foreach (Process proc in processes)
            {
                processesNameList[cnt] = proc.MainWindowTitle;
                processesIDList[cnt++] = proc.Id;
            }

            string nameOfFileToCompare = nameOfNeededFile;
            int cntOfProcesses = 0;

            APIWork.SpellerAPI spellerAPI = new APIWork.SpellerAPI();

            string[] spellerAnswer = spellerAPI.XmlYandexAPIWordsVariants(dataToPast);

            int j = 1;
            for (int i = 0; i < spellerAnswer.Length; i += 2)
            {
                if (!spellerAnswer[i].Equals("###"))
                {
                    dataToPast = dataToPast.Replace(spellerAnswer[i], spellerAnswer[j]);
                    j += 2;
                }
                else
                    break;
            }

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
            string[] processesNameListP;
            int[] processesIDListP;
            //string procNameP = "Console";
            int cntP = 0;

            processesP = Process.GetProcesses();

            processesNameListP = new string[processesP.Length];
            processesIDListP = new int[processesP.Length];

            foreach (Process proc in processesP)
            {
                processesNameListP[cntP] = proc.MainWindowTitle;
                processesIDListP[cntP++] = proc.Id;
            }

            string nameOfFileToCompareP = "ProjectP";
            int cntOfProcessesP = 0;

            foreach (string name in processesNameListP)
            {
                if (name != null)
                {
                    if (name.Contains(nameOfFileToCompareP))
                    {
                        int procIDP = processesIDListP[cntOfProcessesP];
                        Process tempProcP = Process.GetProcessById(procIDP);
                        SetForegroundWindow(tempProcP.MainWindowHandle);
                    }
                }
                cntOfProcessesP++;
            }
        }
    }
}
