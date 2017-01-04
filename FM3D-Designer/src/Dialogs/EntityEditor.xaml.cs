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
    class Comp
    {
            public string component { get; set; }
            public string type { get; set; }
            public bool m_get { get; set; }
            public bool m_set { get; set; }
            public bool m_custom { get; set; }
            public bool m_const { get; set; }
            public bool m_standard { get; set; }

    }

public partial class EntityEditor : DialogBase
    {
        List<Comp> avaiabel = new List<Comp>();
        List<Comp> added = new List<Comp>();

        public EntityEditor(MetroWindow window) : base(window)
        {
            InitializeComponent();
            InitializeAvaiabel();

            

        }

        public void InitializeAvaiabel()
        {
            avaiabel.Add(new Comp() { component = "Completed",  type = "asd", m_get = false, m_set = true });
            avaiabel.Add(new Comp() { component = "blahhh",     type = "asd", m_get = false, m_set = true });
            avaiabel.Add(new Comp() { component = "Completed",  type = "asd", m_get = false, m_set = true });
            avaiabel.Add(new Comp() { component = "blahhh",     type = "asd", m_get = false, m_set = true });
            avaiabel.Add(new Comp() { component = "Complerial", type = "asd", m_get = false, m_set = true });
            
            added.Add(new Comp() { component = "Completed", type = "asd", m_custom = false, m_standard = true });
            added.Add(new Comp() { component = "blahhh", type = "asd", m_custom = false, m_standard = true });
            added.Add(new Comp() { component = "Complerial", type = "asd", m_custom = false, m_standard = true });
            


            cb_addcomp.ItemsSource = avaiabel;

            lb_auto.ItemsSource = added;
            lb_comp.ItemsSource = added;
            lb_custom.ItemsSource = added;

        }

        public void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
           
            //if((string)cb_added.SelectedItem =="Size")
            //{
            //    foreach (char ch in e.Text)
            //    {
            //        if (!((Char.IsDigit(ch) || ch.Equals('.'))))
            //        {
            //            e.Handled = true;
            //            break;
            //        }

            //    }
            //}
        }

        private void btn_cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void btn_add_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void bt_add_Click(object sender, RoutedEventArgs e)
        {
            //AddComponent((string)cb_addcomp.SelectedItem);
        }
        
        private void bt_del_Click(object sender, RoutedEventArgs e)
        {
            //DeleteComponent((string)cb_added.SelectedItem);
        }

        private void AddComponent(string component)
        {
            //if(!cb_added.Items.Contains(component))
            //{
            //    cb_added.Items.Add(component);
            //    cb_addcomp.Items.Remove((string)cb_addcomp.SelectedItem);
            //}
        }

        private void DeleteComponent(string component)
        {
            //cb_added.Items.Remove(component);
            //cb_addcomp.Items.Add(component);
        }

        private void Button_Remove(object sender, RoutedEventArgs e)
        {

        }
    }
}
