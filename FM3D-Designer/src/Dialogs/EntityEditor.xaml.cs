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

namespace FM3D_Designer.src.Dialogs
{
    /// <summary>
    /// Interaction logic for EntityEditor.xaml
    /// </summary>
   

public partial class EntityEditor : DialogBase
    {
        private Entity _entity = new Entity();
        private List<Component> _avaiabel = new List<Component>();

        private Component _selectedc = new Component();
        private Property _selectedp = new Property();

        private string _path { get; set; }

        private ObservableCollection<string> allcomponents = new ObservableCollection<string>();

        private MetroWindow _window { get; set; }

        private bool _newent { get; set; }

        public EntityEditor(MetroWindow window, string path, bool newent) : base(window)
        {
            InitializeComponent();
            InitializeItems();
            LoadCBAvaiabel();
            LoadListBox();

            _newent = newent;
            _path = path;
            _window = window;

            if (newent == false)
            {
                LoadEntity(path);
            }
        }

        public void InitializeItems()
        {
            _avaiabel.Add(new Component() { name = "FM3D::PositionComponent" });
            _avaiabel.Add(new Component() { name = "FM3D::RotationComponent" });
            _avaiabel.Add(new Component() { name = "FM3D::ScaleComponent" });
            _avaiabel.Add(new Component() { name = "FM3D::RenderableComponent" });

            //ObservableCollection<string> components;
            //if(!MainWindow.Instance.visualStudio.GetComponents(out components))
            //{
            //    MainWindow.Instance.ShowMessageAsync("VisualStudio Error", "Could not get components");
            //    return;
            //}
            //foreach(var c in components)
            //{
            //    _avaiabel.Add(new Component() { name = c });
            //}
        }
		private void AutoProps() {
			foreach (Component check in _entity.components) {
				if (check.m_standard == true) {
					switch (check.name) {
						case "FM3D::PositionComponent":
							_entity._propauto.Add(new Property() { name = "Position", m_get = true, m_set = true, type = "FM3D::Vector3f" });
							break;
						case "FM3D::RotationComponent":
							_entity._propauto.Add(new Property() { name = "Rotation", m_get = true, m_set = true, type = "FM3D::Vector3f" });
							break;
						case "FM3D::ScaleComponent":
							_entity._propauto.Add(new Property() { name = "Scale", m_get = true, m_set = true, type = "FM3D::Vector3f" });
							break;
						case "FM3D::RenderableComponent":
							_entity._propauto.Add(new Property() { name = "Model", m_get = true, m_set = true, type = "const FM3D::Model*" });
							break;
						default:
							break;
					}
				}
			}

		}

		private void LoadListBox()
        {
            lb_comp.ItemsSource = _entity.components;
            lb_auto.ItemsSource = _entity._propauto;
            lb_custom.ItemsSource = _entity._propcustom;
            
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
                    _selectedc = temp;
                    break;
                }
            }
            _avaiabel.Add(_selectedc);

            var lola = MessageBox.Show(_avaiabel.ToString() + " comp!!");
            _entity.components.Remove(_selectedc);

            var aa = MessageBox.Show(_selectedc.name + " selected!!");
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
            this.Close();
        }

        private void btn_save_Click(object sender, RoutedEventArgs e)
        {
        //    ToolWindows.FileBrowser.Item item;
        //    item.CreateFile();

            //ToolWindows.FileBrowser.Item.
            //ToolWindows.FileBrowser.Item.CreateFile(_entity.name+".ent", ToolWindows.FileBrowser.ItemTypes.UnknownFile);
            WriteEntity(_path);
        }

        private void cb_standard_Checked(object sender, RoutedEventArgs e)
        {
            _entity._propauto.Clear();
            AutoProps();
            this.Refresh();
        }

        private void CheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            _entity._propauto.Clear();
            AutoProps();
            this.Refresh();

        }
       

        private void DeletePropauto(string prop)
        {
            foreach(Property prop_ in _entity._propauto)
            {
                if (prop_.name == prop) { _entity._propauto.Remove(prop_); }
            }
        }

        #region LOAD
        private async void LoadEntity(string path)
        {
            string xmlfile = System.IO.File.ReadAllText(_path);
            if (xmlfile.Contains("EntityPreset"))
            {
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.IgnoreWhitespace = true;
                XmlReader xml = XmlReader.Create(path, settings);

                xml.ReadToDescendant("EntityPreset");

				XmlReader xml2 = xml.ReadSubtree();

				// LoadXmlFile(path, xml.ReadSubtree());
				while (xml2.Read()) {
					if ((xml2.NodeType == XmlNodeType.Element) && (xml2.Name == "EntityPreset") && (xml2.Depth == 0)) {
						xml2.MoveToAttribute("preset");
						_entity.name = xml2.Value;
						tb_entityname.Text += _entity.name;
						// LoadProjectFiles(xml);
						while (xml2.Read()) {
							if (xml2.NodeType == XmlNodeType.Element) {
								if (xml2.Name == "Component") {
									Component temp = new Component();
									xml2.MoveToAttribute("name");
									temp.name = xml2.Value;
									xml2.MoveToAttribute("const");
									temp.m_const = Convert.ToBoolean(xml2.Value);
									xml2.MoveToAttribute("standard");
									temp.m_standard = Convert.ToBoolean(xml2.Value);

									AddComponent(temp.name, temp.m_const, temp.m_standard);
								}
								if (xml2.Name == "Property") {
									Property temp = new Property();
									xml2.MoveToAttribute("name");
									temp.name = xml2.Value;

									xml2.MoveToAttribute("get");
									temp.m_get = Convert.ToBoolean(xml2.Value);

									xml2.MoveToAttribute("set");
									temp.m_set = Convert.ToBoolean(xml2.Value);

									xml2.MoveToAttribute("typ");
									temp.type = xml2.Value;

									xml2.MoveToAttribute("auto");

									if (Convert.ToBoolean(xml2.Value) == true) {
										//Abfragen
										_entity._propauto.Add(temp);
									} else {
										_entity._propcustom.Add(temp);
									}
								}
							}
						}
					}
				}

				xml.Close();
            } else { await _window.ShowMessageAsync("ERROR", "No Entityfile!"); }

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
                        Property temp = new Property();
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
                            _entity._propauto.Add(temp);
                        }
                        else
                        {
                            _entity._propcustom.Add(temp);
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

                foreach (Property prop in _entity._propauto)
                {
                    writer.WriteStartElement("Property");
                    writer.WriteAttributeString("name", prop.name);
                    writer.WriteAttributeString("get", prop.m_get.ToString());
                    writer.WriteAttributeString("set", prop.m_set.ToString());
                    writer.WriteAttributeString("typ", prop.type);
                    writer.WriteAttributeString("auto", true.ToString());
                    writer.WriteEndElement();
                }

                foreach (Property prop in _entity._propcustom)
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
            _entity._propcustom.Add(new Property() { name = (string)tb_propnam.Text, type=(string)tb_proptype.Text });
            this.Refresh();
            //.Dispatcher.Invoke(DispatcherPriority.Render, EmptyDelegate);
        }

        private void bt_deletecustomprop(object sender, RoutedEventArgs e)
        {
            foreach (Property temp in _entity._propcustom)
            {
                if (temp.m_selected == true)
                {
                    _selectedp = temp;
                    break;
                }
            }
            _entity._propcustom.Remove(_selectedp);
            this.Refresh();
        }
    }
}
