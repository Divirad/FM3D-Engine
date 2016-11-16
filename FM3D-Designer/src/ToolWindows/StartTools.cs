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
    public partial class MainLayout
    {
        public void startFileBrowser(Dock dock, int docksize)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.FileBrowser.View(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, dock);
            DockSite.SetDockSize(splitPanel, docksize);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }
        public void startFileBrowser(Dock dock)
        {
            startFileBrowser(dock, 150);
        }
        public void startFileBrowser()
        {
            startFileBrowser(Dock.Right, 150);
        }

        public void startTextEditor(Dock dock, int docksize)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.TextEditor.TextEditor(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, dock);
            DockSite.SetDockSize(splitPanel, docksize);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }
        public void startTextEditor(Dock dock)
        {
            startTextEditor(dock, 600);
        }
        public void startTextEditor()
        {
            startTextEditor(Dock.Top, 600);
        }

        public void startCreateProject(Dock dock, int docksize)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.TextEditor.TextEditor(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, dock);
            DockSite.SetDockSize(splitPanel, docksize);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }
    }
}
