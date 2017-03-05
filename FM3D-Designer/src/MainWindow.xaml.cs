using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

using DevComponents.WpfDock;
using MahApps.Metro.Controls;
using System.ComponentModel;

///Hauptnamespace
/**
 * Alle Klassen liegen in diesem Namepsace
 * um eine Komplikation mit einer Klasse
 * aus einer externen Bibliothek zu verhindern
 */
namespace FM3D_Designer.src
{
    ///Hauptfenster
    /**
     * Ein fast leeres Fenster, enthält nur ein DockSite-Control,
     * um das docken von WindowLayouts zu ermöglichen. Der modern
     * aussehende style wird durch die Basisklasse MetroAppWindow
     * hervorgerufen.
     */
    public partial class MainWindow : MetroWindow, INotifyPropertyChanged
    {
        public static MainWindow Instance { get; private set; } = null;

        public VisualStudio visualStudio { get; private set; } = new VisualStudio();
        public Compiler compiler { get; private set; } = new Compiler();
																	//0, 122, 204)
		private Brush statusColor = new SolidColorBrush(Color.FromRgb(0, 122, 204));    //Standard blue
        public Brush StatusColor
        {
            get
            {
                return statusColor;
            }
            set
            {
                if (value != statusColor)
                {
                    statusColor = value;
                    OnPropertyChanged("StatusColor");
                }
            }
        }

        public MainWindow()
        {
            //Themes.DarkTheme.SetTheme();
            if (Instance != null) throw new InvalidOperationException("Already created Object of Singleton class MainWindow");
            
            InitializeComponent();
            AttachNewWindowLayout(new WindowLayouts.StartLayout(this));
            Instance = this;
        }
        ~MainWindow()
        {
            if (Instance == this) Instance = null;
        }
        public void AttachNewWindowLayout(WindowLayout layout, bool isSelected = false)
        {
            this.dockingGroup.Items.Add(layout);
            layout.IsSelected = isSelected;
            this.dockingGroup.UpdateVisibility();
        }

        public void ClearAttachedWindows()
        {
            this.dockingGroup.Items.Clear();
            this.dockingGroup.UpdateVisibility();
        }

        private void MetroWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            visualStudio.Close();
        }

        #region NotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name)
        {
            if (this.PropertyChanged != null) this.PropertyChanged(this, new PropertyChangedEventArgs(name));
        }
        #endregion
    }


    public static class CustomCommands {

        public static readonly RoutedUICommand Export = new RoutedUICommand
            (
                        "Export",
                        "Export",
                        typeof(MainWindow),
                        new InputGestureCollection()
                        {
                            new KeyGesture(Key.E, ModifierKeys.Control,"Strg+E")
                        }
                );

        public static readonly RoutedUICommand Compile = new RoutedUICommand
            (
                        "Compile",
                        "Compile",
                        typeof(MainWindow),
                        new InputGestureCollection()
                        {
                            new KeyGesture(Key.F5)
                        }
                );
        public static readonly RoutedUICommand Start = new RoutedUICommand
           (
                       "Start",
                       "Start",
                       typeof(MainWindow),
                       new InputGestureCollection()
                       {
                            new KeyGesture(Key.F6)
                       }
               );
        //Define more commands here, just like the commands above
    }

}
