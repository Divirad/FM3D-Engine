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
    public partial class NewResourceDialog : DialogBase
    {
        public NewResourceDialog(MetroWindow window) : base(window)
        {
            InitializeComponent();
            (this.Resources["logic"] as NewResourceLogic).Dialog = this;
        }

        public void Cancel(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}