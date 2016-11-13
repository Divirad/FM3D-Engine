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

namespace FM3D_Designer.src.ToolWindows
{
    /// <summary>
    /// Interaction logic for TextureViewPort.xaml
    /// </summary>
    public partial class TextureViewPort : ToolWindow
    {
        public TextureViewPort(WindowLayout mainWindow, Image image)
        {
            InitializeComponent();

            this.Header = "View Port";
            this.Initialize(mainWindow);

            this.textureContainer.Content = image;
        }
    }
}
