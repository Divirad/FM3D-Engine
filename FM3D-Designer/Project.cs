using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace FM3D_Designer
{
    class Project
    {
        private static Project _CurrentProject = null;
        public static Project CurrentProject { get { return _CurrentProject; } }

        public Project(string path)
        {
            this.Directory = new FileInfo(path).Directory.FullName;
        }

        public const string ProjectFilesDirectory = "/ProjectFiles";
        public string Name { get; set; }

        public string Directory { get; set; }

        public static Project Load(string path)
        {
            if (_CurrentProject != null)
            {
                throw new Exception("A Project is already opened!");
            }
            else
            {
                Project result = new Project(path);
                _CurrentProject = result;
                return result;
            }
        }
    }
}
