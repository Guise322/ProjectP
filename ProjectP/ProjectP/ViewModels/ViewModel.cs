using System.ComponentModel;
using System.Runtime.InteropServices;
using ProjectP.Models.ImportNativeCode;

namespace ProjectP.ViewModels
{
    public class ViewModel : INotifyPropertyChanged
    {
        //public ICommand ChangeNameCommand => _changeNameCommand;
        //private readonly DelegateCommand _changeNameCommand;

        public event PropertyChangedEventHandler PropertyChanged;
        
        public void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        string _textAreaContent;
        public string TextAreaContent
        {
            get => _textAreaContent;
            set
            {
                int mode = 1;
                //SetProperty(ref _textAreaContent, Marshal.PtrToStringAnsi(ImportNativeCode.DllCpp(value, mode)));
                _textAreaContent = Marshal.PtrToStringAnsi(ImportNativeCode.DllCpp(Marshal.StringToHGlobalAnsi(value), mode));
                OnPropertyChanged(nameof(TextAreaContent));
            }
        }
        //public ViewModel()
        //{
        //    _changeNameCommand = new DelegateCommand(OnChangeName, CanChangeName);
        //}
        //private void OnChangeName(object commandParameter)
        //{
        //    FirstName = "Walter";
        //    _changeNameCommand.InvokeCanExecuteChanged();
        //}
        //private bool CanChangeName(object commandParameter)
        //{
        //    return FirstName != "Walter";
        //}
    }

    //public class DelegateCommand : ICommand
    //{
    //    private readonly Action<object> _executeAction;
    //    private readonly Func<object, bool> _canExecuteAction;
    //    public DelegateCommand(Action<object> executeAction, Func<object, bool> canExecuteAction)
    //    {
    //        _executeAction = executeAction;
    //        _canExecuteAction = canExecuteAction;
    //    }
    //    public void Execute(object parameter) => _executeAction(parameter);
    //    public bool CanExecute(object parameter) => _canExecuteAction?.Invoke(parameter) ?? true;
    //    public event EventHandler CanExecuteChanged;
    //    public void InvokeCanExecuteChanged() => CanExecuteChanged?.Invoke(this, EventArgs.Empty);
    //}
}