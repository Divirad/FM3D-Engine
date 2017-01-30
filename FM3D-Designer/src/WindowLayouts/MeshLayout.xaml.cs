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
using FM3D_Designer.src.ToolWindows.Mesh;
using System.ComponentModel;

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for MeshLayout.xaml
    /// </summary>
    public partial class MeshLayout : WindowLayout, INotifyPropertyChanged
    {
        public PartsWindow partsWin { get; private set; }
        public PartsPropWindow partsPropWin { get; private set; }
        public VerticesWindow verticesWin { get; private set; }
        public DocumentWindows.MeshViewPort viewPort { get; private set; }

        public DesignerLib.Mesh mesh { get; private set; }
        public MeshLayout(DesignerLib.Mesh mesh)
        {
            this.mesh = mesh;
            InitializeComponent();

            this.Header = "Mesh";
            this.Initialize(mainWindow, this.dockSite);

            {
                SplitPanel splitPanel = new SplitPanel();
                DockWindowGroup dg = new DockWindowGroup();
                dg.Items.Add(partsWin = new PartsWindow(this.mesh));
                splitPanel.Children.Add(dg);
                DockWindowGroup dg2 = new DockWindowGroup();
                dg2.Items.Add(partsPropWin = new PartsPropWindow(this));
                splitPanel.Children.Add(dg2);
                DockSite.SetDock(splitPanel, Dock.Right);
                DockSite.SetDockSize(splitPanel, 300);
                this.dockSite.SplitPanels.Add(splitPanel);
                dg.UpdateVisibility();
                dg2.UpdateVisibility();
            }
            {
                SplitPanel splitPanel = new SplitPanel();
                DockWindowGroup dg = new DockWindowGroup();
                dg.Items.Add(verticesWin = new VerticesWindow(this));
                splitPanel.Children.Add(dg);
                DockSite.SetDock(splitPanel, Dock.Left);
                DockSite.SetDockSize(splitPanel, 200);
                this.dockSite.SplitPanels.Add(splitPanel);
                dg.UpdateVisibility();
            }
            {
                SplitPanel splitPanel = new SplitPanel();
                DockWindowGroup dg = new DockWindowGroup();
                dg.Items.Add(viewPort = new DocumentWindows.MeshViewPort(this));
                splitPanel.Children.Add(dg);
                this.dockSite.Content = splitPanel;
                dg.UpdateVisibility();
            }

            partsWin.Closed += OnPartsWinClosed;
            partsPropWin.Closed += OnPartsPropWinClosed;
            verticesWin.Closed += OnVerticesWinClosed;
            viewPort.Closed += OnViewPortClosed;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        void Menu_View_ViewPort(object sender, RoutedEventArgs e)
        {
            if (this.viewPort != null)
            {
                this.viewPort.FocusContent();
            }
            else
            {
                dockSite.FloatWindow(this.viewPort = new DocumentWindows.MeshViewPort(this));
                viewPort.Closed += OnViewPortClosed;
            }
        }

        void Menu_View_Parts(object sender, RoutedEventArgs e)
        {
            if (this.partsWin != null)
            {
                this.partsWin.FocusContent();
            }
            else
            {
                dockSite.FloatWindow(this.partsWin = new PartsWindow(this.mesh));
                partsWin.Closed += OnPartsWinClosed;
                OnPropertyChanged("partsWin");
            }
        }

        void Menu_View_PartProperties(object sender, RoutedEventArgs e)
        {
            if (this.partsPropWin != null)
            {
                this.partsPropWin.FocusContent();
            }
            else
            {
                dockSite.FloatWindow(this.partsPropWin = new PartsPropWindow(this));
                partsPropWin.Closed += OnPartsPropWinClosed;
            }
        }

        void Menu_View_Vertices(object sender, RoutedEventArgs e)
        {
            if (this.verticesWin != null)
            {
                this.verticesWin.FocusContent();
            }
            else
            {
                dockSite.FloatWindow(this.verticesWin = new VerticesWindow(this));
                verticesWin.Closed += OnVerticesWinClosed;
            }
        }

        void OnPartsWinClosed(object sender, RoutedEventArgs e)
        {
            this.partsWin = null;
            OnPropertyChanged("partsWin");
        }

        void OnPartsPropWinClosed(object sender, RoutedEventArgs e)
        {
            this.partsPropWin = null;
        }

        void OnViewPortClosed(object sender, RoutedEventArgs e)
        {
            this.viewPort = null;
        }

        void OnVerticesWinClosed(object sender, RoutedEventArgs e)
        {
            this.verticesWin = null;
        }

        private void OnPropertyChanged(string name)
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
