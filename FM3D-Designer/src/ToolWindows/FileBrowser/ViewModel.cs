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

namespace FM3D_Designer.ToolWindows.FileBrowser
{
    public class TreeItemViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private FileSystemObjectData objectData;

        public TreeItemViewModel(FileSystemObjectData objectData)
        {
            this.objectData = objectData;

            if(this.objectData.State == FileState.NOT_FOUND)
            {
                this.ExtraImageSource = new Uri("/FM3D-Designer;component/resources/images/warning.png", UriKind.Relative);
            }
            if(this.objectData.State == FileState.NOT_PROJECT)
            {
                if(this.objectData.FileType == FileType.DIRECTORY)
                {
                    this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_nonproj_icon.ico", UriKind.Relative);
                } else
                {
                    this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/file_nonproj_icon.ico", UriKind.Relative);
                }
            } else
            {
                switch (this.objectData.FileType)
                {
                    case FileType.DIRECTORY:
                        this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/folder_closed_icon.ico", UriKind.Relative);
                        break;
                    default:
                        this.ImageSource = new Uri("/FM3D-Designer;component/resources/images/file browser/file_icon.ico", UriKind.Relative);
                        break;
                }
            }
            _Children = new ObservableCollection<TreeItemViewModel>();
            foreach(FileSystemObjectData f in objectData.Children)
            {
                _Children.Add(new TreeItemViewModel(f));
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
                    if(PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("ImageSource"));
                }
            }
        }

        private ObservableCollection<TreeItemViewModel> _Children;
        public IList<TreeItemViewModel> Children
        {
            get
            {
                return _Children; 
            }
        }
    }
    public class ViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private Model model = new Model();

        #region Commands
        private Command commIcons;
        public ICommand CommIcons
        {
            get
            {
                return commIcons;
            }
        }
        private Command commTreeIcons;
        public ICommand CommTreeIcons
        {
            get
            {
                return commTreeIcons;
            }
        }
        private Command commTree;
        public ICommand CommTree
        {
            get
            {
                return commTree;
            }
        }
        #endregion

        public ViewModel()
        {
            model.PropertyChanged += OnDirectoryChanched;

            commIcons = new Command(this.ExecuteIcons, this.CanExecuteIcons);
            commTreeIcons = new Command(this.ExecuteTreeIcons, this.CanExecuteTreeIcons);
            commTree = new Command(this.ExecuteTree, this.CanExecuteTree);

            _RootDirectories = new ObservableCollection<TreeItemViewModel>();
            foreach (FileSystemObjectData f in model.RootDirectories)
            {
                _RootDirectories.Add(new TreeItemViewModel(f));
            }

            ExecuteTree();
        }

        #region TreeModes
        public bool ModeIcons
        {
            get
            {
                return model.Mode == Model.ViewMode.ICONS;
            }
        }

        public bool ModeTreeIcons
        {
            get
            {
                return model.Mode == Model.ViewMode.TREE_ICONS;
            }
        }

        public bool ModeTree
        {
            get
            {
                return model.Mode == Model.ViewMode.TREE;
            }
        }

        private bool CanExecuteIcons()
        {
            return model.Mode != Model.ViewMode.ICONS;
        }

        private bool CanExecuteTreeIcons()
        {
            return model.Mode != Model.ViewMode.TREE_ICONS;
        }

        private bool CanExecuteTree()
        {
            return model.Mode != Model.ViewMode.TREE;
        }

        private void ExecuteIcons()
        {
            model.Mode = Model.ViewMode.ICONS;
            UpdateMode();
        }

        private void ExecuteTreeIcons()
        {
            model.Mode = Model.ViewMode.TREE_ICONS;
            UpdateMode();
        }

        private void ExecuteTree()
        {
            model.Mode = Model.ViewMode.TREE;
            UpdateMode();
        }

        public void UpdateMode()
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs("ModeIcons"));
                PropertyChanged(this, new PropertyChangedEventArgs("ModeTreeIcons"));
                PropertyChanged(this, new PropertyChangedEventArgs("ModeTree"));
            }
            //commIcons.UpdateCanExecuteState();
        }

        #endregion

        private ObservableCollection<TreeItemViewModel> _RootDirectories;
        public IEnumerable<TreeItemViewModel> RootDirectories
        {
            get
            {
                return _RootDirectories;
            }
        }

        void OnDirectoryChanched(object sender, PropertyChangedEventArgs args)
        {
            if(args.PropertyName.Equals(nameof(model.RootDirectories), StringComparison.Ordinal))
            {
                MessageBox.Show("CHANGED D:");
            }
        }
    }
}
