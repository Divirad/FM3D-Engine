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
    public partial class MainLayout : WindowLayout
    {
        // Removed by Felix
        // You need to assign Filebrowser to a member variable
        //
        //public void startFileBrowser(Dock dock, int docksize)
        //{
        //    SplitPanel splitPanel = new SplitPanel();
        //    DockWindowGroup dg = new DockWindowGroup();
        //    dg.Items.Add(new ToolWindows.FileBrowser.View(this));
        //    splitPanel.Children.Add(dg);
        //    DockSite.SetDock(splitPanel, dock);
        //    DockSite.SetDockSize(splitPanel, docksize);
        //    this.dockSite.SplitPanels.Add(splitPanel);
        //    dg.UpdateVisibility();
        //}
        //public void startFileBrowser(Dock dock)
        //{
        //    startFileBrowser(dock, 150);
        //}
        //public void startFileBrowser()
        //{
        //    startFileBrowser(Dock.Right, 150);
        //}
        //public void startFileBrowser(object sender, RoutedEventArgs e)
        //{
        //    startFileBrowser();
        //}

        public void startTextEditor(Dock dock, int docksize, string path="")
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.TextEditor.TextEditor(this, path));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, dock);
            DockSite.SetDockSize(splitPanel, docksize);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }

        public void startTextEditor(Dock dock, string path) {
            startTextEditor(dock, 600, path);
        }

        public void startTextEditor(Dock dock)
        {
            startTextEditor(dock, 600);
        }

        public void startTextEditor(string path) {
            startTextEditor(Dock.Top, 600, path);
        }

        public void startTextEditor()
        {
            startTextEditor(Dock.Top, 600);
        }
        public void startTextEditor(object sender, RoutedEventArgs e)
        {
            startTextEditor();
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
