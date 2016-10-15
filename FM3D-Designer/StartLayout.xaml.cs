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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace FM3D_Designer
{
    /// <summary>
    /// Interaction logic for StartLayout.xaml
    /// </summary>
    public partial class StartLayout : WindowLayout
    {
        public StartLayout(MainWindow mainWindow)
        {
            InitializeComponent();

            //Initialize DockWindow
            this.Header = "StartPage";

            this.Initialize(mainWindow, null);
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            mainWindow.ClearAttachedWindows();

            Project.Load(this.textBox.Text);

            mainWindow.AttachNewWindowLayout(new MainLayout(this.mainWindow), true);

        }

        private void testButton_Click(object sender, RoutedEventArgs e)
        {
            //this.textBox.Text = "C:\\Users\\Dyrax\\Desktop\\TestProject\\Test.project";
        }
    }
}
