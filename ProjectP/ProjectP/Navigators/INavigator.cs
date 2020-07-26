using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ProjectP.ViewModels;

namespace ProjectP.Navigators
{
    public interface INavigator
    {
        ViewModel viewModel { get; set; }
    }
}
