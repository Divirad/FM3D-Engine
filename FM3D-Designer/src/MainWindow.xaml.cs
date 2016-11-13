using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

using DevComponents.WPF.Metro;
using DevComponents.WpfDock;

///Hauptnamespace
/**
 * Alle Klassen liegen in diesem Namepsace
 * um eine Komplikation mit einer Klasse
 * aus einer externen Bibliothek zu verhindern
 */
namespace FM3D_Designer.src
{
    ///Hauptfenster
    /**
     * Ein fast leeres Fenster, enthält nur ein DockSite-Control,
     * um das docken von WindowLayouts zu ermöglichen. Der modern
     * aussehende style wird durch die Basisklasse MetroAppWindow
     * hervorgerufen.
     */
    public partial class MainWindow : MetroAppWindow
    {
        public MainWindow()
        {
            Themes.DarkTheme.SetTheme();
            
            InitializeComponent();
            if (this.dockSite != null) this.dockSite.AfterDocked += AfterDocked;
            AttachNewWindowLayout(new WindowLayouts.StartLayout(this));
        }
        public void AttachNewWindowLayout(WindowLayout layout, bool isSelected = false)
        {
            this.dockingGroup.Items.Add(layout);
            layout.IsSelected = isSelected;
            this.dockingGroup.UpdateVisibility();
        }

        public void ClearAttachedWindows()
        {
            this.dockingGroup.Items.Clear();
            this.dockingGroup.UpdateVisibility();
        }

        void AfterDocked(object sender, DockRoutedEventArgs e)
        {
            if (e.DockControl is DockWindow)
            {
                DockWindow dg = e.DockControl as DockWindow;
                if (dg.IsFloating)
                {
                    Window w = Window.GetWindow(dg);
                    MetroUI.SetTheme(w, MetroUI.GetTheme(this));
                }
            }
        }

    }

}
