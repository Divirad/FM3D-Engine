using System;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using DevComponents.WpfDock;
using System.ComponentModel;
using System.Windows.Shapes;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Navigation;
using System.Collections.Generic;
using System.Windows.Media.Imaging;
using System.Windows.Controls.Primitives;
using System.Collections.ObjectModel;

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for MainLayout.xaml
    /// </summary>
    public partial class MainLayout : WindowLayout
    {
        public static MainLayout Instance { get; set; }
        public ToolWindows.FileBrowser.View fileBrowser { get; private set; }
        public MainLayout(MainWindow mainWindow)
        {
            if (Instance != null)
                throw new InvalidOperationException("You cant create multiple objects of MainLayout!");
            Instance = this;

            InitializeComponent();
            
            this.Header = "Main Page";
            this.Initialize(mainWindow, this.dockSite);
            { 
                startFileBrowser();
                startTextEditor();
            }
        }

        private void startFileBrowser()
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(this.fileBrowser = new ToolWindows.FileBrowser.View(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Right);
            DockSite.SetDockSize(splitPanel, 200);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }

        ~MainLayout()
        {
            Instance = null;
        }

        private void ToolBar_Loaded(object sender, RoutedEventArgs e)
        {
            ToolBar toolBar = sender as ToolBar;
            var overflowGrid = toolBar.Template.FindName("OverflowButton", toolBar) as ButtonBase;
            if (overflowGrid != null)
            {
                overflowGrid.Background = toolBar.Background;
            }
        }

        public void OpenFileBrowser(object sender, RoutedEventArgs e)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(this.fileBrowser = new ToolWindows.FileBrowser.View(this));

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

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.Instance.visualStudio.Start("FM3D_PIPE_EPIC_GAME_5754656", Project.CurrentProject._Directory + "/C++/GameProject.sln");
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Project.AddClass();
            //   MainWindow.Instance.visualStudio.AddClass("EpicFishClasselein", "Main.cpp");
        }

        private void ExportProj(object sender, RoutedEventArgs e)
        {
            //Project.SaveProject();
        }
    }
}
