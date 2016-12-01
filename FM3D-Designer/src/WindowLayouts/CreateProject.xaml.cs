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
using System.Windows.Forms;
using System.IO;

using System.Collections.ObjectModel;
using System.Xml;

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

            //var result = await((MetroWindow)Application.Current.MainWindow).ShowMessageAsync("Deleeete", "This will delete the file/directory for ever!", MessageDialogStyle.AffirmativeAndNegative);
            //if (result == MessageDialogResult.Affirmative)
            //{ }

            this.Initialize(mainWindow, null);
        }

        public void bt_Click(object sender, RoutedEventArgs e)
        {
            FolderBrowserDialog openbrowserdialog = new FolderBrowserDialog();

            if (openbrowserdialog.ShowDialog() == DialogResult.OK)
            { tb_path.Text = openbrowserdialog.SelectedPath; }
        }
        
        public void startdev(object sender, RoutedEventArgs e)
        {
            Project.CreateProject(tb_path.Text, tb_name.Text);
            mainWindow.ClearAttachedWindows();
            mainWindow.AttachNewWindowLayout(new MainLayout(this.mainWindow), true);
        }
    }
}
