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

using System.Text.RegularExpressions;

namespace FM3D_Designer.src.Dialogs
{
    /// <summary>
    /// Interaction logic for EntityEditor.xaml
    /// </summary>
    public partial class EntityEditor : DialogBase
    {
        public EntityEditor(MetroWindow window) : base(window)
        {
            InitializeComponent();
            InitializeComponentsInCB();
        }

        public void InitializeComponentsInCB()
        {
            cb_addcomp.Items.Add("Position");
            cb_addcomp.Items.Add("Size");
            cb_addcomp.Items.Add("Blahh");
            cb_addcomp.Items.Add("OtherStuff");

            cb_added.Items.Add("Size");
        }

        public void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            //http://stackoverflow.com/questions/1268552/how-do-i-get-a-textbox-to-only-accept-numeric-input-in-wpf
            //https://social.msdn.microsoft.com/Forums/vstudio/en-US/9180fdc0-8140-4515-ad18-a966430d68e2/creating-a-doublefloating-only-textbox-ragex-maybe?forum=wpf
            Regex regex = new Regex(@"^[0-9]*(?:\.[0-9]*)?$");
            //?$
            //Regex("[0-9]*[.][0-9]*[.][0-9]*")
            //e.Handled = regex.IsMatch(e.Text);
            if((string)cb_added.SelectedItem =="Size")
            {
                foreach (char ch in e.Text)
                {
                    if (!((Char.IsDigit(ch) || ch.Equals('.'))))
                    {
                        e.Handled = true;
                        break;
                    }

                }
            }
        }

        private void btn_cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void btn_add_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
