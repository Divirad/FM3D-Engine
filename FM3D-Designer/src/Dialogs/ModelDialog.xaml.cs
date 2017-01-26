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
    public partial class ModelDialog : DialogBase
    {
        public ModelDialog(MetroWindow window, String path) : base(window)
        {
            InitializeComponent();

            ExternResource res = this.Resources["res"] as ExternResource;
            res.Load(path);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }

    [ValueConversion(typeof(FoundResource.Type), typeof(string))]
    public class ModelDialogIconConverter: IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            
            string s =  "/FM3D-Designer;component/resources/images/ModelDialog/" + Enum.GetName(typeof(FoundResource.Type), value) + "_icon.png";
            return s;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}
