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
using MahApps.Metro.Controls.Dialogs;

namespace FM3D_Designer.src.ToolWindows.TextEditor
{
    /// <summary>
    /// Interaktionslogik für TextEditor.xaml
    /// </summary>
    public partial class TextEditor : ToolWindow
    {
        private string _path;
        public TextEditor(WindowLayout mainWindow, string path="")
        {
            InitializeComponent();
            this.Header = "Text Editor";
            this.Initialize(mainWindow);

            if (path != "") {
                rtb_text.Document.Blocks.Clear();
                rtb_text.Document.Blocks.Add(new Paragraph(new Run(System.IO.File.ReadAllText(path))));
                _path = path;
            }
        }

        public void KeyComplete(object sender, RoutedEventArgs e)
        {
           // Point point = new Point();
           // this.GetCaretPos(out point);
        }

        public void Open_Click()
        {
        }


        private async void CommandBinding_Executed(object sender, ExecutedRoutedEventArgs e) {
            string richText = new TextRange(rtb_text.Document.ContentStart, rtb_text.Document.ContentEnd).Text;

            if (System.IO.File.Exists(_path)) {
                System.IO.File.WriteAllText(_path, richText);
            } else {
                await MainWindow.Instance.ShowMessageAsync("Error", "File does not Exist....");
            }
        }
    }
}
