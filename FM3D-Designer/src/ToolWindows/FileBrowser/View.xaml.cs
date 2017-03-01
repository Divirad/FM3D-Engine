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

using System.Windows.Controls.Primitives;

namespace FM3D_Designer.src.ToolWindows.FileBrowser
{
    /// <summary>
    /// Interaction logic for FileBrowserView.xaml
    /// </summary>
    public partial class View : ToolWindow
    {
        public static View Instance { get; private set; }

        public Logic logic
        {
            get
            {
                return this.Resources["logic"] as Logic;
            }
        }

        public View(WindowLayout mainWindow)
        {
            if (Instance != null)
                throw new InvalidOperationException("You cant create multiple objects of class Filebrowser.View");
            Instance = this;

            InitializeComponent();
            this.Header = "File Browser";
            
            this.Initialize(mainWindow);
        }

        ~View()
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

        private void TreeViewItemRClick(object sender, MouseEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;
            item.IsSelected = true;
            e.Handled = true;
        }
    }
}
