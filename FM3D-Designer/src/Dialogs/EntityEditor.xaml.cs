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
        public List<Component> _available = new List<Component>();

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

            _newent = newent;
            _path = path;
            _window = window;

			if (newent == false) {
				LoadEntity(path);
				tb_entityname.Text = _entity.name;
				foreach (Component c in _entity.components) {

					List<Component> delete = new List<Component>();
					foreach (Component av in _available) {
						if (av.name ==c.name) {
							delete.Add(av);
						}
					}
					foreach(Component del in delete) {
						_available.Remove(del);
					}
				}
			}

			LoadCBAvaiabel();
			LoadListBox();
		}

        public void InitializeItems()
        {
			List<Property> a1 = new List<Property>();
			a1.Add(new Property() { name = "Position", m_get = true, m_set = true, type = "FM3D::Vector3f" });
            _available.Add(new Component() { name = "FM3D::PositionComponent" , _propauto= a1  });

			List<Property> a2 = new List<Property>();
			a2.Add(new Property() { name = "Rotation", m_get = true, m_set = true, type = "FM3D::Vector3f" });
			_available.Add(new Component() { name = "FM3D::RotationComponent" , _propauto = a2 });

			List<Property> a3 = new List<Property>();
			a3.Add(new Property() { name = "Scale", m_get = true, m_set = true, type = "FM3D::Vector3f" });
			_available.Add(new Component() { name = "FM3D::ScaleComponent", _propauto = a3 });

			List<Property> a4 = new List<Property>();
			a4.Add(new Property() { name = "Model", m_get = true, m_set = true, type = "const FM3D::Model*" });
			_available.Add(new Component() { name = "FM3D::RenderableComponent", _propauto = a4 });
			
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
		private void AddPropToComp(Component comp, Property prop) {
			_entity._propauto.Add(prop);
			comp._propauto.Add(prop);
		}

		private void AutoProps() {
			foreach (Component check in _entity.components) {
				if (check.m_standard == true) {
					switch (check.name) {
						case "FM3D::PositionComponent":
							AddPropToComp(check, new Property() { name = "Position", m_get = !check.m_const, m_set = true, type = "FM3D::Vector3f" });
							break;
						case "FM3D::RotationComponent":
							AddPropToComp(check, new Property() { name = "Rotation", m_get = !check.m_const, m_set = true, type = "FM3D::Vector3f" });
							break;
						case "FM3D::ScaleComponent":
							AddPropToComp(check, new Property() { name = "Scale", m_get = !check.m_const, m_set = true, type = "FM3D::Vector3f" });
							break;
						case "FM3D::RenderableComponent":
							AddPropToComp(check, new Property() { name = "Model", m_get = !check.m_const, m_set = true, type = "const FM3D::Model*" });
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
            foreach (Component ac in _available)
            {
                cb_addcomp.Items.Add(ac.name);
            }
        }

        private void AddComponent(string component_)
        {
            if (component_ != "")
            {
            cb_addcomp.Items.Remove(component_);

                foreach (Component listed in _available)
                {
                    if ((string)listed.name == component_)
                    {
                        _entity.components.Add(listed);
                        _available.Remove(listed);
                        Refresh();
                        break;
                    }
                }
            }
        }

		private void AddComponent(string component_, bool _const, bool _stand) {
			if (component_ != "") {
				cb_addcomp.Items.Remove(component_);

				foreach (Component listed in _available) {
					if ((string)listed.name == component_) {
						_entity.components.Add(new Component() { name = listed.name, m_const = _const, m_standard = _stand });
						_available.Remove(listed);
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
                    _selectedc = temp;
                    break;
                }
            }
            _available.Add(_selectedc);
            _entity.components.Remove(_selectedc);
			
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
			foreach(Component c in _entity.components) {
				c._propauto.Clear();
			}
            AutoProps();
            this.Refresh();
        }

        private void CheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            _entity._propauto.Clear();
			foreach (Component c in _entity.components) {
				c._propauto.Clear();
			}
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
		
        private void LoadEntity(string path)
        {
			string ent = System.IO.File.ReadAllText(path);
			Entity entnew;
			if (path=="") {
				entnew = new Entity();
			} else {
				entnew = new Entity(ent);
			}
			_entity = entnew;

		}
		
        private void WriteEntity(string path)
        {
			System.IO.File.WriteAllText(path,_entity.ToString());
        }

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