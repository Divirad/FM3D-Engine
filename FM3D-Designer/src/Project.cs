using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Collections.ObjectModel;
using System.Xml;
using MahApps.Metro.Controls.Dialogs;
using FM3D_Designer.src.ToolWindows.FileBrowser;
using System.Windows.Media;
using System.Text.RegularExpressions;

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

        public string _Name { get; private set; }
        public string _Directory { get; private set; }
        public RootDirectory ProjectFiles { get; private set; }
        private static Project _CurrentProject = null;
        public static Project CurrentProject { get { return _CurrentProject; } }

        public ResourceFile resourceFile { get; private set; }

        public Project(string path)
        {
            this._Directory = new FileInfo(path).Directory.FullName;
            this._Name = "UnknownName";
            this.ProjectFiles = new RootDirectory("ProjectFiles", this._Directory + ProjectFilesDirectory);
            this.resourceFile = new ResourceFile(_Directory + "/Cpp/Resources.h");
        }

        public void SetProjName(string name) {
            this._Name = name;
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

                XmlReader xm = XmlReader.Create(path, settings);
                xm.ReadToDescendant("Project");
                xm.MoveToAttribute("name");
                string name = "";
                name = xm.Value;
                xm.Close();

                result._Name = name;
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
                    //if(xml.Name == "File" || xml.Name == "MaterialFile" || xml.Name == "TextureFile" || xml.Name == "SkeletonFile" || xml.Name == "MeshFile" || xml.Name == "File")
                    if (xml.Name.Contains("File"))
                    {
                        xml.MoveToAttribute("name");
                        var xf = new File(xml.Value);
                        folder.Content.Add(xf);
                        folder.Files.Add(xf);
                    }
                    else if(xml.Name == "Directory")
                    {
                        xml.MoveToAttribute("name");
                        Directory f = new Directory(xml.Value);
                        xml.MoveToElement();
                        //if (xml.IsStartElement())
                        if (!xml.IsEmptyElement)
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
                            
                                writer.WriteStartElement("Directory");
                                writer.WriteAttributeString("name", "Entities");
                                writer.WriteString(" ");
                                writer.WriteEndElement();

                                writer.WriteStartElement("Directory");
                                writer.WriteAttributeString("name", "Textures");
                                writer.WriteString(" ");
                                writer.WriteEndElement();

                                writer.WriteStartElement("Directory");
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
                System.Random t = new Random();
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
                    writer.WriteAttributeString("Name", "GameProject");
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

                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.sln")){ return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.sln", cppdir + @"\GameProject.sln");

                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj")) { return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj", cppdir + @"\GameProject.vcxproj");

                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj")) { return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\GameProject.vcxproj.filters", cppdir + @"\GameProject.vcxproj.filters");

                if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\Main.cpp")) { return false; }
                System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\Main.cpp", cppdir + @"\Main.cpp");

				if (!System.IO.File.Exists(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\presets.h")) { return false; }
				System.IO.File.Copy(Environment.CurrentDirectory + "\\..\\..\\resources\\proj\\presets.h", cppdir + @"\presets.h");

#if DEBUG
				string EngineDllDir = Environment.CurrentDirectory + @"\..\..\..\Debug";
				string EngineIncludeDir = Environment.CurrentDirectory + @"\..\..\..\FM3D-Engine";
#endif
				System.IO.File.WriteAllText(cppdir + @"\GameProject.vcxproj", System.IO.File.ReadAllText(cppdir + @"\GameProject.vcxproj").
					Replace("ENGINE_INCLUDE_DIR", EngineIncludeDir).Replace("ENGINE_DLL_DIR", EngineDllDir));
				
				Project.Load(pathtofile);
                return true;
            }
        }
        
        public string GetProjectPath() {
            return _Directory; ;
        }

        private bool AnalyseChildren(XmlWriter writer, ToolWindows.FileBrowser.Item i) {

            foreach (ToolWindows.FileBrowser.Item child in i.Children) {
                
                if (child.State == ToolWindows.FileBrowser.Item.ItemState.NORMAL) {
                    writer.WriteStartElement(child.type.ToString().Replace(" ", ""));
                    
                    writer.WriteAttributeString("name", child.Name);
                    writer.WriteAttributeString("type", child.type.ToString().Replace(" ", ""));
                    writer.WriteAttributeString("path", child.Path);
                    
                    if (child.Children.Count >= 1) {
                        AnalyseChildren(writer, child);
                    }
                    writer.WriteEndElement();
                }
            }
            
            return true;
        }

        public static async void SaveProject(MainWindow w) {
            double progress = 0.0;
            var controller = await w.ShowProgressAsync("Please wait... DON'T CLOSE THE PROGRAMM", "Saving Process Started...");

            controller.SetProgress(progress);
            string path = Project.CurrentProject._Directory + "\\" + Project.CurrentProject._Name + ".fmproj";
            
            if (System.IO.File.Exists(path) == true) {
                System.IO.File.Delete(path);
                controller.SetMessage("Overwriting Old File...");
            }
            progress = 0.3;
            controller.SetProgress(progress);
            controller.SetMessage("Saving Files Into The FM3D-Project-File...");

            using (XmlWriter writer = XmlWriter.Create(path)) {
                writer.WriteStartDocument();
                writer.WriteStartElement("Project");
                writer.WriteAttributeString("name", Project.CurrentProject._Name);

                foreach (ToolWindows.FileBrowser.Item i in ToolWindows.FileBrowser.View.Instance.logic.RootDirectories) {
                    writer.WriteStartElement("ProjectFiles");
                    writer.WriteAttributeString("name", i.Name);
                    Project.CurrentProject.AnalyseChildren(writer, i);
                    writer.WriteEndElement();
                }
                progress = 0.8;
                controller.SetProgress(progress);
                controller.SetMessage("Writging Pipe Information...");

                writer.WriteStartElement("CPlusPlus");
                writer.WriteStartElement("FM3D_File");
                writer.WriteAttributeString("name", "fm3d.xml");
                writer.WriteEndElement();
                progress = 0.9;
                controller.SetProgress(progress);

                controller.SetMessage("Writging Solution Information...");
                writer.WriteStartElement("Solution");
                writer.WriteAttributeString("name", "GameProject.sln");
                writer.WriteEndElement();
                writer.WriteEndElement();

                writer.WriteEndElement();
                writer.WriteEndDocument();
                progress = 1.0;
                controller.SetProgress(progress);
                await controller.CloseAsync();


            }

        }
        public static void AddClass() {
            MainWindow.Instance.visualStudio.AddClass("Blah", "Quelle.cpp");

            MainWindow.Instance.visualStudio.AddClass("Blah2", "Quelle.cpp");
            MainWindow.Instance.visualStudio.AddClass("Fischilein", "Quelle.cpp", new string[] { "Blah" });
        }

		// View.Instance.logic.RootDirectories

		public List<Entity> GetAllEntities() {
			List<Entity> all = new List<Entity>();

			foreach (var i in Item.AllItems[ItemTypes.EntityFile]) {
				if (i.State == ToolWindows.FileBrowser.Item.ItemState.NORMAL) {
					Entity ent = new Entity(System.IO.File.ReadAllText(i.Path));
					all.Add(ent);
				}
			}
			return all;
		}
		// Project.CurrentProject.GetAllEntities()
		public List<string> ConvertAllEntitiesToString() {
			List<string> list = new List<string>();
			foreach(Entity e in Project.CurrentProject.GetAllEntities()) {
				list.Add(e.ToString());
			}
			return list;
		}
		public static void TestEntityConvertTostr() {
			//(189, 00, 255));
			MainWindow.Instance.StatusColor = new SolidColorBrush(Color.FromRgb(189, 00, 255));
			MainWindow.Instance.tb_statbar.Text = "Exporting Enities...";

			MainWindow.Instance.visualStudio.SendEntities(Project.CurrentProject.ConvertAllEntitiesToString());

			MainWindow.Instance.StatusColor = new SolidColorBrush(Color.FromRgb(0, 122, 204));

			MainWindow.Instance.tb_statbar.Text = "VisualStudio is Started";
		}
	}
}
