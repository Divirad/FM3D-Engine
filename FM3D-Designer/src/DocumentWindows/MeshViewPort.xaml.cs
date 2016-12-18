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

namespace FM3D_Designer.src.DocumentWindows
{
    /// <summary>
    /// Interaction logic for MeshViewPort.xaml
    /// </summary>
    public partial class MeshViewPort : DocumentWindow
    {
        public MeshViewPort(WindowLayout mainWindow)
        {
            InitializeComponent();

            this.Header = "View Port";
            this.Initialize(mainWindow);
            
        }
    }
}
