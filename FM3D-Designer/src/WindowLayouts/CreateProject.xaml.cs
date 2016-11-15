using System;
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
using Microsoft.Win32;

using MahApps.Metro.Controls;
using MahApps.Metro.Controls.Dialogs;

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for MainLayout.xaml
    /// </summary>
    public partial class CreateProject : WindowLayout
    {
        public CreateProject(MainWindow mainWindow)
        {

            InitializeComponent();
            this.Header = "Create Project";

            this.Initialize(mainWindow, null);
        }

        public void bt_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
                tb_path.Text = openFileDialog.FileName;
        }
    }
}
