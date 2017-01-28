using MahApps.Metro.Controls;
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

using System.Collections.ObjectModel;

namespace FM3D_Designer.src.Dialogs
{
    /// <summary>
    /// Interaction logic for ChangeMeshDialog.xaml
    /// </summary>
    public partial class ChangeMeshDialog : DialogBase
    {
        public ObservableCollection<DesignerLib.FoundResource> Meshes { get; private set; }
        private DesignerLib.FoundResource res;

        public ChangeMeshDialog(MetroWindow window, DesignerLib.ExternResource res, DesignerLib.FoundResource fres) : base(window)
        {

            this.Meshes = new ObservableCollection<DesignerLib.FoundResource>();
            this.res = fres;

            foreach (var fr in res.Resources)
            {
                if (fr.ResType == DesignerLib.ResourceType.Mesh)
                {
                    this.Meshes.Add(fr);
                }
            }
            Meshes.Remove(fres);

            InitializeComponent();

            this.grid.DataContext = this;
        }

        private bool CanAccept
        {
            get
            {
                return list.SelectedIndex != -1;
            }
        }

        private void Button_Accept(object sender, RoutedEventArgs e)
        {
            var mesh = this.Meshes[this.list.SelectedIndex];
            this.res.Parent.Content.Remove(this.res);
            mesh.Content.Add(this.res);
            this.Close();
        }

        private void Button_Cancel(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }

    [ValueConversion(typeof(int), typeof(bool))]
    public class IntUnequalToBoolConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            int param;
            if (parameter is int) param = (int)parameter;
            else if (parameter is string) param = System.Convert.ToInt32((string)parameter);
            else throw new ArgumentException();

            return ((int)value) != param;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}
