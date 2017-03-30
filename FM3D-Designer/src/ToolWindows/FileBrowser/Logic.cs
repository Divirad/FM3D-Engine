using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace FM3D_Designer.src.ToolWindows.FileBrowser
{
    public class Logic : INotifyPropertyChanged
    {
        #region Mode
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
                if (value != _Mode)
                {
                    _Mode = value;
                    OnPropertyChanged("Mode");
                }
            }
        }

        public bool ShowAllFiles { get; private set; } = true;
        #endregion

        public Logic()
        {
            CommTreeMode = new Command(CommModeAction, CommModeCondition);
            CommCollapseAll = new Command(CommCollapseAllAction, CommCollapseAllCondition);
            CommRefresh = new Command(CommRefreshAction, CommRefreshCondition);
            CommDirUp = new Command(CommDirUpAction, CommDirUpCondition);

            this._Mode = ViewMode.TREE;
            UpdateGrid();

            RootDirectories = new ObservableCollection<Item>();
            var folder = Project.CurrentProject.ProjectFiles;
            RootDirectories.Add(Creator.CreateItem(new DirectoryInfo(folder.Path), folder, Item.ItemState.NORMAL, null, this));
        }

        #region Directories
        public ObservableCollection<Item> RootDirectories { get; private set; }

        public Item ListItem { get; set; }

        private Item _CurrentDirectory;
        public Item CurrentDirectory
        {
            get
            {
                return _CurrentDirectory;
            }
            set
            {
                if(value != _CurrentDirectory)
                {
                    _CurrentDirectory = value;
                    OnPropertyChanged("CurrentDirectory");
                    OnPropertyChanged("CurrentDirectoryContent");
                }
            }
        }

        public void OpenFile()
        {
            if(this.CurrentDirectory.type != ItemTypes.Directory && this.CurrentDirectory.State == Item.ItemState.NORMAL)
                this.CurrentDirectory.type.Open(this.CurrentDirectory);
        }

        public void OpenFile2()
        {
            if (this.ListItem.type != ItemTypes.Directory && this.ListItem.State == Item.ItemState.NORMAL)
                this.ListItem.type.Open(this.ListItem);
        }

        public void OpenDirectory()
        {
            if (this.ListItem != null && this.ListItem.type == ItemTypes.Directory)
            {
                this.CurrentDirectory = this.ListItem;
                this.CurrentDirectory.IsSelected = true;
            }

        }

        public IList<Item> CurrentDirectoryContent
        {
            get
            {
                return CurrentDirectory != null ? CurrentDirectory.ChildrenForList : new ObservableCollection<Item>();
            }
        }

        public void UpdateCurrentDirectoryContent()
        {
            OnPropertyChanged("CurrentDiretoryContent");
        }
        #endregion

        #region Commands
        private bool CommModeCondition(object parameter)
        {
            return (ViewMode)parameter != Mode;
        }
        private void CommModeAction(object parameter)
        {
            Mode = (ViewMode)parameter;
            foreach (var r in RootDirectories)
            {
                r.UpdateChildren();
            }
            UpdateGrid();
        }
        public Command CommTreeMode { get; private set; }

        private bool CommCollapseAllCondition(object parameter)
        {
            return true;
        }
        private void CommCollapseAllAction(object parameter)
        {
            foreach (var r in RootDirectories)
            {
                r.CollapseAll();
            }
        }
        public Command CommCollapseAll { get; private set; }

        private bool CommRefreshCondition(object parameter)
        {
            return true;
        }
        private void CommRefreshAction(object parameter)
        {
            Refresh();
        }
        public Command CommRefresh { get; private set; }

        private bool CommDirUpCondition(object parameter)
        {
            return this.Mode == ViewMode.ICONS;
        }
        private void CommDirUpAction(object parameter)
        {
            this.CurrentDirectory = this.CurrentDirectory.Parent;
            this.CurrentDirectory.IsSelected = true;
        }
        public Command CommDirUp { get; private set; }
        #endregion

        #region Grid, Tree, List
        public GridLength TreeLength { get; private set; }
        public GridLength ListLength { get; private set; }
        public GridLength SplitterLength { get; private set; }
        public Visibility TreeVisibility
        {
            get
            {
                return Mode == ViewMode.ICONS ? Visibility.Hidden : Visibility.Visible;
            }
        }

        public Visibility ListVisibility
        {
            get
            {
                return Mode == ViewMode.TREE ? Visibility.Hidden : Visibility.Visible;
            }
        }

        public void UpdateGrid()
        {
            switch (Mode)
            {
                case ViewMode.TREE:
                    SplitterLength = new GridLength(0);
                    TreeLength = new GridLength(1, GridUnitType.Star);
                    ListLength = new GridLength(0);
                    break;
                case ViewMode.ICONS:
                    SplitterLength = new GridLength(0);
                    TreeLength = new GridLength(0);
                    ListLength = new GridLength(1, GridUnitType.Star);
                    break;
                case ViewMode.TREE_ICONS:
                    SplitterLength = new GridLength(5);
                    TreeLength = new GridLength(1, GridUnitType.Star);
                    ListLength = new GridLength(1, GridUnitType.Star);
                    break;
            }

            OnPropertyChanged("TreeVisibility");
            OnPropertyChanged("ListVisibility");
            OnPropertyChanged("SplitterVisibility");
            OnPropertyChanged("TreeLength");
            OnPropertyChanged("ListLength");
            OnPropertyChanged("SplitterLength");
        }
        #endregion

        public void Refresh()
        {
            throw new NotImplementedException();
        }

        private Item CreateItems(Item root, ItemType type, string fname, string fullName, string[] dirs, string[] fullDirs, int i)
        {
            Item item = root;
            Item item2;
            Project.File f;
            Project.Directory d;
            //Create all directories
            for (;i < dirs.Length; i++)
            {
                (item.FileObject as Project.Directory).SubDirectories.Add(d = new Project.Directory(dirs[i], fullDirs[i]));
                item.AddChild(item2 = new FileBrowser.Item(item, this, ItemTypes.Directory, dirs[i], fullDirs[i], Item.ItemState.NORMAL, d));
                item = item2;
            }
            //Create file
            (item.FileObject as Project.Directory).Files.Add(f = new Project.File(fname));
            item.AddChild(item2 = new FileBrowser.Item(item, this, type, fname, fullName, Item.ItemState.NORMAL, f));
            return item2;
        }

        public Item CreateFile(string path, ItemType type)
        {
            var dirs = path.Split('/', '\\');
            var fname = dirs.Last();                //File name
            var fullName = Project.CurrentProject._Directory + path; //Complete file path
            Array.Resize(ref dirs, dirs.Length - 1); //Remove filename
            var fullDirs = new string[dirs.Length];
            fullDirs[0] = Project.CurrentProject._Directory + dirs[0];
            for (int x = 1; x < dirs.Length; x++)
            {
                fullDirs[x] = fullDirs[x - 1] + "/" + dirs[x];
            }

            int i = 0;
            Item d = (from it in RootDirectories where it.Name == dirs[i] select it).FirstOrDefault();
            if (d == null)
            {
                //New Root Directory
                Project.Directory dir = new Project.Directory(dirs[i], fullDirs[i]);
                Project.CurrentProject.ProjectFiles.SubDirectories.Add(dir);
                RootDirectories.Add(d = new Item(null, this, ItemTypes.Directory, dirs[i], fullDirs[i], Item.ItemState.NORMAL, dir));
            }
            i++;

            Directory.CreateDirectory(fullDirs.Last());
            File.Create(fullName)?.Close();

            //Go through all existing directories
            for (; i < dirs.Length; i++)
            {
                d.MakeStateNormal();
                Item d2 = (from it in d.DirectoryChildren where it.Name == dirs[i] select it).FirstOrDefault();
                if (d2 != null)
                {
                    d = d2;
                }
                else
                {
                    return CreateItems(d, type, fname, fullName, dirs, fullDirs, i);
                }
            }
            d.MakeStateNormal();
            //Create file
            var f = new Project.File(fname);
            (d.FileObject as Project.Directory).Files.Add(f);
            var result = new FileBrowser.Item(d, this, type, fname, fullName, Item.ItemState.NORMAL, f);
            d.AddChild(result);
            return result;
        }

        #region NotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name)
        {
            if (this.PropertyChanged != null) this.PropertyChanged(this, new PropertyChangedEventArgs(name));
        }
        #endregion
    }
}
