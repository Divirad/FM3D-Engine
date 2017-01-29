using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

using MahApps.Metro.Controls;
using MahApps.Metro.Controls.Dialogs;
using System.Windows;
using FM3D_Designer.src.Dialogs;
using System.IO;

namespace FM3D_Designer.src.ToolWindows.FileBrowser
{
    public static class ItemTypes
    {
        //Static Properties
        public static ItemType Directory { get; } = new ItemType("Directory", "",
            new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_icon.ico", UriKind.Relative),
            new Uri("/FM3D-Designer;component/resources/images/file browser/folder_bigIcon.png", UriKind.Relative),
            new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_nonproj_icon.ico", UriKind.Relative),
            new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_nonproj_icon.ico", UriKind.Relative),
            new Uri("/FM3D-Designer;component/resources/images/file browser/folder_open_icon.ico", UriKind.Relative),
            new Uri("/FM3D-Designer;component/resources/images/file browser/folder_open_nonproj_icon.ico", UriKind.Relative));

        public static ItemType UnknownFile { get; } = new ItemType("Unknown File", "",
            new Uri("/FM3D-Designer;component/resources/images/file browser/file_icon.ico", UriKind.Relative),
            new Uri("/FM3D-Designer;component/resources/images/file browser/file_bigIcon.png", UriKind.Relative));

        public static Dictionary<string, ItemType> FileTypes { get; } = new Dictionary<string, ItemType>();
    }

    public class ItemType
    {
        //Static fields
        public static Uri NotFoundImageSource { get; }
            = new Uri("/FM3D-Designer;component/resources/images/warning.png", UriKind.Relative);
        private static Uri StandardNotProjectImage { get; }
            = new Uri("/FM3D-Designer;component/resources/images/file browser/file_nonproj_icon.ico", UriKind.Relative);
        private static Uri StandardNotProjectBigImage { get; } 
            = new Uri("/FM3D-Designer;component/resources/images/file browser/file_nonproj_icon.ico", UriKind.Relative);

        //Fields
        private readonly string name;
        private readonly string extension;

        //Properties
        public Uri ImageSource { get; private set; }
        public Uri ExpandedImageSource { get; private set; }
        public Uri BigImageSource { get; private set; }

        public Uri NotProjectImageSource { get; private set; }
        public Uri NotProjectExpandedImageSource { get; private set; }
        public Uri NotProjectBigImageSource { get; private set; }

        //Constructors
        public ItemType(string name, string extension, Uri imageSource, Uri bigImageSource, Uri notProjectImageSource,
            Uri notProjectBigImageSource, Uri expandedImageSource = null, Uri notProjectExpandedImageSource = null)
        {
            this.name = name;
            this.extension = extension;

            this.ImageSource = imageSource;
            this.ExpandedImageSource = expandedImageSource;
            this.BigImageSource = bigImageSource;

            this.NotProjectImageSource = notProjectImageSource;
            this.NotProjectExpandedImageSource = notProjectExpandedImageSource;
            this.NotProjectBigImageSource = notProjectBigImageSource;

            if(this.extension != "")
            {
                ItemTypes.FileTypes.Add(this.extension, this);
            }
        }

        public ItemType(string name, string extension, Uri imageSource, Uri bigImageSource)
        {
            this.name = name;
            this.extension = extension;

            this.ImageSource = imageSource;
            this.ExpandedImageSource = null;
            this.BigImageSource = bigImageSource;

            this.NotProjectImageSource = StandardNotProjectImage;
            this.NotProjectExpandedImageSource = null;
            this.NotProjectBigImageSource = StandardNotProjectBigImage;

            if (this.extension != "")
            {
                ItemTypes.FileTypes.Add(this.extension, this);
            }
        }

        //Methods
        public override string ToString()
        {
            return name;
        }
    }

    public class Item : INotifyPropertyChanged
    {
        //Types
        public enum ItemState
        {
            NORMAL,
            NOT_FOUND,
            NOT_PROJECT
        }

        public Logic logic { get; private set; }
        public ItemType type { get; private set; }

        public string Path { get; private set; }

        private Project.FileObject fileObject;

        //Constructor
        public Item(Item parent, Logic logic, ItemType type, string name, string path, ItemState state, Project.FileObject fileObject)
        {
            this.Parent = parent;
            this.logic = logic;
            this.type = type;
            this._Name = name;
            this._State = state;
            this.Path = path;
            this.fileObject = fileObject;
        }

        //Properties and Methods
        #region Basic Properties
        private ItemState _State;
        public ItemState State
        {
            get
            {
                return _State;
            }
            set
            {
                if(value != _State)
                {
                    _State = value;
                    OnPropertyChanged("State");
                    OnPropertyChanged("ImageSource");
                    OnPropertyChanged("BigImageSource");
                    OnPropertyChanged("ExtraImageSource");
                }
            }
        }
        private string _Name;
        public string Name
        {
            get
            {
                return _Name;
            }
            set
            {
                if (value != _Name)
                {
                    _Name = value;
                    OnPropertyChanged("Name");
                }
            }
        }

        private bool _IsSelected = false;
        public bool IsSelected
        {
            get
            {
                return _IsSelected;
            }
            set
            {
                if (value != _IsSelected)
                {
                    logic.CurrentDirectory = this;
                    _IsSelected = value;
                    OnPropertyChanged("IsSelected");
                }
            }
        }

        private bool _IsExpanded = false;
        public bool IsExpanded
        {
            get
            {
                return _IsExpanded;
            }
            set
            {
                if(value != _IsExpanded)
                {
                    _IsExpanded = value;
                    OnPropertyChanged("IsExpanded");
                    OnPropertyChanged("ImageSource");
                }
            }
        }
        #endregion

        #region Context Menu
        
        public ContextMenu CMenu
        {
            get
            {
                var menu = new ContextMenu();

                if (this.type == ItemTypes.Directory)
                {
                    var menu_add = new MenuItem();
                    var menu_res = new MenuItem();
                    var menu_adde = new MenuItem();

                    menu_add.Header = "Add File";
                    menu_add.Click += OnAddNewFile;

                    menu_adde.Header = "Add Entity";
                    menu_adde.Click += OnEntityEditorNew;

                    menu_res.Header = "New Resource";
                    menu_res.Click += OnNewResource;


                    menu.Items.Add(menu_add);
                    menu.Items.Add(menu_res);
                    menu.Items.Add(menu_adde);
                }
                else
                {
                    var menu_ee = new MenuItem();
                    menu_ee.Header = "Edit Entity";
                    menu_ee.Click += OnEntityEditor;
                    menu.Items.Add(menu_ee);
                }

                return menu;
            }
        }
        private void OnNewResource(object sender, EventArgs args)
        {
            var window = Application.Current.MainWindow as MetroWindow;
            window.ShowNewResourceDialog();
        }

        private void OnEntityEditor(object sender, EventArgs args)
        {
            var window = Application.Current.MainWindow as MetroWindow;
            window.ShowEntityEditor(false, "D:/entity.ent");
        }

        private async void OnEntityEditorNew(object sender, EventArgs args)
        {
            var window = Application.Current.MainWindow as MetroWindow;
            string x = await window.ShowInputAsync("New Entity!", "Give your Entity a fancy name!\nLike Pumuckel, Mister Eder... Or Something like that...\n");
            if (!x.Contains(".ent")) { x += ".ent"; }
            Item i;
            CreateFile(x, ItemTypes.UnknownFile, out i);
        }

        private async void OnAddNewFile(object sender, EventArgs args)
        {
            var window = Application.Current.MainWindow as MetroWindow;
            string x = await window.ShowInputAsync("New File!", "Give your file a fancy name!");
            if (!x.Contains(".")) { x += ".txt"; }
            Item i;
            CreateFile(x, ItemTypes.UnknownFile, out i);
        }

        #endregion

        #region Parent
        public Item Parent { get; private set; }
        public bool IsRootItem
        {
            get
            {
                return Parent != null;
            }
        }
        #endregion

        #region Children
        public ObservableCollection<Item> AllChildren { get; private set; } = new ObservableCollection<Item>();

        public ObservableCollection<Item> DirectoryChildren { get; private set; } = new ObservableCollection<Item>();
        public ObservableCollection<Item> OnlyProjectAllChildren { get; private set; } = new ObservableCollection<Item>();

        public ObservableCollection<Item> OnlyProjectDirectoryChildren { get; private set; } = new ObservableCollection<Item>();

        public IList<Item> Children
        {
            get
            {
                switch (this.logic.Mode)
                {
                    case Logic.ViewMode.TREE:
                        return logic.ShowAllFiles ? AllChildren : OnlyProjectAllChildren;
                    case Logic.ViewMode.TREE_ICONS:
                        return logic.ShowAllFiles ? DirectoryChildren : OnlyProjectDirectoryChildren;
                    case Logic.ViewMode.ICONS:
                        return new ObservableCollection<Item>();
                    default:
                        throw new InvalidOperationException("Unknown Mode State!");
                }
            }
        }

        public IList<Item> ChildrenForList
        {
            get
            {
                return logic.ShowAllFiles ? AllChildren : OnlyProjectAllChildren;
            }
        }

        public void UpdateChildren()
        {
            OnPropertyChanged("ChildrenForList");
            OnPropertyChanged("Children");
            if(this.IsSelected)
                logic.UpdateCurrentDirectoryContent();
        }

        public void AddChildSilently(Item item)
        {
            this.AllChildren.Add(item);
            if(item.type == ItemTypes.Directory)
            {
                this.DirectoryChildren.Add(item);
                if (item.State != ItemState.NOT_PROJECT)
                    this.OnlyProjectDirectoryChildren.Add(item);
            }
            if (item.State != ItemState.NOT_PROJECT)
                this.OnlyProjectAllChildren.Add(item);
            UpdateChildren();
        }
        public void AddChild(Item item)
        {
            AddChildSilently(item);
            UpdateChildren();
        }

        private bool HasChilds()
        {
            if (logic.ShowAllFiles)
                return logic.Mode == Logic.ViewMode.TREE ? AllChildren.Count > 0 : DirectoryChildren.Count > 0;
            else
                return logic.Mode == Logic.ViewMode.TREE ? OnlyProjectAllChildren.Count > 0 : OnlyProjectDirectoryChildren.Count > 0;
        }
        #endregion

        #region ImageSource
        public Uri ExtraImageSource
        {
            get
            {
                return this.State == ItemState.NOT_FOUND ? ItemType.NotFoundImageSource : null;
            }
        }
        
        public Uri ImageSource
        {
            get
            {
                if (this.State == ItemState.NOT_PROJECT)
                    return IsExpanded && HasChilds() ? type.NotProjectExpandedImageSource : type.NotProjectImageSource;
                else
                    return IsExpanded && HasChilds() ? type.ExpandedImageSource : type.ImageSource;
            }
        }
        
        public Uri BigImageSource
        {
            get
            {
                return this.State == ItemState.NOT_PROJECT ? type.NotProjectBigImageSource : type.BigImageSource;
            }
        }
        #endregion

        public void CollapseAll()
        {
            this.IsExpanded = false;
            foreach(var i in AllChildren)
            {
                i.CollapseAll();
            }
        }

        public bool CreateFile(string name, ItemType type, out Item item, bool addToProject = true)
        {
            if (this.type != ItemTypes.Directory) throw new InvalidOperationException("Item is not a directory");
            if (name.Contains('/') || name.Contains('\\')) throw new ArgumentException("Name has to be the filename not the path", "name");
            if (this.State != ItemState.NORMAL) throw new InvalidOperationException("Itemstate must be normal");

            string path = this.Path + "/" + name;
            if (File.Exists(path))
            {
                MessageBox.Show("File already exists");
                item = null;
                return false;
            }
            try
            {
                File.Create(path);
            } catch(Exception e)
            {
                MessageBox.Show(e.Message);
                item = null;
                return false;
            }
            if(addToProject)
            {
               var dir = new Project.Directory(name, path);
                (this.fileObject as Project.Directory).Content.Add(dir);
                (this.fileObject as Project.Directory).SubDirectories.Add(dir);
                item = new Item(this, this.logic, type, name, path, ItemState.NORMAL, dir);
            }
            else item = new Item(this, this.logic, type, name, path, ItemState.NOT_PROJECT, null);
            this.AllChildren.Add(item);
            return true;
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