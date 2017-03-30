using DevComponents.WpfDock;
using FM3D_Designer.src.ToolWindows.FileBrowser;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
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
    public partial class SkeletonLayout : WindowLayout, INotifyPropertyChanged
    {

        public static void OpenFile(Item file)
        {
            var skel = DesignerLib.ResourceReferences.AddSkeleton(file.Path);
            MainWindow.Instance.AttachNewWindowLayout(new SkeletonLayout(skel.Target), true);
        }
        public static void LoadFile(Item file)
        {
            if(new FileInfo(file.Path).Length > 1)
            DesignerLib.ResourceReferences.AddSkeleton(file.Path);
        }

        public ToolWindows.Skeleton.BonesWindow bonesWindow { get; private set; }
        public ToolWindows.Skeleton.AnimationsWindow animWindow { get; private set; }
        public ToolWindows.Skeleton.PropertiesWindow propWindow { get; private set; }
        public DesignerLib.Skeleton skeleton { get; private set; }
        public SkeletonLayout(DesignerLib.Skeleton skeleton)
        {
            this.skeleton = skeleton;
            InitializeComponent();

            this.Header = this.skeleton.Name + (this.skeleton.IsSaved ? "" : "*");
            this.Initialize(mainWindow, this.dockSite);

            {
                SplitPanel splitPanel = new SplitPanel();
                DockWindowGroup dg = new DockWindowGroup();
                dg.Items.Add(bonesWindow = new ToolWindows.Skeleton.BonesWindow(this.skeleton));
                splitPanel.Children.Add(dg);
                DockSite.SetDock(splitPanel, Dock.Top);
                DockSite.SetDockSize(splitPanel, 500);
                this.dockSite.SplitPanels.Add(splitPanel);
                dg.UpdateVisibility();
            }
            //{
            //    SplitPanel splitPanel = new SplitPanel();
            //    DockWindowGroup dg = new DockWindowGroup();
            //    dg.Items.Add(animWindow = new ToolWindows.Skeleton.AnimationsWindow(this.skeleton));
            //    splitPanel.Children.Add(dg);
            //    DockSite.SetDock(splitPanel, Dock.Right);
            //    DockSite.SetDockSize(splitPanel, 200);
            //    this.dockSite.SplitPanels.Add(splitPanel);
            //    dg.UpdateVisibility();
            //}
            //{
            //    SplitPanel splitPanel = new SplitPanel();
            //    DockWindowGroup dg = new DockWindowGroup();
            //    dg.Items.Add(propWindow = new ToolWindows.Skeleton.PropertiesWindow());
            //    splitPanel.Children.Add(dg);
            //    DockSite.SetDock(splitPanel, Dock.Top);
            //    DockSite.SetDockSize(splitPanel, 200);
            //    this.dockSite.SplitPanels.Add(splitPanel);
            //    dg.UpdateVisibility();
            //}

            bonesWindow.Closed += OnBonesWinClosed;
            //animWindow.Closed += OnAnimWinClosed;
            //propWindow.Closed += OnPropWinClosed;
        }

        void Menu_Properties(object sender, RoutedEventArgs e)
        {
            if (this.propWindow != null)
            {
                this.propWindow.FocusContent();
            }
            else
            {
                dockSite.FloatWindow(this.propWindow = new ToolWindows.Skeleton.PropertiesWindow());
                propWindow.Closed += OnPropWinClosed;
            }
        }

        void Menu_Animations(object sender, RoutedEventArgs e)
        {
            if (this.animWindow != null)
            {
                this.animWindow.FocusContent();
            }
            else
            {
                dockSite.FloatWindow(this.animWindow = new ToolWindows.Skeleton.AnimationsWindow(this.skeleton));
                animWindow.Closed += OnAnimWinClosed;
            }
        }

        void Menu_Bones(object sender, RoutedEventArgs e)
        {
            if (this.bonesWindow != null)
            {
                this.bonesWindow.FocusContent();
            }
            else
            {
                dockSite.FloatWindow(this.bonesWindow = new ToolWindows.Skeleton.BonesWindow(this.skeleton));
                bonesWindow.Closed += OnBonesWinClosed;
            }
        }

        void OnBonesWinClosed(object sender, RoutedEventArgs e)
        {
            this.bonesWindow = null;
            OnPropertyChanged("bonesWin");
        }

        void OnAnimWinClosed(object sender, RoutedEventArgs e)
        {
            this.animWindow = null;
            OnPropertyChanged("animWin");
        }

        void OnPropWinClosed(object sender, RoutedEventArgs e)
        {
            this.propWindow = null;
            OnPropertyChanged("propWin");
        }

        private void SaveProjectCommand(object sender, ExecutedRoutedEventArgs e)
        {
            this.skeleton.WriteToFile();
            Project.CurrentProject.resourceFile.WriteFile();
            this.Header = this.skeleton.Name;
            this.skeleton.IsSaved = true;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name)
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
