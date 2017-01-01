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
using System.ComponentModel;

namespace FM3D_Designer.src.ToolWindows.TextEditor
{
    /// <summary>
    /// Interaktionslogik für TextEditor.xaml
    /// </summary>
    public partial class TextEditor : ToolWindow
    {
        public TextEditor(WindowLayout mainWindow)
        {
            InitializeComponent();
            this.Header = "Text Editor";
            this.Initialize(mainWindow);
        }

        public void KeyComplete(object sender, RoutedEventArgs e)
        {
           // Point point = new Point();
           // this.GetCaretPos(out point);
        }

        public void Open_Click()
        {
        }

    }
}
