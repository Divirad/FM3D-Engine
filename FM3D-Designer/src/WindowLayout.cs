using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DevComponents.WpfDock;
using System.Windows.Controls;
using System.ComponentModel;
using System.Windows;

namespace FM3D_Designer.src
{

    public class WindowLayout : DockWindow
    {
        [Bindable(true)]
        [Category("Appearance")]
        [DefaultValue(false)]
        public bool IsMainLayout { get; set; }
        public static string start_path { get; set; }
        private DockSite docksite; 

        public MainWindow mainWindow { get; private set; }
        protected void Initialize(MainWindow inMainWindow, DockSite docksite)
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

            if(IsMainLayout)
            {
                this.CanFloat = false;
                this.CloseButtonVisibility = System.Windows.Visibility.Hidden;
                this.CanClose = false;
            }

            this.docksite = docksite;
        }
    }
}
