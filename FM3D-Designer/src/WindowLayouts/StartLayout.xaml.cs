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
    /// Interaction logic for StartLayout.xaml
    /// </summary>
    public partial class StartLayout : WindowLayout
    {
        OpenFileDialog openFileDialog = new OpenFileDialog();

        public StartLayout(MainWindow mainWindow)
        {
            InitializeComponent();

            //Initialize DockWindow
            this.Header = "StartPage";

            this.Initialize(mainWindow, null);
        }


        public void New_Click(object sender, RoutedEventArgs e)
        {
            mainWindow.AttachNewWindowLayout(new CreateProject(this.mainWindow), true);
        }

        private void btn_start_Click(object sender, RoutedEventArgs e)
        {
            LoadProj(sender,  e);
        }

        private bool LoadProj(object sender, RoutedEventArgs e)
        {
            string xmlfile = System.IO.File.ReadAllText(this.tb_path.Text);
            if (!xmlfile.Contains("<Project>") || !xmlfile.Contains("</Project>"))
            {
                ShowMessage("Errorcode EIFOK", "No FM3D Project!\nOpen a ~REAL~ FM3D Project!\n;)");
                return false;
            }

            if (!xmlfile.Contains("ProjectFiles") || !xmlfile.Contains("/ProjectFiles"))
            {
                ShowMessage("Error", "This project is damaged!\nNo ProjectFiles found!");
                return false;
            }

            if (!xmlfile.Contains("CPlusPlus") || !xmlfile.Contains("/CPlusPlus"))
            {
                ShowMessage("Error", "This project is damaged!\nNo CPlusPlus found!");
                return false;
            }

            if (!xmlfile.Contains("<FM3D_File") )
            {
                ShowMessage("Error", "This project is damaged!\nNo FM3D_File found!");
                return false;
            }

            if (!xmlfile.Contains("<Solution"))
            {
                ShowMessage("Error", "This project is damaged!\nNo Solution found!");
                return false;
            }


            if (!xmlfile.Contains("<Folder"))
            {
                ShowMessage("Warning!", "This project does not contain any directory!\n It will become confusing for you!\nCREATE SOME WITH THIS FANCY ENGINE!");
            }

            if (!xmlfile.Contains("<File"))
            {
                ShowMessage("Warning!", "This project does not contain any file!\n It will become confusing for you!\nCREATE SOME WITH THIS FANCY ENGINE!");
            }

            Properties.Settings.Default.lastpath = tb_path.Text;
            Properties.Settings.Default.Save();

            mainWindow.ClearAttachedWindows();
            Project.Load(this.tb_path.Text);
            mainWindow.AttachNewWindowLayout(new MainLayout(this.mainWindow), true);
            WindowLayout layout = new TextureLayout();
            mainWindow.AttachNewWindowLayout(layout);
            //WindowLayout layout2 = new MeshLayout();
            //mainWindow.AttachNewWindowLayout(layout2);

        private async void ShowMessage(string titel, string message)
        {
            await mainWindow.ShowMessageAsync(titel, message);
        }
        private void NewProj(object sender, ExecutedRoutedEventArgs e)
        {
            mainWindow.AttachNewWindowLayout(new CreateProject(this.mainWindow), true);
        }

        private void OpenProj(object sender, ExecutedRoutedEventArgs e)
        {
            openFileDialog.FileName = "fmproj";
            openFileDialog.Title = "Open your FM3D Project-File";

            if (openFileDialog.ShowDialog() == true)
                tb_path.Text = openFileDialog.FileName;
        }
        private void CloseProj(object sender, ExecutedRoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
        private void testButton_Click(object sender, RoutedEventArgs e)
        {
            this.tb_path.Text = "../../TestProjects/Project 0/project 0.fmproj";
        }

        async public void NewProject(object sender, RoutedEventArgs e)
        {
            var varmsg_name = await ((MetroWindow)Application.Current.MainWindow).ShowInputAsync("New Project", "Name your fancy project!"/*, MessageDialogStyle.AffirmativeAndNegative/*/);

            if (openFileDialog.ShowDialog() == true)
            { tb_path.Text = openFileDialog.FileName; }

            var varmsg_path = await ((MetroWindow)Application.Current.MainWindow).ShowInputAsync("New Project", "Path!"/*, MessageDialogStyle.AffirmativeAndNegative/*/);

            string path = varmsg_path + @"\" + varmsg_name;
            string projfiles = path + @"\" + "ProjectFiles";
            string file = path + @"\" + varmsg_name + ".fmproj";
            System.IO.Directory.CreateDirectory(path);
            System.IO.Directory.CreateDirectory(projfiles + "ObjectFiles");
            System.IO.Directory.CreateDirectory(projfiles + "ResourceFiles");
            System.IO.Directory.CreateDirectory(projfiles + "SourceFiles");
            System.IO.Directory.CreateDirectory(projfiles + "TextureFiles");
            System.IO.Directory.CreateDirectory(projfiles);
            System.IO.File.Create(file);
            mainWindow.ClearAttachedWindows();

            file.Replace('\\', '/');
            file.Replace('C', '\b');
            file.Replace(':', '\b');

            Project.Load(file);

            mainWindow.AttachNewWindowLayout(new MainLayout(this.mainWindow), true);
            //path + "\\" + varmsg_name + ".fmproj"



        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
             tb_path.Text = Properties.Settings.Default.lastpath;
        }
    }
}
