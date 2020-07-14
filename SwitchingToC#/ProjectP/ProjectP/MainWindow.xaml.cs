using ProjectP.TextModes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ProjectP
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            ModesOfWork modeOfWork = new ModesOfWork
            {
                Mode = 1
            };
            modeOfWork.FileToPast = new List<string>(3) { "Notepad", "text", modeOfWork.WorkResult};
            PastDataFromSpellAPI.PastingIntoFile pastingIntoFile = 
                new PastDataFromSpellAPI.PastingIntoFile(modeOfWork.FileToPast[0], modeOfWork.FileToPast[1], 
                modeOfWork.FileToPast[2]);
            InitializeComponent();
        }
    }
}
