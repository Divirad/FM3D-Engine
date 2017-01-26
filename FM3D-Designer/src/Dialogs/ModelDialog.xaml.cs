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
    public partial class ModelDialog : DialogBase, IResourceContainer
    {
        public ModelDialog(MetroWindow window, String path) : base(window)
        {
            InitializeComponent();

            ExternResource res = this.Resources["res"] as ExternResource;
            res.Master = this;
            res.Load(path);
        }

        public void OnRemove(FoundResource A_0)
        {
            ExternResource res = this.Resources["res"] as ExternResource;
            res.Resources.Remove(A_0);
        }

        public void OnDelete(FoundResource A_0)
        {
            ExternResource res = this.Resources["res"] as ExternResource;
            res.Resources.Remove(A_0);
        }

        public void OnChangeMesh(FoundResource A_0)
        {
            MainWindow.Instance.ShowChangeMeshDialog(this.Resources["res"] as ExternResource, A_0);
        }

        private void Button_Mesh(object sender, RoutedEventArgs e)
        {
            ExternResource res = this.Resources["res"] as ExternResource;
            res.Resources.Add(new FoundResource("New Mesh", "Path", ResourceType.Mesh, res));
        }

        private void Button_Accept(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void Button_Cancel(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }

    [ValueConversion(typeof(ResourceType), typeof(string))]
    public class ModelDialogIconConverter: IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            
            string s =  "/FM3D-Designer;component/resources/images/ModelDialog/" + Enum.GetName(typeof(ResourceType), value) + "_icon.png";
            return s;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }

    [ValueConversion(typeof(ResourceType), typeof(Visibility))]
    public class MeshTypeConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return ((ResourceType)value) == ((ResourceType)parameter) ? Visibility.Visible : Visibility.Collapsed;       
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}
