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

using System.Windows.Controls.Primitives;

namespace FM3D_Designer
{
    /// <summary>
    /// Interaction logic for FileBrowserLayout.xaml
    /// </summary>
    public partial class FileBrowserWindow : ToolWindow
    {
        public FileBrowserWindow(WindowLayout mainWindow)
        {
            InitializeComponent();
            this.Header = "File Browser";
            this.Initialize(mainWindow);
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
    }
}
