using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Collections.ObjectModel;
using System.Xml;

namespace FM3D_Designer.src
{
    public class Project
    {
        public class FileObject
        {
            public string Name { get; protected set; }
            public string Path { get; set; } = "";
            public FileObject(string name)
            {
                this.Name = name;
            }
        }
        public class File : FileObject
        {
            public File(string name): base(name)
            {

            }
        }
        public class Directory : FileObject
        {
            public Directory(string name, string path = ""): base(name)
            {
                this.Content = new ObservableCollection<FileObject>();
                this.Files = new ObservableCollection<File>();
                this.SubDirectories = new ObservableCollection<Directory>();
            }
            public ObservableCollection<FileObject> Content { get; protected set; }
            public ObservableCollection<File> Files { get; protected set; }
            public ObservableCollection<Directory> SubDirectories { get; protected set; }

            public void SetFilePaths()
            {
                foreach (FileObject fo in this.Content)
                {
                    fo.Path = this.Path + "/" + fo.Name;
                    (fo as Directory)?.SetFilePaths();
                }
            }
        }

        public class RootDirectory : Directory
        {
            public RootDirectory(string name, string path, bool visibleInBrowser = true) : base(name)
            {
                this.VisibleInBrowser = visibleInBrowser;
                this.Path = path;
            }

            public bool VisibleInBrowser { get; protected set; }
        }

        private const string ProjectFilesDirectory = "/ProjectFiles";

        public string _Name { get; set; }
        public string _Directory { get; set; }
        public RootDirectory ProjectFiles { get; set; }
        private static Project _CurrentProject = null;
        public static Project CurrentProject { get { return _CurrentProject; } }

        public Project(string path)
        {
            this._Directory = new FileInfo(path).Directory.FullName;
            this.ProjectFiles = new RootDirectory("ProjectFiles", this._Directory + ProjectFilesDirectory);

        }

        public static Project Load(string path)
        {
            if (_CurrentProject != null)
            {
                throw new Exception("A Project is already opened!");
            }
            else
            {
                Project result = new Project(path);

                XmlReaderSettings settings = new XmlReaderSettings();
                settings.IgnoreWhitespace = true;
                XmlReader xml = XmlReader.Create(path, settings);
                xml.ReadToDescendant("Project");
                LoadXmlFile(path, result, xml.ReadSubtree());

                xml.Close();

                _CurrentProject = result;
                return result;
            }
        }

        private static void LoadXmlFile(string path, Project proj, XmlReader xml)
        {
            while (xml.Read())
            {
                if ((xml.NodeType == XmlNodeType.Element) && (xml.Name == "ProjectFiles") && (xml.Depth == 1))
                {
                    LoadProjectFiles(proj.ProjectFiles, xml);
                    proj.ProjectFiles.SetFilePaths();
                }
            }
            xml.Close();
        }

        private static void LoadProjectFiles(Directory folder, XmlReader xml)
        {
            while(xml.Read())
            {
                if(xml.NodeType == XmlNodeType.Element)
                {
                    if(xml.Name == "File")
                    {
                        xml.MoveToAttribute("name");
                        var xf = new File(xml.Value);
                        folder.Content.Add(xf);
                        folder.Files.Add(xf);
                    }
                    else if(xml.Name == "Folder")
                    {
                        xml.MoveToAttribute("name");
                        Directory f = new Directory(xml.Value);
                        xml.MoveToElement();
                        if (xml.IsStartElement())
                        {
                            xml.MoveToContent();
                            LoadProjectFiles(f, xml);
                        }
                        folder.Content.Add(f);
                        folder.SubDirectories.Add(f);
                    }
                } else if(xml.NodeType == XmlNodeType.EndElement)
                {
                    return;
                }
            }
        }

        public static bool CreateProject(string dirpath, string dirname)
        {
            //XmlWriter writer = new XmlWriter();
            string path = dirpath + @"\" + dirname;
            string cppdir = path + @"\Cpp";
            string projfiles = path + @"\ProjectFiles";
            string ent = path + @"\ProjectFiles\Entities";
            string text = path + @"\ProjectFiles\Textures";
            string mesh = path + @"\ProjectFiles\Models";
            string pathtofile = path + @"\" + dirname + ".fmproj";
            string fm3dxml = path + @"\Cpp\fm3d.xml";

            if (System.IO.File.Exists(pathtofile))
            {
                return false;
            }
            else
            {
                System.IO.Directory.CreateDirectory(cppdir);
                System.IO.Directory.CreateDirectory(text);
                System.IO.Directory.CreateDirectory(ent);
                System.IO.Directory.CreateDirectory(mesh);

    ///
    /// #################################FM3D PROJECT-FILE ####################################################
    /// 
                using (XmlWriter writer = XmlWriter.Create(pathtofile))
                {
                    writer.WriteStartDocument();
                        writer.WriteStartElement("Project");
                        writer.WriteAttributeString("name", dirname);

                            writer.WriteStartElement("ProjectFiles");
                            
                                writer.WriteStartElement("Folder");
                                writer.WriteAttributeString("name", "Entities");
                                writer.WriteString(" ");
                                writer.WriteEndElement();

                                writer.WriteStartElement("Folder");
                                writer.WriteAttributeString("name", "Textures");
                                writer.WriteString(" ");
                                writer.WriteEndElement();

                                writer.WriteStartElement("Folder");
                                writer.WriteAttributeString("name", "Models");
                                writer.WriteString(" ");
                                writer.WriteEndElement();

                            writer.WriteEndElement();

                            writer.WriteStartElement("CPlusPlus");
                                writer.WriteStartElement("FM3D_File");
                                writer.WriteAttributeString("name", "fm3d.xml");
                                writer.WriteEndElement();
                                writer.WriteStartElement("Solution");
                                writer.WriteAttributeString("name", dirname+".sln");
                                writer.WriteEndElement();

                            writer.WriteEndElement();
                        writer.WriteEndElement();
                    writer.WriteEndDocument();
                }

    /// 
    /// #################################FM3D XML ####################################################
    /// 
                System.Random t = new Random(23);
                int rb = t.Next(100000, 1000000);

                System.Random a = new Random(rb);
                int b = a.Next(100000, 1000000);
                string projid = Convert.ToString(b);

                using (XmlWriter writer = XmlWriter.Create(fm3dxml))
                {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("FM3D_Project");
                    writer.WriteAttributeString("Name", dirname);

                    writer.WriteStartElement("MainProject");
                    writer.WriteAttributeString("Name", dirname);
                    writer.WriteEndElement();

                    writer.WriteStartElement("Pipe");
                    writer.WriteAttributeString("Name", "FM3D_" + dirname + "_" + projid);
                    writer.WriteEndElement();

                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                }
                /// 
                /// ################################# FILES ####################################################
                /// 
                //System.Diagnostics.Process.Start(Environment.CurrentDirectory+ "\\..\\..\\resources\\proj"); //GameProject.sln
                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.sln")){ return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.sln", cppdir + @"\" + dirname + ".sln");

                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj")) { return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj", cppdir + @"\" + dirname + ".vcxproj");

                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj")) { return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj.filters", cppdir + @"\" + dirname + ".vcxproj.filters");

                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\Quelle.cpp")) { return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\Quelle.cpp", cppdir + @"\Quelle.cpp");
                
                Project.Load(pathtofile);
                return true;
            }
        }

        public static void SaveProject()
        {
            //MainWindow.Instance.visualStudio.AddClass("");
            throw new NotImplementedException();
        }

    }
}
