using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Collections.ObjectModel;
using System.Xml;

namespace FM3D_Designer
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

        private static Project _CurrentProject = null;
        public static Project CurrentProject { get { return _CurrentProject; } }

        public Project(string path)
        {
            this.Directory = new FileInfo(path).Directory.FullName;
            this.ProjectFiles = new Folder("ProjectFiles", this.Directory + ProjectFilesDirectory);
        }

        private const string ProjectFilesDirectory = "/ProjectFiles";
        public string Name { get; set; }

        public string Directory { get; set; }

        public Folder ProjectFiles { get; set; }

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


    }
}
