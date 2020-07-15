using System.Windows;
using Encapsulate;

namespace ProjectP
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            new EncapsPasting(1);
            InitializeComponent();
        }
    }
}