using DevComponents.WPF.Controls;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Collections;
using System.Windows.Controls;
using MahApps.Metro.Controls;
using MahApps.Metro.Controls.Dialogs;

namespace FM3D_Designer.src.ToolWindows.FileBrowser
{
    public class TreeItemViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private FileSystemObjectData objectData;

        private ViewModel viewModel;

        private TreeItemViewModel parent;

        public TreeItemViewModel(ViewModel vm, FileSystemObjectData objectData, TreeItemViewModel parent)
        {
            this.viewModel = vm;
            this.objectData = objectData;
            this.parent = parent;

            //Set Image
            if (this.objectData.State == FileState.NOT_FOUND)
            {
                this.ExtraImageSource = new Uri("/FM3D-Designer;component/resources/images/warning.png", UriKind.Relative);
            }
            if (this.objectData.State == FileState.NOT_PROJECT)
            {
                if (this.objectData.FileType == FileType.DIRECTORY)
                {
                    this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_nonproj_icon.ico", UriKind.Relative);
                    this.BigImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_nonproj_icon.ico", UriKind.Relative);
                }
                else
                {
                    this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/file_nonproj_icon.ico", UriKind.Relative);
                    this.BigImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/file_nonproj_icon.ico", UriKind.Relative);
                }
            }
            else
            {
                switch (this.objectData.FileType)
                {
                    case FileType.DIRECTORY:
                        this.BigImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_bigIcon.png", UriKind.Relative);
                        this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_icon.ico", UriKind.Relative);
                        break;
                    default:
                        this.BigImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/file_bigIcon.png", UriKind.Relative);
                        this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/file_icon.ico", UriKind.Relative);
                        break;
                }
            }

            //Set Folder content
            _AllChildren = new ObservableCollection<TreeItemViewModel>();
            _DirectoryChildren = new ObservableCollection<TreeItemViewModel>();
            foreach (FileSystemObjectData f in objectData.Children)
            {
                var child = new TreeItemViewModel(viewModel, f, this);
                _AllChildren.Add(child);
                if (child.objectData.FileType == FileType.DIRECTORY)
                {
                    _DirectoryChildren.Add(child);
                }
            }

            //Context Menu
            {
                _ContextMenu = new ContextMenu();
                if (this.objectData.FileType == FileType.DIRECTORY)
                {
                    var add = new MenuItem();
                    add.Header = "Add";
                    add.Click += this.Menu_Add;
                    _ContextMenu.AddItem(add);
                }
                if (this.parent != null)
                {
                    var delete = new MenuItem();
                    delete.Header = "Delete";
                    delete.Click += this.Menu_Delete;
                    _ContextMenu.AddItem(delete);
                }

            }
        }

        public String Name
        {
            get
            {
                return objectData.Name;
            }
            set
            {
                objectData.Name = value;
                if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("Name"));
                if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("DisplayName"));
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
                    if (this.objectData.FileType == FileType.DIRECTORY)
                    {
                        if (this.objectData.State == FileState.NOT_PROJECT)
                        {
                            if (value)
                            {
                                this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_open_nonproj_icon.ico", UriKind.Relative);
                            }
                            else
                            {
                                this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_nonproj_icon.ico", UriKind.Relative);
                            }
                        }
                        else
                        {
                            if (value)
                            {
                                this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_open_icon.ico", UriKind.Relative);
                            }
                            else
                            {
                                this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_icon.ico", UriKind.Relative);
                            }
                        }
                    }

                    _IsExpanded = value;
                    if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("IsExpanded"));
                }
            }
        }

        private Uri _ExtraImageSource;
        public Uri ExtraImageSource
        {
            get
            {
                return _ExtraImageSource;
            }
            set
            {
                if (value != _ExtraImageSource)
                {
                    _ExtraImageSource = value;
                    if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("ExtraImageSource"));
                }
            }
        }

        private Uri _ImageSource;
        public Uri ImageSource
        {
            get
            {
                return _ImageSource;
            }
            set
            {
                if (value != _ImageSource)
                {
                    _ImageSource = value;
                    if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("ImageSource"));
                }
            }
        }

        private Uri _BigImageSource;
        public Uri BigImageSource
        {
            get
            {
                return _BigImageSource;
            }
            set
            {
                if (value != _BigImageSource)
                {
                    _BigImageSource = value;
                    if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("BigImageSource"));
                }
            }
        }

        private Visibility _IsVisible = Visibility.Visible;
        public Visibility IsVisible
        {
            get
            {
                return _IsVisible;
            }
        }

        private ObservableCollection<TreeItemViewModel> _AllChildren;
        public IList<TreeItemViewModel> AllChildren
        {
            get
            {
                return _AllChildren;
            }
        }

        private ObservableCollection<TreeItemViewModel> _DirectoryChildren;
        public IList<TreeItemViewModel> DirectoryChildren
        {
            get
            {
                return _DirectoryChildren;
            }
        }

        public IList<TreeItemViewModel> Children
        {
            get
            {
                switch (viewModel.Mode)
                {
                    case ViewModel.ViewMode.TREE:
                        return AllChildren;
                    case ViewModel.ViewMode.TREE_ICONS:
                        return DirectoryChildren;
                    case ViewModel.ViewMode.ICONS:
                        return new ObservableCollection<TreeItemViewModel>();
                    default:
                        throw new Exception("Unknown Mode State!");
                }
            }
        }

        public bool IsSelected
        {
            set
            {
                if (value)
                {
                    viewModel.UpdateSelected(this);
                }
            }
        }

        private ContextMenu _ContextMenu;
        public ContextMenu CMenu
        {
            get
            {
                return _ContextMenu;
            }
        }

        private void Menu_Add(object sender, System.EventArgs e)
        {
            //((MetroWindow)Application.Current.MainWindow).ShowDialog();
        }
        private async void Menu_Delete(object sender, System.EventArgs e)
        {
            var result = await ((MetroWindow)Application.Current.MainWindow).ShowMessageAsync("Deleeete", "This will delete the file/directory for ever!", MessageDialogStyle.AffirmativeAndNegative);
            if (result == MessageDialogResult.Affirmative)
            {
                //TODO: Delete file here
                if (parent != null)
                {
                    this.parent.AllChildren.Remove(this);
                    this.parent.objectData.Children.Remove(this.objectData);
                    if (this.parent.PropertyChanged != null) this.parent.PropertyChanged(this, new PropertyChangedEventArgs("Children"));
                }
            }
        }

        public void CollapseAll()
        {
            this.IsExpanded = false;
            foreach (var c in this.AllChildren)
            {
                c.CollapseAll();
            }
        }

        public void ExpandAll()
        {
            this.IsExpanded = true;
            foreach (var c in this.AllChildren)
            {
                c.ExpandAll();
            }
        }

        public void UpdateMode()
        {
            if (this.PropertyChanged != null) this.PropertyChanged(this, new PropertyChangedEventArgs("Children"));
            foreach (var c in this.AllChildren)
            {
                c.ExpandAll();
            }
        }
    }
    public class ViewModel : INotifyPropertyChanged
    {
        public enum ViewMode
        {
            ICONS,
            TREE_ICONS,
            TREE
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private Model model = new Model();
        private ViewMode _Mode;
        public ViewMode Mode
        {
            set
            {
                _Mode = value;
            }
            get
            {
                return _Mode;
            }
        }

        #region Commands
        public class CommandTreeMode : CommandBase
        {
            private ViewModel model;
            public CommandTreeMode(ViewModel model)
            {
                this.model = model;
            }
            public override bool CanExecute(object parameter)
            {
                return (ViewMode)parameter != model.Mode;
            }
            public override void Execute(object parameter)
            {
                model.Mode = (ViewMode)parameter;
                foreach (var r in model.RootDirectories)
                {
                    r.UpdateMode();
                }
                model.UpdateMode();
            }
        }
        private CommandTreeMode _CommTreeMode;
        public ICommand CommTreeMode
        {
            get
            {
                return _CommTreeMode;
            }
        }

        public class CommandCollapseAll : CommandBase
        {
            private ViewModel model;
            public CommandCollapseAll(ViewModel model)
            {
                this.model = model;
            }
            public override bool CanExecute(object parameter)
            {
                return true;
            }
            public override void Execute(object parameter)
            {
                foreach (var r in model.RootDirectories)
                {
                    r.CollapseAll();
                }
            }
        }
        private CommandCollapseAll _CommCollapseAll;
        public ICommand CommCollapseAll
        {
            get
            {
                return _CommCollapseAll;
            }
        }

        public class CommandRefresh : CommandBase
        {
            private ViewModel model;
            public CommandRefresh(ViewModel model)
            {
                this.model = model;
            }
            public override bool CanExecute(object parameter)
            {
                return true;
            }
            public override void Execute(object parameter)
            {
                model.Refresh();
            }
        }
        private CommandRefresh _CommRefresh;
        public ICommand CommRefresh
        {
            get
            {
                return _CommRefresh;
            }
        }
        #endregion

        public ViewModel()
        {
            model.PropertyChanged += OnDirectoryChanged;

            _CommTreeMode = new CommandTreeMode(this);
            _CommCollapseAll = new CommandCollapseAll(this);
            _CommRefresh = new CommandRefresh(this);

            this._Mode = ViewMode.TREE;
            UpdateMode();

            _RootDirectories = new ObservableCollection<TreeItemViewModel>();
            foreach (FileSystemObjectData f in model.RootDirectories)
            {
                _RootDirectories.Add(new TreeItemViewModel(this, f, null));
            }
        }

        public void UpdateMode()
        {
            switch(Mode)
            {
                case ViewMode.TREE:
                    _SplitterLength = new GridLength(0);
                    _TreeLength = new GridLength(1, GridUnitType.Star);
                    _ListLength = new GridLength(0);
                    break;
                case ViewMode.ICONS:
                    _SplitterLength = new GridLength(0);
                    _TreeLength = new GridLength(0);
                    _ListLength = new GridLength(1, GridUnitType.Star);
                    break;
                case ViewMode.TREE_ICONS:
                    _SplitterLength = new GridLength(5);
                    _TreeLength = new GridLength(1, GridUnitType.Star);
                    _ListLength = new GridLength(1, GridUnitType.Star);
                    break;
            }

            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs("TreeVisibility"));
                PropertyChanged(this, new PropertyChangedEventArgs("ListVisibility"));
                PropertyChanged(this, new PropertyChangedEventArgs("SplitterVisibility"));
                PropertyChanged(this, new PropertyChangedEventArgs("TreeLength"));
                PropertyChanged(this, new PropertyChangedEventArgs("ListLength"));
                PropertyChanged(this, new PropertyChangedEventArgs("SplitterLength"));
            }
            //commIcons.UpdateCanExecuteState();
        }

        private ObservableCollection<TreeItemViewModel> _RootDirectories;
        public IEnumerable<TreeItemViewModel> RootDirectories
        {
            get
            {
                return _RootDirectories;
            }
        }

        private TreeItemViewModel _CurrentDirectory;
        public IEnumerable<TreeItemViewModel> CurrentDirectory
        {
            get
            {
                if (_CurrentDirectory != null)
                    return _CurrentDirectory.AllChildren;
                else
                    return new ObservableCollection<TreeItemViewModel>();
            }
        }

        void OnDirectoryChanged(object sender, PropertyChangedEventArgs args)
        {
            if (args.PropertyName.Equals(nameof(model.RootDirectories), StringComparison.Ordinal))
            {
                MessageBox.Show("CHANGED D:");
            }
        }

        public void UpdateSelected(TreeItemViewModel item)
        {
            _CurrentDirectory = item;
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs("CurrentDirectory"));
        }

        public Visibility TreeVisibility
        {
            get
            {
                if (Mode == ViewMode.ICONS)
                {
                    return Visibility.Hidden;
                }
                else
                {
                    return Visibility.Visible;
                }
            }
        }

        public Visibility ListVisibility
        {
            get
            {
                if (Mode == ViewMode.TREE)
                {
                    return Visibility.Hidden;
                }
                else
                {
                    return Visibility.Visible;
                }
            }
        }

        private GridLength _SplitterLength;
        public GridLength SplitterLength
        {
            get
            {
                return _SplitterLength;
            }
        }

        private GridLength _TreeLength;
        public GridLength TreeLength
        {
            get
            {
                return _TreeLength;
            }
            set
            {
                _TreeLength = value;
            }
        }

        private GridLength _ListLength;
        public GridLength ListLength
        {
            get
            {
                return _ListLength;
            }
            set
            {
                _ListLength = value;
            }
        }

        public void Refresh()
        {
            this._RootDirectories.Clear();
            this._CurrentDirectory = null;

            model = null;
            model = new Model();
            model.PropertyChanged += OnDirectoryChanged;

            _RootDirectories = new ObservableCollection<TreeItemViewModel>();
            foreach (FileSystemObjectData f in model.RootDirectories)
            {
                _RootDirectories.Add(new TreeItemViewModel(this, f, null));
            }

            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs("RootDirectories"));
                PropertyChanged(this, new PropertyChangedEventArgs("CurrentDirectory"));
            }
        }
    }
}
