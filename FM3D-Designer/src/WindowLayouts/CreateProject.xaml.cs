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
                tb_path.Text = openbrowserdialog.SelectedPath;
        }
        public void startdev(object sender, RoutedEventArgs e)
        {

            //XmlWriter writer = new XmlWriter();
            string path = tb_path.Text + @"\" + tb_name.Text;
            string projfiles = path + @"\" + @"ProjectFiles";
            string text = path + @"\" + @"ProjectFiles\Textures";
            string ent = path + @"\" + @"ProjectFiles\Entities";
            string scen = path + @"\" + @"ProjectFiles\Scenes";
            string pathtofile = path + @"\" + tb_name.Text + ".fmproj";

            Directory.CreateDirectory(text);
            Directory.CreateDirectory(ent);
            Directory.CreateDirectory(scen);

            //File.Create(pathtofile);
            mainWindow.ClearAttachedWindows();
            ///
            ///XML - Neues XML Element
            ///
            XmlDocument projfile = new XmlDocument();
            //projfile.CreateDocumentFragment(pathtofile);
            ///
            ///Main Knoten & "initialisierung"cdes knotens in das projekt
            /// 

            XmlNode mainproj = projfile.CreateElement("Project");
                ///
                ///Hinzufügen des knotens in den geschrieben werden soll 
                ///         <Project>   
                ///
                ///         </Project>
                ///
                projfile.AppendChild(mainproj);

            XmlNode projectfilesdir = projfile.CreateElement("ProjectFiles");
            XmlNode folder = projfile.CreateElement("Folder");

            XmlNode file = projfile.CreateElement("File");
            XmlAttribute name = projfile.CreateAttribute("name"); ///Neues Attribut

            //ProjectFile Dir
            name.Value = "ProjectFiles";
            projectfilesdir.Attributes.Append(name);
            mainproj.AppendChild(projectfilesdir);

            //Entitie Dir
            name.Value = "Entities";
            folder.Attributes.Append(name);
            projectfilesdir.AppendChild(folder);
            //Textures Dir
            name.Value = "Textures";
            folder.Attributes.Append(name);
            projectfilesdir.AppendChild(folder);
            //Scenes Dir
            name.Value = "Scenes";
            folder.Attributes.Append(name);
            projectfilesdir.AppendChild(folder);

            projfile.Save(pathtofile);

            Project.Load(pathtofile);

            mainWindow.AttachNewWindowLayout(new MainLayout(this.mainWindow), true);
        }

    }
}
