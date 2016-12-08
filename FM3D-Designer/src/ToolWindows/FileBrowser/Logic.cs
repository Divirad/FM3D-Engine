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

            this._Mode = ViewMode.TREE;
            UpdateGrid();

            RootDirectories = new ObservableCollection<Item>();
            var folder = Project.CurrentProject.ProjectFiles;
            RootDirectories.Add(Creator.CreateItem(new DirectoryInfo(folder.Path), folder, Item.ItemState.NORMAL, null, this));
        }

        #region Directories
        public ObservableCollection<Item> RootDirectories { get; private set; }
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

        #region NotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name)
        {
            if (this.PropertyChanged != null) this.PropertyChanged(this, new PropertyChangedEventArgs(name));
        }
        #endregion
    }
}
