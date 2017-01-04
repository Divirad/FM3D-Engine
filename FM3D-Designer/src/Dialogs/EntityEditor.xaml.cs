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

namespace FM3D_Designer.src
{
    class Component
    {
        public int ID { get; set; }
        public string component { get; set; }
        public string type { get; set; }
        public bool m_get { get; set; }
        public bool m_set { get; set; }
        public bool m_custom { get; set; }
        public bool m_const { get; set; }
        public bool m_standard { get; set; }



    }
}

namespace FM3D_Designer.src.Dialogs
{
    /// <summary>
    /// Interaction logic for EntityEditor.xaml
    /// </summary>
   

public partial class EntityEditor : DialogBase
    {
        List<Component> avaiabel = new List<Component>();
        List<Component> added = new List<Component>();

        public EntityEditor(MetroWindow window) : base(window)
        {
            InitializeComponent();
            InitializeItems();
            LoadCBAvaiabel();
            LoadListBox();

            
        }

        public void InitializeItems()
        {
            //avaiabel.Add(new Comp() { component = "Completed",  type = "asd", m_get = false, m_set = true });

            avaiabel.Add(new Component() { component = "Position", type = "Vector3f" });
            avaiabel.Add(new Component() { component = "Size", type = "Vector3f" });
            avaiabel.Add(new Component() { component = "Model", type = "Model" });
            avaiabel.Add(new Component() { component = "Texture", type = "Texture" });
            avaiabel.Add(new Component() { component = "2DRender", type = "??" });
            avaiabel.Add(new Component() { component = "3DRender", type = "??" });
        }

        private void LoadListBox()
        {
            lb_auto.ItemsSource = added;
            lb_comp.ItemsSource = added;
            lb_custom.ItemsSource = added;

            //lb_auto.SelectionMode = SelectionMode.Multiple;
            //lb_comp.SelectionMode = SelectionMode.Multiple;
            //lb_custom.SelectionMode = SelectionMode.Multiple;
        }

        private void Refresh()
        {
            lb_auto.Items.Refresh();
            lb_comp.Items.Refresh();
            lb_custom.Items.Refresh();

            cb_addcomp.Items.Refresh();
        }

        private void LoadCBAvaiabel()
        {
            cb_addcomp.Items.Clear();
            foreach (Component ac in avaiabel)
            {
                cb_addcomp.Items.Add(ac.component);
            }
        }

        private void AddComponent(string component_)
        {
            if (component_ != "")
            {
            cb_addcomp.Items.Remove(component_);

                foreach (Component listed in avaiabel)
                {
                    if ((string)listed.component == component_)
                    {
                        added.Add(listed);
                        avaiabel.Remove(listed);
                        Refresh();
                        break;
                    }
                }
            }

        }

        private void DeleteComponent(string component_)
        {
            if (component_ != "")
            {
                foreach (Component listed in added)
                {
                    cb_addcomp.Items.Add(component_);
                    if ((string)listed.component == component_)
                    {
                        avaiabel.Add(listed);
                        added.Remove(listed);
                        Refresh();
                        break;
                    }
                }
            }
            cb_addcomp.SelectedItem = 1;
        }

        private void Button_Remove(object sender, RoutedEventArgs e)
        {
                //avaiabel.Add(added[lb_comp.SelectedIndex]);
                //added.RemoveAt(/*lb_comp.SelectedIndex*/lb_comp.SelectedItems.GetEnumerator();
                //foreach(var a in lb_comp)
                //Refresh();

        }

        private void bt_add_Click(object sender, RoutedEventArgs e)
        {
            AddComponent((string)cb_addcomp.SelectedItem);
            

        }

        private void btn_cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void btn_save_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void cb_standard_Checked(object sender, RoutedEventArgs e)
        {

        }
    }
}
