using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace FM3D_Designer.src
{

    public abstract class CommandBase : ICommand
    {
        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public abstract bool CanExecute(object parameter);

        public abstract void Execute(object parameter);
    }

    public class Command : CommandBase
    {
        private Action action;
        private Func<bool> condition;

        public Command(Action action, Func<bool> condition)
        {
            this.action = action;
            this.condition = condition;
        }

        public override bool CanExecute(object parameter)
        {
            return condition();
        }
        public override void Execute(object parameter)
        {
            action();
        }
    }
}
