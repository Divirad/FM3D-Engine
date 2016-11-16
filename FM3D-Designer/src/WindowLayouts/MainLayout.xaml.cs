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
using System.Windows.Navigation;
using System.Windows.Shapes;

using DevComponents.WpfDock;
using System.ComponentModel;

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for MainLayout.xaml
    /// </summary>
    public partial class MainLayout : WindowLayout
    {
        public MainLayout(MainWindow mainWindow)
        {
            InitializeComponent();
            
            this.Header = "Main Page";
            this.Initialize(mainWindow, this.dockSite);
            { 
                startFileBrowser();
                startTextEditor();
            }
        }
        
        public void OpenFileBrowser(object sender, RoutedEventArgs e)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.FileBrowser.View(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Left);
            DockSite.SetDockSize(splitPanel, 150);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }

        public void OpenTextEditor(object sender, RoutedEventArgs e)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.TextEditor.TextEditor(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Right);
            DockSite.SetDockSize(splitPanel,600);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }
    }
}
