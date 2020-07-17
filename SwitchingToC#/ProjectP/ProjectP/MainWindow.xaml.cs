using System.Windows;
using ProjectP.Requests;

namespace ProjectP
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            RequestsFormer requestsFormer = new RequestsFormer();
            InitializeComponent();
            requestsFormer.PastIntoFileReq(1);
        }
    }
}