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

using System.IO;
using System.Collections.ObjectModel;
using System.Xml;

namespace FM3D_Designer.src
{
    class Props
    {
        public string name { get; set; }
        public string type { get; set; }
        public bool m_get { get; set; }
        public bool m_set { get; set; }
        public bool m_selected { get; set; }
    }

    class Component
    {
        public string name { get; set; }
        public bool m_custom { get; set; }
        public bool m_const { get; set; }
        public bool m_standard { get; set; }
        public bool m_selected { get; set; }
    }

    class Entity
    {
        public string name { get; set;  }
        public List<Component> components = new List<Component>();
    }
    
}

namespace FM3D_Designer.src.Dialogs
{
    /// <summary>
    /// Interaction logic for EntityEditor.xaml
    /// </summary>
   

public partial class EntityEditor : DialogBase
    {
        private Entity _entity = new Entity();
        private List<Component> _avaiabel = new List<Component>();
        private List<Props> _propauto = new List<Props>();
        private List<Props> _propcustom = new List<Props>();

        private Component selectedc = new Component();
        private Props selectedp = new Props();

        private string thepath { get; set; }

        private ObservableCollection<string> allcomponents = new ObservableCollection<string>();

        private MetroWindow _window { get; set; }

        public EntityEditor(MetroWindow window, string path, bool newent) : base(window)
        {
            InitializeComponent();
            InitializeItems();
            LoadCBAvaiabel();
            LoadListBox();
            if (newent == false)
            {
                LoadEntity(path);
            }
            thepath = path;

            _window = window;
        }

        public void InitializeItems()
        {
            
            _avaiabel.Add(new Component() { name = "Rotation" });
            _avaiabel.Add(new Component() { name = "Position" });
            _avaiabel.Add(new Component() { name = "Size"});
            _avaiabel.Add(new Component() { name = "2DRender"});
            _avaiabel.Add(new Component() { name = "3DRender"});
        }

        private void LoadListBox()
        {
            lb_comp.ItemsSource = _entity.components;
            lb_auto.ItemsSource = _propauto;
            lb_custom.ItemsSource = _propcustom;
            
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
            foreach (Component ac in _avaiabel)
            {
                cb_addcomp.Items.Add(ac.name);
            }
        }

        private void AddComponent(string component_)
        {
            if (component_ != "")
            {
                
            cb_addcomp.Items.Remove(component_);

                foreach (Component listed in _avaiabel)
                {
                    if ((string)listed.name == component_)
                    {
                        _entity.components.Add(listed);
                        _avaiabel.Remove(listed);
                        Refresh();
                        break;
                    }
                }
            }
        }

        private void AddComponent(string component_, bool _const, bool _stand)
        {
            if (component_ != "")
            {
                cb_addcomp.Items.Remove(component_);

                foreach (Component listed in _avaiabel)
                {
                    if ((string)listed.name == component_)
                    {
                        _entity.components.Add(new Component(){name= listed.name, m_const= _const, m_standard=_stand});
                        _avaiabel.Remove(listed);
                        Refresh();
                        break;
                    }
                }
            }
        }

        private void DeleteComponent()
        {
            foreach (Component temp in _entity.components)
            {
                if (temp.m_selected == true)
                {
                    var a = MessageBox.Show(temp.name + " selected!!");
                    selectedc = temp;
                    break;
                }
            }
            _avaiabel.Add(selectedc);

            var lola = MessageBox.Show(_avaiabel.ToString() + " comp!!");
            _entity.components.Remove(selectedc);

            var aa = MessageBox.Show(selectedc.name + " selected!!");
            this.Refresh();
            LoadCBAvaiabel();


        }

        private void Button_Remove(object sender, RoutedEventArgs e)
        {
            DeleteComponent();
            
        }

        private void bt_add_Click(object sender, RoutedEventArgs e)
        {
            AddComponent((string)cb_addcomp.SelectedItem);
        }

        private void btn_cancel_Click(object sender, RoutedEventArgs e)
        {
            //_window.HideMetroDialogAsync(this);
            this.CloseW();
        }

        private void btn_save_Click(object sender, RoutedEventArgs e)
        {
            WriteEntity(thepath);
        }

        private void cb_standard_Checked(object sender, RoutedEventArgs e)
        {
            _propauto.Clear();
            AutoProps();
            this.Refresh();
        }

        private void CheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            _propauto.Clear();
            AutoProps();
            this.Refresh();

        }
        private void AutoProps()
        {
            foreach (Component check in _entity.components)
            {
                if (check.m_standard == true)
                {
                    switch (check.name)
                    {
                        case "3DRender":
                            _propauto.Add(new Props() { name = "m_model", m_get = true, m_set = true, type = "Model" });
                            break;
                        case "Position":
                            _propauto.Add(new Props() { name = "m_position", m_get = true, m_set = true, type = "Vector3f" });
                            break;
                        case "Rotation":
                            _propauto.Add(new Props() { name = "m_rotation", m_get = true, m_set = true, type = "Vector3f" });
                            break;
                        case "Size":
                            _propauto.Add(new Props() { name = "m_size", m_get = true, m_set = true, type = "Vector3f" });
                            break;
                        default:
                            break;
                    }
                }
            }

        }

        private void DeletePropauto(string prop)
        {
            foreach(Props prop_ in _propauto)
            {
                if (prop_.name == prop) { _propauto.Remove(prop_); }
            }
        }

        #region LOAD
        private void LoadEntity(string path)
        {
            Project result = new Project(path);

            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreWhitespace = true;
            XmlReader xml = XmlReader.Create(path, settings);
            if (xml.ReadToDescendant("EntityPreset"))
            {
                LoadXmlFile(path, xml.ReadSubtree());
            }
            else { var a = MessageBox.Show("No Entity!\nChoose another File!!"); }
            xml.Close();
        }
        private void LoadXmlFile(string path,  XmlReader xml)
        {
            while (xml.Read())
            {
                if ((xml.NodeType == XmlNodeType.Element) && (xml.Name == "EntityPreset") && (xml.Depth == 0))
                {
                    xml.MoveToAttribute("preset");
                    _entity.name = xml.Value;
                    tb_entityname.Text += _entity.name;
                    LoadProjectFiles(xml);
                }
            }
            xml.Close();
        }

         public void LoadProjectFiles(XmlReader xml)
        {
            while (xml.Read())
            {
                if (xml.NodeType == XmlNodeType.Element)
                {
                    if (xml.Name == "Component")
                    {
                        Component temp = new Component();
                        xml.MoveToAttribute("name");
                        temp.name = xml.Value;
                        xml.MoveToAttribute("const");
                        temp.m_const = Convert.ToBoolean(xml.Value);
                        xml.MoveToAttribute("standard");
                        temp.m_standard = Convert.ToBoolean(xml.Value);

                        AddComponent(temp.name, temp.m_const, temp.m_standard);
                    }
                    if (xml.Name == "Property")
                    {
                        Props temp = new Props();
                        xml.MoveToAttribute("name");
                        temp.name = xml.Value;

                        xml.MoveToAttribute("get");
                        temp.m_get = Convert.ToBoolean(xml.Value);

                        xml.MoveToAttribute("set");
                        temp.m_set = Convert.ToBoolean(xml.Value);

                        xml.MoveToAttribute("typ");
                        temp.type = xml.Value;

                        xml.MoveToAttribute("auto");
                        
                        if (Convert.ToBoolean(xml.Value) == true)
                        {
                            //Abfragen
                            _propauto.Add(temp);
                        }
                        else
                        {
                            _propcustom.Add(temp);
                        }
                    }
                }
            }
        }
        #endregion LOAD

        #region SAVE
        private void WriteEntity(string path)
        {
            if (File.Exists(path) == true)
            {
                File.Delete(path);
            }

            using (XmlWriter writer = XmlWriter.Create(path))
            {
                writer.WriteStartDocument();
                writer.WriteStartElement("EntityPreset");
                writer.WriteAttributeString("preset", _entity.name);

                foreach (Component comp in _entity.components)
                {
                    writer.WriteStartElement("Component");
                    writer.WriteAttributeString("name", comp.name);
                    writer.WriteAttributeString("const", comp.m_const.ToString());
                    writer.WriteAttributeString("standard", comp.m_standard.ToString());
                    writer.WriteEndElement();
                }

                foreach (Props prop in _propauto)
                {
                    writer.WriteStartElement("Property");
                    writer.WriteAttributeString("name", prop.name);
                    writer.WriteAttributeString("get", prop.m_get.ToString());
                    writer.WriteAttributeString("set", prop.m_set.ToString());
                    writer.WriteAttributeString("typ", prop.type);
                    writer.WriteAttributeString("auto", true.ToString());
                    writer.WriteEndElement();
                }

                foreach (Props prop in _propcustom)
                {
                    writer.WriteStartElement("Property");
                    writer.WriteAttributeString("name", prop.name);
                    writer.WriteAttributeString("get", prop.m_get.ToString());
                    writer.WriteAttributeString("set", prop.m_set.ToString());
                    writer.WriteAttributeString("typ", prop.type);
                    writer.WriteAttributeString("auto", false.ToString());
                    writer.WriteEndElement();
                }

                writer.WriteEndElement();
                writer.WriteEndDocument();
            }
        }
        #endregion SAVE

        private void tb_entityname_TextChanged(object sender, TextChangedEventArgs e)
        {
            _entity.name = tb_entityname.Text;
        }

        private void tb_propcustom_Click(object sender, RoutedEventArgs e)
        {
            _propcustom.Add(new Props() { name = (string)tb_propnam.Text, type=(string)tb_proptype.Text });
            this.Refresh();
            //.Dispatcher.Invoke(DispatcherPriority.Render, EmptyDelegate);
        }

        private void bt_deletecustomprop(object sender, RoutedEventArgs e)
        {
            foreach (Props temp in _propcustom)
            {
                if (temp.m_selected == true)
                {
                    selectedp = temp;
                    break;
                }
            }
            _propcustom.Remove(selectedp);
            this.Refresh();
        }
    }
}
