using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DevComponents.WpfDock;
using System.Windows.Controls;
using System.ComponentModel;
using System.Windows;
using DevComponents.WPF.Metro;

namespace FM3D_Designer
{
    public class ToolWindow : DockWindow
    {
        public WindowLayout mainWindow { get; private set; }
        protected void Initialize(WindowLayout inMainWindow)
        {
            this.mainWindow = inMainWindow;

            this.CanAutoHide = true;
            this.OptionsMenu = true;
            this.CanDockAsDocument = false;
            this.CloseButtonVisibility = System.Windows.Visibility.Visible;

            this.CanDockBottom = true;
            this.CanDockLeft = true;
            this.CanDockRight = true;
            this.CanDockTop = true;
        }

    }
}
