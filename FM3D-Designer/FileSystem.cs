using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using DevComponents.WPF.Controls;
using System.Windows.Controls;
using System.Windows.Data;

namespace FM3D_Designer
{
    public class FileSystemObjectNameValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, System.Globalization.CultureInfo cultureInfo)
        {
            var strValue = value as String;
            if (String.IsNullOrWhiteSpace(strValue))
                return new ValidationResult(false, "A name is required.");
            if (strValue.IndexOfAny(new char[] { '/', '\\', ':', '*', '"', '<', '>', '|' }) >= 0)
                return new ValidationResult(false, @"The name cannot contain any of the following characters: \/:*""<>|");
            return ValidationResult.ValidResult;
        }
    }
    public class FileSystemObjectData : INotifyPropertyChanged, IDataErrorInfo
    {
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

        public string Type { get; set; }

        public int HierarchyLevel { get; protected set; }

        private Uri _ImageSource;
        public Uri ImageSource
        {
            get { return _ImageSource; }
            set
            {
                if (value != _ImageSource)
                {
                    _ImageSource = value;
                    OnPropertyChanged("ImageSource");
                }
            }
        }

        private bool _IsExpanded;
        public bool IsExpanded
        {
            get { return _IsExpanded; }
            set
            {
                if (_IsExpanded != value)
                {
                    _IsExpanded = value;
                    OnPropertyChanged("IsExpanded");
                }
            }
        }

        protected static ObservableCollection<FolderContentObjectData> GenerateChildren(DirectoryInfo dirInfo, int hierarchyLevel)
        {
            var list = new ObservableCollection<FolderContentObjectData>();

            try
            {
                foreach (var dir in dirInfo.GetDirectories())
                {
                    if ((dir.Attributes & FileAttributes.Hidden) == FileAttributes.Hidden)
                        continue;
                    var folder = new FolderData(dir, hierarchyLevel + 1);
                    list.Add(folder);
                }
            }
            catch (UnauthorizedAccessException) { }

            try
            {
                foreach (var fileInfo in dirInfo.GetFiles())
                {
                    var file = new FileData(fileInfo);
                    list.Add(file);
                }
            }
            catch (UnauthorizedAccessException) { }
            return list;
        }

        protected static bool DetermineHasChildren(DirectoryInfo dirInfo)
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

        private bool IsValidFileName(string name)
        {
            if (name.Contains('<'))
                return false;
            if (name.Contains('>'))
                return false;
            if (!(this is DriveData) && name.Contains(':'))
                return false;
            if (name.Contains('"'))
                return false;
            if (name.Contains('/'))
                return false;
            if (name.Contains('\\'))
                return false;
            if (name.Contains('|'))
                return false;
            if (name.Contains('?'))
                return false;
            if (name.Contains('*'))
                return false;

            return true;
        }

        public string Error
        {
            get { return null; }
        }

        public string this[string columnName]
        {
            get
            {
                if (columnName == "Name")
                {
                    if (String.IsNullOrEmpty(Name))
                        return "Name cannot be empty.";
                    else if (!IsValidFileName(Name))
                    {
                        return @"Name cannot contain any of the following characters: <,>,:,"",/,\,|,?,*";
                    }
                }

                return null;
            }
        }
    }

    public class FolderContentObjectData : FileSystemObjectData
    {

    }

    public class FolderData : FolderContentObjectData, IEnumerableProvider
    {
        private DirectoryInfo _DirInfo;
        public FolderData()
        {
        }

        public FolderData(DirectoryInfo dirInfo, int hierarchyLevel)
        {
            _DirInfo = dirInfo;
            HierarchyLevel = hierarchyLevel;
            Name = _DirInfo.Name;
            IsExpanded = false;
            ImageSource = new Uri("resources/images/file browser/folder_closed.ico", UriKind.Relative);
            Type = "Folder";
        }

        private IList<FolderContentObjectData> _Children;
        public IList<FolderContentObjectData> Children
        {
            get
            {
                if (_Children == null)
                    _Children = FileSystemObjectData.GenerateChildren(_DirInfo, HierarchyLevel);
                return _Children;
            }
        }

        public bool HasItems
        {
            get
            {
                return FileSystemObjectData.DetermineHasChildren(_DirInfo);
            }
        }

        public IEnumerable GetEnumerable()
        {
            return Children;
        }

        protected override void OnPropertyChanged(string propertyName)
        {
            base.OnPropertyChanged(propertyName);

            if (GetType() == typeof(FolderData))
                ImageSource = IsExpanded ? new Uri("resources/images/file browser/folder_open_icon.ico", UriKind.Relative) : new Uri("resources/images/file browser/folder_closed_icon.ico", UriKind.Relative);
        }

        public override string ToString()
        {
            return string.Format("Folder: {0}", Name);
        }

    }
    
    public class FileData : FolderContentObjectData
    {
        public FileData()
        {

        }

        public FileData(FileInfo fileInfo)
        {
            Name = fileInfo.Name;
            Type = "File";
            ImageSource = new Uri("resources/images/file browser/file_icon.ico", UriKind.Relative);
        }

        public override string ToString()
        {
            return string.Format("File: {0}", Name);
        }
    }

    public class DriveData : FileSystemObjectData, IEnumerableProvider
    {
        DriveInfo _DriveInfo;
        public DriveData()
        { }

        public DriveData(DriveInfo drive)
        {
            _DriveInfo = drive;
            Name = drive.Name.Replace(@"\", "");
            Type = "Local Disk";
            IsExpanded = true;
            ImageSource = new Uri(@"Images\Harddrive.png", UriKind.RelativeOrAbsolute);
        }

        private ObservableCollection<FolderContentObjectData> _Children;
        public ObservableCollection<FolderContentObjectData> Children
        {
            get { return _Children ?? (_Children = GenerateChildren(_DriveInfo.RootDirectory, 1)); }
        }

        public override string ToString()
        {
            return string.Format("Drive: {0}", Name);
        }

        public bool HasItems
        {
            get { return DetermineHasChildren(_DriveInfo.RootDirectory); }
        }

        public IEnumerable GetEnumerable()
        {
            return Children;
        }
    }

    public class FileSystem : INotifyPropertyChanged
    {
        public IEnumerable<FolderData> RootDirectories
        {
            get
            {
                if (Project.CurrentProject == null)
                {
                    throw new Exception("No Project is opened");
                }
                else
                {
                    ObservableCollection<FolderData> directoryList = new ObservableCollection<FolderData>();
                    directoryList.Add(new FolderData(new DirectoryInfo(Project.CurrentProject.Directory + Project.ProjectFilesDirectory), 0));
                    return directoryList;
                }
            }
        }

        private ObservableCollection<object> _SelectedItems = new ObservableCollection<object>();
        public ObservableCollection<object> SelectedItems
        {
            get { return _SelectedItems; }
            set
            {
                _SelectedItems = value;
            }
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            var h = PropertyChanged;
            if (h != null)
                h(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }
}
