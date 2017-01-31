using DevComponents.WpfDock;
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

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for SkeletonLayout.xaml
    /// </summary>
    public partial class SkeletonLayout : WindowLayout
    {
        public ToolWindows.Skeleton.MeshWindow meshWindow { get; private set; }
        public SkeletonLayout()
        {
            InitializeComponent();

            {
                SplitPanel splitPanel = new SplitPanel();
                DockWindowGroup dg = new DockWindowGroup();
                dg.Items.Add(meshWindow = new ToolWindows.Skeleton.MeshWindow());
                splitPanel.Children.Add(dg);
                DockSite.SetDock(splitPanel, Dock.Left);
                DockSite.SetDockSize(splitPanel, 200);
                this.dockSite.SplitPanels.Add(splitPanel);
                dg.UpdateVisibility();
            }
        }
    }
}
