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

using DesignerLib;
using MahApps.Metro.Controls.Dialogs;
using MahApps.Metro.Controls;

namespace FM3D_Designer.src.Dialogs
{
    /// <summary>
    /// Interaction logic for NewResourceDialog.xaml
    /// </summary>
    public partial class NewResourceDialog : BaseMetroDialog
    {
        private MetroWindow win;
        public NewResourceDialog(MetroWindow window, String path)
        {
            this.win = window;
            InitializeComponent();

            ExternResource res = this.Resources["res"] as ExternResource;
            res.Load(path);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            win.HideMetroDialogAsync(this);
        }

        public void cancel(object sender, RoutedEventArgs e)
        {
        }
    }
}
