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

namespace FM3D_Designer.src
{
    public class DocumentWindow : DockWindow
    {

        private DockSite docksite;

        public WindowLayout mainWindow { get; private set; }
        protected void Initialize(WindowLayout inMainWindow)
        {
            this.mainWindow = inMainWindow;

            this.CanAutoHide = false;
            this.OptionsMenu = false;
            this.CanDockAsDocument = true;
            this.CloseButtonVisibility = System.Windows.Visibility.Visible;

            this.CanDockBottom = false;
            this.CanDockLeft = false;
            this.CanDockRight = false;
            this.CanDockTop = false;
        }
    }
}
