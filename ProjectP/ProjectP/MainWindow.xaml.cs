using System.Windows;
using ProjectP.ViewModels;

namespace ProjectP
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            var viewModel = new ViewModel();
            viewModel.FirstName = "Kevin";

            DataContext = viewModel;
            InitializeComponent();
            viewModel.FirstName = "Sue";
        }
    }
}