using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace FM3D_Designer.src
{
    public class Command : ICommand
    {
        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        private Action action;
        private Func<bool> condition;

        public Command(Action action, Func<bool> condition)
        {
            this.action = action;
            this.condition = condition;
        }

        public bool CanExecute(object parameter)
        {
            return condition();
        }
        public void Execute(object parameter)
        {
            action();
        }
    }
}
