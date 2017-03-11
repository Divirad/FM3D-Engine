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
using MahApps.Metro.Controls.Dialogs;

namespace FM3D_Designer.src.WindowLayouts {
    /// <summary>
    /// Interaction logic for MainLayout.xaml
    /// </summary>
    public partial class MainLayout : WindowLayout {
        public static MainLayout Instance { get; set; }
        public ToolWindows.FileBrowser.View fileBrowser { get; private set; }
        public MainLayout(MainWindow mainWindow) {
			MainWindow.Instance.StatusColor = new SolidColorBrush(Color.FromRgb(255, 00, 00));
			MainWindow.Instance.tb_statbar.Text = "Please Start VisualStudio";
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

        private void startFileBrowser() {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(this.fileBrowser = new ToolWindows.FileBrowser.View(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Right);
            DockSite.SetDockSize(splitPanel, 200);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }

        ~MainLayout() {
            Instance = null;
        }

        private void ToolBar_Loaded(object sender, RoutedEventArgs e) {
            ToolBar toolBar = sender as ToolBar;
            var overflowGrid = toolBar.Template.FindName("OverflowButton", toolBar) as ButtonBase;
            if (overflowGrid != null) {
                overflowGrid.Background = toolBar.Background;
            }
        }

        public void OpenFileBrowser(object sender, RoutedEventArgs e) {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(this.fileBrowser = new ToolWindows.FileBrowser.View(this));

            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Left);
            DockSite.SetDockSize(splitPanel, 150);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }
        public void OpenTextEditor(object sender, RoutedEventArgs e) {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.TextEditor.TextEditor(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Right);
            DockSite.SetDockSize(splitPanel, 600);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }

        private void StartVSProject(object sender, RoutedEventArgs e) {
            FM3DPropertyFile fmFile = new FM3DPropertyFile();
            fmFile.Load(Project.CurrentProject.GetProjectPath() + "/Cpp/fm3d.xml");
            MainWindow.Instance.visualStudio.Start(fmFile.PipeName, Project.CurrentProject._Directory + "/Cpp/GameProject.sln");
			MainWindow.Instance.StatusColor = new SolidColorBrush(Color.FromRgb(0, 122, 204));
			MainWindow.Instance.tb_statbar.Text = "VisualStudio is Started";
		}
		
        private void StartVSNoDebug(object sender, RoutedEventArgs e) {
            MainWindow.Instance.visualStudio.Start(false);
        }

        private void Build(object sender, RoutedEventArgs e) {
            MainWindow.Instance.visualStudio.Build();
        }

        private void SaveProjectCommand(object sender, ExecutedRoutedEventArgs e) {
            Project.SaveProject(this.mainWindow);
        }
        
        private void OpenNewProject(object sender, RoutedEventArgs e) {
            MessageBox.Show("OPEN NEW PROJECT");
        }

        private void Export(object sender, ExecutedRoutedEventArgs e) {
            Project.TestEntityConvertTostr();
        }

        private void Compile(object sender, RoutedEventArgs e) {
            MainWindow.Instance.visualStudio.Build();
         
        }
        private void StartVSDebug(object sender, RoutedEventArgs e) {
         
            MainWindow.Instance.visualStudio.Start(true);
        }


		private void AboutUs(object sender, RoutedEventArgs e) {

			INFORMATIONS.aboutus();
		}

		private void Help(object sender, RoutedEventArgs e) {
			INFORMATIONS.opendoku();
		}

		private void ForkUsOnGitHub(object sender, RoutedEventArgs e) {
			INFORMATIONS.forkus();
		}

	}
}