using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Collections.ObjectModel;
using System.Xml;

namespace FM3D_Designer.src
{
    public class Project
    {
        public class File
        {
            public File(string name)
            {
                this.Name = name;
            }
            public string Name { get; set; }
            public string Path { get; set; }
        }
        public class Folder
        {
            public Folder(string name, string path = "")
            {
                this.Name = name;
                this.Path = path;
                this.Files = new ObservableCollection<File>();
                this.SubFolders = new ObservableCollection<Folder>();
            }
            public string Name { get; set; }
            public ObservableCollection<Folder> SubFolders { get; set; }
            public ObservableCollection<File> Files { get; set; }
            public string Path { get; set; }

            public void SetFilePaths()
            {
                foreach (File file in this.Files)
                {
                    file.Path = this.Path + "/" + file.Name;
                }
                foreach (Folder folder in this.SubFolders)
                {
                    folder.Path = this.Path + "/" + folder.Name;
                    folder.SetFilePaths();
                }
            }
        }

        private const string ProjectFilesDirectory = "/ProjectFiles";

        public string _Name { get; set; }
        public string _Directory { get; set; }
        public Folder ProjectFiles { get; set; }
        private static Project _CurrentProject = null;
        public static Project CurrentProject { get { return _CurrentProject; } }

        public Project(string path)
        {
            this._Directory = new FileInfo(path).Directory.FullName;
            this.ProjectFiles = new Folder("ProjectFiles", this._Directory + ProjectFilesDirectory);
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

        private static void LoadProjectFiles(Folder folder, XmlReader xml)
        {
            while(xml.Read())
            {
                if(xml.NodeType == XmlNodeType.Element)
                {
                    if(xml.Name == "File")
                    {
                        xml.MoveToAttribute("name");
                        folder.Files.Add(new File(xml.Value));
                    }
                    else if(xml.Name == "Folder")
                    {
                        xml.MoveToAttribute("name");
                        Folder f = new Folder(xml.Value);
                        xml.MoveToElement();
                        if (xml.IsStartElement())
                        {
                            xml.MoveToContent();
                            LoadProjectFiles(f, xml);
                        }
                        folder.SubFolders.Add(f);
                    }
                } else if(xml.NodeType == XmlNodeType.EndElement)
                {
                    return;
                }
            }
        }

        public static void CreateProject(string dirpath, string dirname)
        {

            //XmlWriter writer = new XmlWriter();
            string path = dirpath + @"\" + dirname;
            string projfiles = path + @"\" + @"ProjectFiles";
            string text = path + @"\" + @"ProjectFiles\Textures";
            string ent = path + @"\" + @"ProjectFiles\Entities";
            string scen = path + @"\" + @"ProjectFiles\Scenes";
            string pathtofile = path + @"\" + dirname + ".fmproj";

            Directory.CreateDirectory(text);
            Directory.CreateDirectory(ent);
            Directory.CreateDirectory(scen);
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
            XmlNode entfolder = projfile.CreateElement("Folder");
            XmlNode textfolder = projfile.CreateElement("Folder");
            XmlNode scenesfolder = projfile.CreateElement("Folder");

            XmlNode file = projfile.CreateElement("File");

            XmlAttribute name = projfile.CreateAttribute("name");
            XmlAttribute namescen = projfile.CreateAttribute("name"); ///Neues Attribut
            XmlAttribute nameent = projfile.CreateAttribute("name");
            XmlAttribute nametext = projfile.CreateAttribute("name");
            //ProjectFile Dir
            name.Value = "ProjectFiles";
            projectfilesdir.Attributes.Append(name);
            mainproj.AppendChild(projectfilesdir);

            //Entitie Dir
            nameent.Value = "Entities";
            entfolder.Attributes.Append(nameent);
            entfolder.InnerText = " ";
            projectfilesdir.AppendChild(entfolder);

            //Textures Dir
            nametext.Value = "Textures";
            textfolder.Attributes.Append(nametext);
            textfolder.InnerText = " ";
            projectfilesdir.AppendChild(textfolder);

            //Scenes Dir
            namescen.Value = "Scenes";
            scenesfolder.Attributes.Append(namescen);
            scenesfolder.InnerText = " ";
            projectfilesdir.AppendChild(scenesfolder);

            projfile.Save(pathtofile);

            Project.Load(pathtofile);
        }

        public static void InsertFile(File file)
        {
            
        }

        public static void InsertDir(Folder folder)
        {

        }
    }
}
