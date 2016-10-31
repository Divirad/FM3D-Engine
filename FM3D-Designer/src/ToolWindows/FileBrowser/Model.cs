using DevComponents.WPF.Controls;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Collections;

namespace FM3D_Designer.ToolWindows.FileBrowser
{
    public enum FileType
    {
        UNKNOWN,
        DIRECTORY,
    }

    public enum FileState
    {
        NORMAL,
        NOT_FOUND,
        NOT_PROJECT
    }

    public class Model : INotifyPropertyChanged
    {
        public enum ViewMode
        {
            ICONS,
            TREE_ICONS,
            TREE
        }

        private ViewMode _Mode;
        public ViewMode Mode
        {
            get
            {
                return _Mode;
            }
            set
            {
                _Mode = value;
            }
        }

        public Model()
        {
            _RootDirectories = new ObservableCollection<FileSystemObjectData>();
            Refresh();
       }

        private ObservableCollection<FileSystemObjectData> _RootDirectories;
        public IEnumerable<FileSystemObjectData> RootDirectories
        {
            get
            {
                return _RootDirectories;
            }
        }

        public void Refresh()
        {
            _RootDirectories.Clear();
            FileSystemObjectData projectFiles = new FileSystemObjectData(Project.CurrentProject.ProjectFiles.Name, FileType.DIRECTORY, FileState.NORMAL);
            projectFiles.GenerateChildren(new DirectoryInfo(Project.CurrentProject.ProjectFiles.Path), 0, Project.CurrentProject.ProjectFiles, true, FileState.NORMAL);
            _RootDirectories.Add(projectFiles);
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }

    public class FileSystemObjectData : INotifyPropertyChanged
    {
        public FileSystemObjectData(string name, FileType fileType, FileState state)
        {
            this._State = state;
            this._Name = name;
            this._FileType = fileType;
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            var h = PropertyChanged;
            if (h != null)
                h(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private string _Name;
        public string Name
        {
            get { return _Name; }
            set
            {
                _Name = value;
                OnPropertyChanged("Name");
                OnPropertyChanged("DisplayName");
            }
        }

        private FileState _State;
        public FileState State
        {
            get { return _State; }
            set
            {
                _State = value;
                OnPropertyChanged("State");
            }
        }

        private FileType _FileType;

        public FileType FileType
        {
            get
            {
                return _FileType;
            }
        }

        private ObservableCollection<FileSystemObjectData> _Children = new ObservableCollection<FileSystemObjectData>();
        public IList<FileSystemObjectData> Children
        {
            get
            {
                return _Children;
            }
        }

        //public int HierarchyLevel { get; protected set; }

        public void GenerateChildren(DirectoryInfo dirInfo, int hierarchyLevel, Project.Folder projFolder, bool allFiles, FileState fileState)
        {
            if (projFolder == null && allFiles)
            {
                _Children.Clear();
                try
                {
                    foreach (DirectoryInfo dir in dirInfo.GetDirectories())
                    {
                        if ((dir.Attributes & FileAttributes.Hidden) == FileAttributes.Hidden)
                            continue;
                        var folder = new FileSystemObjectData(dir.Name, FileType.DIRECTORY, FileState.NOT_PROJECT);
                        folder.GenerateChildren(dir, hierarchyLevel + 1, projFolder, allFiles, FileState.NOT_PROJECT);
                        _Children.Add(folder);
                    }
                }
                catch (UnauthorizedAccessException) { }

                try
                {
                    foreach (FileInfo fileInfo in dirInfo.GetFiles())
                    {
                        var file = new FileSystemObjectData(fileInfo.Name, GetFileTypeFromExtension(fileInfo.Extension), FileState.NOT_PROJECT);
                        _Children.Add(file);
                    }
                }
                catch (UnauthorizedAccessException) { }
            }
            else if (projFolder != null)
            {
                if (fileState == FileState.NOT_FOUND)
                {
                    _Children.Clear();

                    try
                    {
                        foreach (Project.Folder f in projFolder.SubFolders)
                        {                         
                            var folder = new FileSystemObjectData(f.Name, FileType.DIRECTORY, FileState.NOT_FOUND);
                            folder.GenerateChildren(null, hierarchyLevel + 1, f, allFiles, FileState.NOT_FOUND);
                            _Children.Add(folder);
                        }
                    }
                    catch (UnauthorizedAccessException) { }

                    try
                    {
                        foreach (Project.File f in projFolder.Files)
                        {
                            FileInfo fileInfo = new FileInfo(f.Path);
                            var file = new FileSystemObjectData(fileInfo.Name, GetFileTypeFromExtension(fileInfo.Extension), FileState.NOT_FOUND);
                            _Children.Add(file);
                        }
                    }
                    catch (UnauthorizedAccessException) { }
                }
                else
                {
                    _Children.Clear();

                    List<FileInfo> files = dirInfo.GetFiles().ToList();
                    List<DirectoryInfo> directories = dirInfo.GetDirectories().ToList();

                    try
                    {
                        foreach (Project.Folder f in projFolder.SubFolders)
                        {
                            DirectoryInfo dir = new DirectoryInfo(f.Path);
                            bool isFound = false;
                            foreach (DirectoryInfo d in directories)
                            {
                                if (d.FullName.Equals(dir.FullName))
                                {
                                    isFound = true;
                                    directories.Remove(d);
                                    break;
                                }
                            }
                            var folder = new FileSystemObjectData(dir.Name, FileType.DIRECTORY, isFound ? FileState.NORMAL : FileState.NOT_FOUND);
                            folder.GenerateChildren(dir, hierarchyLevel + 1, f, allFiles, isFound ? FileState.NORMAL : FileState.NOT_FOUND);
                            _Children.Add(folder);
                        }
                        if (allFiles)
                        {
                            foreach (DirectoryInfo dir in directories)
                            {
                                var folder = new FileSystemObjectData(dir.Name, FileType.DIRECTORY, FileState.NOT_PROJECT);
                                folder.GenerateChildren(dir, hierarchyLevel + 1, projFolder, allFiles, FileState.NOT_PROJECT);
                                _Children.Add(folder);
                            }
                        }
                    }
                    catch (UnauthorizedAccessException) { }

                    try
                    {
                        foreach (Project.File f in projFolder.Files)
                        {
                            FileInfo fileInfo = new FileInfo(f.Path);
                            bool isFound = false;
                            foreach (FileInfo fi in files)
                            {
                                if (fi.FullName.Equals(fileInfo.FullName))
                                {
                                    isFound = true;
                                    files.Remove(fi);
                                    break;
                                }
                            }
                            var file = new FileSystemObjectData(fileInfo.Name, GetFileTypeFromExtension(fileInfo.Extension), isFound ? FileState.NORMAL : FileState.NOT_FOUND);
                            _Children.Add(file);
                        }
                        if (allFiles)
                        {
                            foreach (FileInfo fi in files)
                            {
                                var file = new FileSystemObjectData(fi.Name, GetFileTypeFromExtension(fi.Extension), FileState.NOT_PROJECT);
                                _Children.Add(file);
                            }
                        }
                    }
                    catch (UnauthorizedAccessException) { }
                }
            }
        }

        public static bool DetermineHasChildren(DirectoryInfo dirInfo)
        {
            try
            {
                foreach (var dir in dirInfo.EnumerateDirectories())
                {
                    if ((dir.Attributes & FileAttributes.Hidden) == FileAttributes.Hidden)
                        continue;
                    return true;
                }
            }
            catch (UnauthorizedAccessException) { }

            try
            {
                foreach (var fileInfo in dirInfo.EnumerateFiles())
                    return true;
            }
            catch (UnauthorizedAccessException) { }

            return false;
        }

        public static FileType GetFileTypeFromExtension(string ext)
        {
            if(ext.Equals("test", StringComparison.Ordinal))
            {
                return FileType.UNKNOWN;
            }
            else
            {
                return FileType.UNKNOWN;
            }
        }
    }
}
