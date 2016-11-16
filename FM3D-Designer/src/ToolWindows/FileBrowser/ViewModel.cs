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

namespace FM3D_Designer.src.ToolWindows.FileBrowser
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

        private Visibility _IsVisible = Visibility.Visible;
        public Visibility IsVisible
        {
            get
            {
                return _IsVisible;
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
        public enum ViewMode
        {
            ICONS,
            TREE_ICONS,
            TREE
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private Model model = new Model();
        public ViewMode Mode
        {
            set
            {
                model.Mode = value;
            }
            get
            {
                return model.Mode;
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
        #endregion

        public ViewModel()
        {
            model.PropertyChanged += OnDirectoryChanged;

            _CommTreeMode = new CommandTreeMode(this);

            _RootDirectories = new ObservableCollection<TreeItemViewModel>();
            foreach (FileSystemObjectData f in model.RootDirectories)
            {
                _RootDirectories.Add(new TreeItemViewModel(f));
            }
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

        private ObservableCollection<TreeItemViewModel> _RootDirectories;
        public IEnumerable<TreeItemViewModel> RootDirectories
        {
            get
            {
                return _RootDirectories;
            }
        }

        void OnDirectoryChanged(object sender, PropertyChangedEventArgs args)
        {
            if(args.PropertyName.Equals(nameof(model.RootDirectories), StringComparison.Ordinal))
            {
                MessageBox.Show("CHANGED D:");
            }
        }
    }
}
