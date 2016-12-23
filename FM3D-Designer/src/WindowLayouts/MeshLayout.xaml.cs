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
using DevComponents.WpfDock;

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for MeshLayout.xaml
    /// </summary>
    public partial class MeshLayout : WindowLayout
    {
        public MeshLayout()
        {
            InitializeComponent();

            this.Header = "Mesh";
            this.Initialize(mainWindow, this.dockSite);

            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new DocumentWindows.MeshViewPort(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Right);
            DockSite.SetDockSize(splitPanel, 150);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }
    }
}
