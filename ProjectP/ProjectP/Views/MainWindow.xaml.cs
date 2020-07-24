using System.Windows;
using ProjectP.ViewModels;

namespace ProjectP.Views
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            var viewModel = new ViewModel();
            DataContext = viewModel;
            InitializeComponent();
            TextField.Text = "Text...";
        }
    }
}