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
        private Action<object> action;
        private Func<object, bool> condition;

        public Command(Action<object> action, Func<object, bool> condition)
        {
            if (action == null) throw new ArgumentNullException("action");
            this.action = action;
            this.condition = condition;
        }

        public override bool CanExecute(object parameter)
        {
            return (condition != null) ? condition(parameter) : true;
        }
        public override void Execute(object parameter)
        {
            action(parameter);
        }
    }
}
