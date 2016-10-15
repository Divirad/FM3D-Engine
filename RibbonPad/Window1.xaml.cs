using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using DevComponents.WpfRibbon;
using DevComponents.WpfDock;
using System.Collections.ObjectModel;


namespace RibbonPad
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>

    public partial class Window1 : DevComponents.WpfRibbon.RibbonWindow
    {
        public Window1()
        {
            InitializeComponent();

            // This gives us styling for default system resources like Scroll-Bars etc. 
            DevComponents.WPF.Controls.VisualStyleManager.ApplicationVisualStyle = DevComponents.WPF.Controls.VisualStyle.Office2016Colorful;

            // Connect an existing command to the extender so the shared properties can be propagated.
            // See http://www.devcomponents.com/kb2/?p=562 for details
            RibbonCommandManager.Connect(ApplicationCommands.Open, new ButtonDropDownCommandExtender("Open", "/images/FolderOpen32.png"));
            RibbonCommandManager.Connect(ApplicationCommands.New, new ButtonDropDownCommandExtender("New", "/images/Document32.png", "/images/NewDocument.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Close, new ButtonDropDownCommandExtender("Exit RibbonPad", "/images/Exit.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Paste, new ButtonDropDownCommandExtender("Paste", "/images/Paste32.png", "/images/Paste16.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Cut, new ButtonDropDownCommandExtender("Cut", "/images/Cut.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Copy, new ButtonDropDownCommandExtender("Copy", "/images/Copy.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Save, new ButtonDropDownCommandExtender("Save", "/images/Save32.png", "/images/Save.png"));
            RibbonCommandManager.Connect(ApplicationCommands.SaveAs, new ButtonDropDownCommandExtender("Save As...", "/images/SaveAs32.png", "/images/SaveAs16.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Print, new ButtonDropDownCommandExtender("Print...", "/images/Print32.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Properties, new ButtonDropDownCommandExtender("Options", "/images/Options.png"));

            // Create command bindings for some commands
            this.CommandBindings.Add(new CommandBinding(MyCommands.MostRecentlyUsed, MostRecentlyUsedCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.CloseDocument, CloseDocumentCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.Options, CloseDocumentCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Close, CloseCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Open, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.New, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Save, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.SaveAs, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Print, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.Office2010SilverTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.Office2010BlueTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.Office2010BlackTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.Office2013Theme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.BlueTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.BlackTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.SilverTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.OrangeTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.MagentaTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.GreenTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.DarkBlueTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.HelpBackstage, HelpCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.HelpContact, HelpCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.HelpKB, HelpCommandExecute));
        }

        #region Command Execution
        private void HelpCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            ICommand command = e.Command;
            if (command == MyCommands.HelpBackstage)
            {
                System.Diagnostics.Process.Start("http://www.devcomponents.com/kb2/?p=861");
            }
            else if (command == MyCommands.HelpContact)
            {
                System.Diagnostics.Process.Start("http://www.devcomponents.com/support.aspx");
            }
            else if (command == MyCommands.HelpKB)
            {
                System.Diagnostics.Process.Start("http://www.devcomponents.com/kb2/");
            }

            // Close backstage menu
            AppMenu.IsPopupOpen = false;
        }

        private bool m_CustomColor = false;

        private void MostRecentlyUsedCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            LogAction("Most recently used command executed for '" + e.Parameter.ToString() + "'");
        }

        private void CloseCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            this.Close();
        }

        private void CloseDocumentCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            LogAction("Close active document command executed...");
        }

        private void AppCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            if(e.Command is RoutedUICommand)
                LogAction(((RoutedUICommand)e.Command).Text + " command executed...");
            else if(e.Command is RoutedCommand)
                LogAction(((RoutedCommand)e.Command).Name + " command executed...");
        }

        private void CanExecuteChangeRibbonColor(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            IButtonCommandParameter param = e.Parameter as IButtonCommandParameter;
            if (param == null) return;

            if (e.Command == MyCommands.Office2013Theme)
            {
                param.IsChecked = !m_CustomColor && (AppRibbon.EffectiveStyle == eEffectiveStyle.Office2013);
                param.ValueChanged = true;
            }
            else if (e.Command == MyCommands.BlackTheme)
            {
                param.IsChecked = !m_CustomColor && (AppRibbon.VisualStyle == eRibbonVisualStyle.Office2007Black);
                param.ValueChanged = true;
            }
            else if (e.Command == MyCommands.SilverTheme)
            {
                param.IsChecked = !m_CustomColor && (AppRibbon.VisualStyle == eRibbonVisualStyle.Office2007Silver);
                param.ValueChanged = true;
            }
            else if (e.Command == MyCommands.BlueTheme)
            {
                param.IsChecked = !m_CustomColor && (AppRibbon.VisualStyle == eRibbonVisualStyle.Office2007Blue);
                param.ValueChanged = true;
            }
            else if (e.Command == MyCommands.Office2010SilverTheme)
            {
                param.IsChecked = !m_CustomColor && (AppRibbon.VisualStyle == eRibbonVisualStyle.Office2010Silver);
                param.ValueChanged = true;
            }
            else if (e.Command == MyCommands.Office2010BlueTheme)
            {
                param.IsChecked = !m_CustomColor && (AppRibbon.VisualStyle == eRibbonVisualStyle.Office2010Blue);
                param.ValueChanged = true;
            }
        }

        private void ChangeRibbonColor(object sender, ExecutedRoutedEventArgs e)
        {
            ICommand cmd = e.Command;

            if (cmd == MyCommands.Office2013Theme)
            {
                ChangeColors(eRibbonVisualStyle.Office2013LightGray, DevComponents.WpfDock.eDockVisualStyle.Office2013LightGray, Colors.Transparent);
            }
            else if (cmd == MyCommands.Office2010SilverTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2010Silver, DevComponents.WpfDock.eDockVisualStyle.Office2010Silver, Colors.Transparent);
            }
            else if (cmd == MyCommands.Office2010BlueTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2010Blue, DevComponents.WpfDock.eDockVisualStyle.Office2010Blue, Colors.Transparent);
            }
            else if (cmd == MyCommands.Office2010BlackTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2010Black, DevComponents.WpfDock.eDockVisualStyle.Office2010Black, Colors.Transparent);
            }
            else if (cmd == MyCommands.BlueTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Blue, DevComponents.WpfDock.eDockVisualStyle.Office2007Blue, Colors.Transparent);
            }
            else if (cmd == MyCommands.SilverTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Silver, DevComponents.WpfDock.eDockVisualStyle.Office2007Silver, Colors.Transparent);
            }
            else if (cmd == MyCommands.BlackTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Black, DevComponents.WpfDock.eDockVisualStyle.Office2007Black, Colors.Transparent);
            }
            // Custom Colors...
            else if (cmd == MyCommands.OrangeTheme)
            {
                // Note that you can use any built-in color table as base table any any color as base color
                ChangeColors(eRibbonVisualStyle.Office2013, DevComponents.WpfDock.eDockVisualStyle.Office2013, Color.FromRgb(0xD2, 0x47, 0x26));
            } 
            else if (cmd == MyCommands.MagentaTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2013, DevComponents.WpfDock.eDockVisualStyle.Office2013, Color.FromRgb(0x80, 0x39, 0x7B));
            }
            else if (cmd == MyCommands.GreenTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2013, DevComponents.WpfDock.eDockVisualStyle.Office2013, Color.FromRgb(0x21, 0x73, 0x46));
            }
            else if (cmd == MyCommands.DarkBlueTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2013, DevComponents.WpfDock.eDockVisualStyle.Office2013, Color.FromRgb(0x00, 0x72, 0xC6));
            }
        }

        private void ChangeColors(eRibbonVisualStyle ribbonColor, DevComponents.WpfDock.eDockVisualStyle dockColor, Color customBaseColor)
        {
            AppRibbon.VisualStyle = ribbonColor;
            AppDock.VisualStyle = dockColor;
            m_CustomColor = (customBaseColor != Colors.Transparent);
            if (m_CustomColor)
            {
                AppRibbon.ChangeColorScheme(ribbonColor, customBaseColor);
                AppDock.ChangeColorScheme(dockColor, customBaseColor);
            }
            else
            {
                AppRibbon.ChangeColorScheme(ribbonColor);
                AppDock.ChangeColorScheme(dockColor);
            }

            // Disable backstage application menu for Office 2007 style
            this.AppMenu.BackstageEnabled = AppRibbon.EffectiveStyle != eEffectiveStyle.Office2007;

            if (AppRibbon.EffectiveStyle == eEffectiveStyle.Office2010 || AppRibbon.EffectiveStyle == eEffectiveStyle.Office2013)
            {
                ((Image)AppMenu.Image).Visibility = Visibility.Collapsed;
            }
            else
            {
                ((Image)AppMenu.Image).Visibility = Visibility.Visible;
            }
        }

        private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
        {
            document1.FocusContent();
        }
        #endregion

        #region Direct Event Handling
        private void DialogLauncherClicked(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Dialog Launcher Clicked.");
        }

        private void NavigateHyperlink(object sender, RoutedEventArgs e)
        {
            Hyperlink link = e.OriginalSource as Hyperlink;
            System.Diagnostics.Process.Start(link.NavigateUri.AbsoluteUri);
        }
        private void ShowOffice2007Window(object sender, RoutedEventArgs e)
        {
            AdvWindow w = new AdvWindow();
            w.Title = "Office 2007 Style Window";
            w.Width = 300;
            w.Height = 300;
            w.Show();
        }
        private void ShowCustomStyleWindow(object sender, RoutedEventArgs e)
        {
            Window3 w = new Window3();
            w.Show();
        }
        #endregion

        #region Dock Window Support
        private string m_Layout = "";
        private void SaveDockLayout(object sender, RoutedEventArgs e)
        {
            m_Layout = AppDock.Layout;
            StatusItem1.Content = "Docking Layout Saved.";
        }
        private void LoadDockLayout(object sender, RoutedEventArgs e)
        {
            if (m_Layout.Length > 0)
                AppDock.Layout = m_Layout;
            else
                MessageBox.Show("Click Save to save docking layout, then rearrange the windows and load it by clicking Load.");
        }

        private void DockWindowActivated(object sender, RoutedEventArgs e)
        {
            LogAction(AppDock.ActiveDockWindow.Header.ToString() + " Activated");
        }

        private void DockWindowDeactivated(object sender, RoutedEventArgs e)
        {
            DockWindow dw=e.OriginalSource as DockWindow;
            LogAction(dw.Header.ToString()+" Deactivated");
        }

        private void DockWindowClosing(object sender, CancelSourceRoutedEventArgs e)
        {
            // Occurs before DockWindow is closed and you can cancel the closing of the window
            DockWindow dw = e.OriginalSource as DockWindow;
            LogAction(dw.Header.ToString() + " Closing");
        }

        private void DockWindowClosed(object sender, RoutedEventArgs e)
        {
            DockWindow dw = e.OriginalSource as DockWindow;
            LogAction(dw.Header.ToString() + " Closed");
        }

        private void LogAction(string text)
        {
            FindResults1.AppendText(DateTime.Now.ToString() + ": " + text + Environment.NewLine);
            FindResults1.ScrollToEnd();
        }
        #endregion

    }

    #region Backstage Data
    public class SupportItems : ObservableCollection<FileItem>
    {
        public SupportItems()
            : base()
        {
            Add(new FileItem("Backstage", "How to build Office 2010 style Backstage with DotNetBar", "images/Globe.png", MyCommands.HelpBackstage));
            Add(new FileItem("DotNetBar Knowledge Base", "Browse our online Knowledge Base", "images/Help64.png", MyCommands.HelpKB));
            Add(new FileItem("Contact Us", "Let us know if you need help or how we can make DotNetBar even better", "images/ContactUs2.png", MyCommands.HelpContact));
        }
    }

    public class MruFolders : ObservableCollection<FileItem>
    {
        public MruFolders()
            : base()
        {
            Add(new FileItem("Documents", @"\\fileserver\Documents", "images/OpenExistingPlace.png"));
            Add(new FileItem("My Documents", @"\\fileserver\My Documents", "images/OpenExistingPlace.png"));
            Add(new FileItem("Transfer", @"\\droboshare\drobo\Transfer", "images/OpenExistingPlace.png"));
        }
    }

    public class DocTemplates : ObservableCollection<FileItem>
    {
        public DocTemplates()
            : base()
        {
            Add(new FileItem("Blank document", "", "images/DocTemplateNew.png"));
            Add(new FileItem("Blog post", "", "images/DocTemplateBlogPost.png"));
            Add(new FileItem("Recent templates", "", "images/DocTemplateRecent.png"));
            Add(new FileItem("Sample templates", "", "images/DocTemplateSamples.png"));
            Add(new FileItem("My templates", "", "images/DocTemplateMy.png"));
            Add(new FileItem("New from existing", "", "images/DocTemplateNewBasedOn.png"));
        }
    }

    public class MruFiles : ObservableCollection<FileItem>
    {
        public MruFiles()
            : base()
        {
            Add(new FileItem("Services Invoice 108.rtf", @"\\fileserver\Documents", "images/Document.png"));
            Add(new FileItem("Services Invoice 109.rtf", @"\\fileserver\Documents", "images/Document.png"));
            Add(new FileItem("Sales Report.rtf", @"\\fileserver\Documents", "images/Document.png"));
            Add(new FileItem("Marketing Draft.rtf", @"c:\My Documents", "images/Document.png"));
            Add(new FileItem("Compensation Report.rtf", @"c:\My Documents", "images/Document.png"));
            Add(new FileItem("Jim Review.rtf", @"c:\My Documents", "images/Document.png"));
            Add(new FileItem("Kathy Review.rtf", @"c:\My Documents", "images/Document.png"));
            Add(new FileItem("Invoice10201.rtf", @"c:\My Documents", "images/Document.png"));
            Add(new FileItem("Invoice10202.rtf", @"c:\My Documents", "images/Document.png"));
            Add(new FileItem("Invoice10203.rtf", @"c:\My Documents", "images/Document.png"));
        }
    }

    public class FileItem
    {
        private string _FileName;
        public string FileName
        {
            get { return _FileName; }
            set
            {
                _FileName = value;
            }
        }
        private string _Folder;
        public string Folder
        {
            get { return _Folder; }
            set
            {
                _Folder = value;
            }
        }

        private string _ImageSource;
        public string ImageSource
        {
            get { return _ImageSource; }
            set
            {
                _ImageSource = value;
            }
        }

        private ICommand _Command;
        public ICommand Command
        {
            get { return _Command; }
            set { _Command = value; }
        }
        
        public FileItem()
        {

        }

        /// <summary>
        /// Initializes a new instance of the MruItem class.
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="folder"></param>
        public FileItem(string fileName, string folder)
        {
            _FileName = fileName;
            _Folder = folder;
        }
        /// <summary>
        /// Initializes a new instance of the  type.
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="folder"></param>
        /// <param name="imageSource"></param>
        public FileItem(string fileName, string folder, string imageSource)
        {
            _FileName = fileName;
            _Folder = folder;
            _ImageSource = imageSource;
        }

        /// <summary>
        /// Initializes a new instance of the FileItem class.
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="folder"></param>
        /// <param name="imageSource"></param>
        /// <param name="command"></param>
        public FileItem(string fileName, string folder, string imageSource, ICommand command)
        {
            _FileName = fileName;
            _Folder = folder;
            _ImageSource = imageSource;
            _Command = command;
        }

        /// <summary>
        /// Initializes a new instance of the FileItem class.
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="folder"></param>
        /// <param name="command"></param>
        public FileItem(string fileName, string folder, ICommand command)
        {
            _FileName = fileName;
            _Folder = folder;
            _Command = command;
        }
    }
    #endregion
}