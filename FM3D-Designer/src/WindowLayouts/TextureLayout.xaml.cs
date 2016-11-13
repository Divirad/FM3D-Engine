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
using System.IO;

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for TextureLayout.xaml
    /// </summary>
    public partial class TextureLayout : WindowLayout
    {
        public TextureLayout()
        {
            InitializeComponent();

            this.Header = "Texture";
            this.Initialize(mainWindow, null);

            int x, y;

            byte[] imageData = ExternFileLoader.LoadTexture("../../resources/images/logofm3d.png", out x, out y);

            BitmapSource bitmapSource = BitmapSource.Create(x, y, 300, 300, PixelFormats.Bgra32, BitmapPalettes.Gray256, imageData, x * 4);


            Image image = new Image();
            image.Source = bitmapSource;

            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new DocumentWindows.TextureViewPort(this, image));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Right);
            DockSite.SetDockSize(splitPanel, 150);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }
    }
}
