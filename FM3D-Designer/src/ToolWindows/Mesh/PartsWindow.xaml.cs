using MahApps.Metro.Controls;
using MahApps.Metro.Controls.Dialogs;
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

namespace FM3D_Designer.src.ToolWindows.Mesh
{
    /// <summary>
    /// Interaction logic for PartsWindow.xaml
    /// </summary>
    public partial class PartsWindow : ToolWindow
    {
        DesignerLib.Mesh mesh;

        public PartsWindow(DesignerLib.Mesh mesh)
        {
            InitializeComponent();

            this.Parts.DataContext = mesh;
            this.mesh = mesh;
        }

        private void Parts_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            if(!this.Parts.Items.IsEmpty && this.Parts.SelectedIndex >= 0)
            {
                var menu = (sender as ListBox).ContextMenu;
                (menu.Items[0] as MenuItem).IsChecked = !this.SelectedPart.Visible;
            } else
            {
                e.Handled = true;
            }
        }

        private void Hide_Click(object sender, RoutedEventArgs e)
        {
            if (!this.Parts.Items.IsEmpty && this.Parts.SelectedIndex >= 0)
            {
                this.SelectedPart.SetVisibility(!this.SelectedPart.Visible);
            }
        }

        private async void Rename_Click(object sender, RoutedEventArgs e)
        {
            if (!this.Parts.Items.IsEmpty && this.Parts.SelectedIndex >= 0)
            {
                var window = System.Windows.Application.Current.MainWindow as MetroWindow;
                var name = await window.ShowInputAsync("Rename Mesh-Part", "Enter the new name of the Mesh-Part");
                this.SelectedPart.SetName(name);
            }
        }

        private async void Delete_Click(object sender, RoutedEventArgs e)
        {
            if (!this.Parts.Items.IsEmpty && this.Parts.SelectedIndex >= 0)
            {
                var window = System.Windows.Application.Current.MainWindow as MetroWindow;
                var delete = await window.ShowMessageAsync("Delete Mesh-Part", "This will delete the Mesh-Part with all data forever!", MessageDialogStyle.Affirmative);
                if(delete == MessageDialogResult.Affirmative)
                {
                    mesh.RemovePart(this.SelectedPart);
                }
            }
        }

        public DesignerLib.MeshPart SelectedPart
        {
            get
            {
                if (this.Parts.SelectedIndex >= 0)
                {
                    return this.mesh.Parts[this.Parts.SelectedIndex];
                }
                else return null;
            }
        }
    }
}
