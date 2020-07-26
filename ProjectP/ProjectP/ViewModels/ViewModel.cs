using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Navigation;
using ProjectP.Models.ImportNativeCode;

namespace ProjectP.ViewModels
{
    class ViewModel : ViewModelBase
    {
        //public ICommand ChangeNameCommand => _changeNameCommand;
        //private readonly DelegateCommand _changeNameCommand;
        string _textAreaContent;
        public string TextAreaContent
        {
            get => _textAreaContent;
            set
            {
                int mode = 1;
                //SetProperty(ref _textAreaContent, Marshal.PtrToStringAnsi(ImportNativeCode.DllCpp(value, mode)));
                SetProperty(ref _textAreaContent, Marshal.PtrToStringAnsi(ImportNativeCode.DllCpp(Marshal.StringToHGlobalAnsi(value), mode)));
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