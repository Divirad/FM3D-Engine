using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml;

namespace FM3D_Designer.src {
    static class SC {
        public static char VAL = ';';  // Char for seperating Values
        public static char COMPSEP = '!';   // Seperates The Properties and Components in Lists
        public static char ENTCOMP = '|';  // Seperate: Name|COMP|PROP|
		public static char COMP = '~';  // Seperate: Name|COMP|PROP|
		public static char cSEPp = '#';   // Seperate: COMPDATA # PROP
	};


    public class Entity {
        
		public string name { get; set; }
		public List<Component> components = new List<Component>();
		public List<Property> _propauto = new List<Property>();
		public List<Property> _propcustom = new List<Property>();

		public Entity() {

		}
		public Entity(string str) {
			// Name
			string[] rawdata = str.Split(SC.ENTCOMP);
			name = rawdata[0];
			// Components
			string[] comps = rawdata[1].Split(SC.COMP);

			foreach (string c in comps) {
				if (c != "" && c != "\n" && c != " ") {
					List<Property> a = new List<Property>();
					components.Add(new Component(c, out a));
					foreach (Property prop in a) {
						_propauto.Add(prop);
					}
				}
			}

			// Properties
			string[] props = rawdata[2].Split(SC.COMPSEP);
			foreach (string p in props) {
				if (p != "" && p != "\n" && p != " ") {
					_propcustom.Add(new Property(p));
				}
			}
		}

		public Entity(XmlReader xml) {

			xml.ReadToDescendant("EntityPreset");
			XmlReader xml2 = xml.ReadSubtree();

			// LoadXmlFile(path, xml.ReadSubtree());
			while (xml2.Read()) {
				if ((xml2.NodeType == XmlNodeType.Element) && (xml2.Name == "EntityPreset") && (xml2.Depth == 0)) {
					xml2.MoveToAttribute("preset");
					name = xml2.Value;

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
								if (!xml2.IsEmptyElement) {

									while (xml2.Read()) {
										if (xml2.Name == "Property") {
											Property proptemp = new Property();
											xml2.MoveToAttribute("name");
											proptemp.name = xml2.Value;

											xml2.MoveToAttribute("get");
											proptemp.m_get = Convert.ToBoolean(xml2.Value);

											xml2.MoveToAttribute("set");
											proptemp.m_set = Convert.ToBoolean(xml2.Value);

											xml2.MoveToAttribute("typ");
											proptemp.type = xml2.Value;

											_propauto.Add(proptemp);
											temp._propauto.Add(proptemp);
										}
									}
								}
								components.Add(temp);
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

								_propcustom.Add(temp);
							}
						}
					}
				}
			}

			xml.Close();

		}

		public static Entity EntityToXML(Entity ent, string path) {

			if (File.Exists(path) == true) {
				File.Delete(path);
			}

			using (XmlWriter writer = XmlWriter.Create(path)) {
				writer.WriteStartDocument();
				writer.WriteStartElement("EntityPreset");
				writer.WriteAttributeString("preset", ent.name);

				foreach (Component comp in ent.components) {
					writer.WriteStartElement("Component");
					writer.WriteAttributeString("name", comp.name);
					writer.WriteAttributeString("const", comp.m_const.ToString());
					writer.WriteAttributeString("standard", comp.m_standard.ToString());

					foreach (Property propauto in comp._propauto) {
						writer.WriteStartElement("Property");
						writer.WriteAttributeString("name", propauto.name);
						writer.WriteAttributeString("typ", propauto.type);
						writer.WriteAttributeString("get", propauto.m_get.ToString());
						writer.WriteAttributeString("set", propauto.m_set.ToString());
						writer.WriteEndElement();
					}

					writer.WriteEndElement();
				}
				
				foreach (Property prop in ent._propcustom) {
					writer.WriteStartElement("Property");
					writer.WriteAttributeString("name", prop.name);
					writer.WriteAttributeString("typ", prop.type);
					writer.WriteAttributeString("get", prop.m_get.ToString());
					writer.WriteAttributeString("set", prop.m_set.ToString());
					writer.WriteEndElement();
				}

				writer.WriteEndElement();
				writer.WriteEndDocument();
			}

			return ent;
		}

		public override string ToString() {
			string str="";

			str += name;
			str += SC.ENTCOMP;
			foreach(Component c in components) {
				str+=c.ToString();
				str += SC.COMP;
			}
			str += SC.ENTCOMP;

			foreach (Property prop in _propcustom) {
				str += prop.ToString();
				str += SC.COMPSEP;
			}

			return str;
		}

		public string ToString(bool a) {
			string str = "";
			if (a) {
				str += "-----------" + "\n";
				str += name + "\n";
				str += "-----------" + "\n";

				foreach (Component c in components) {
					str += c.ToString(2) + "\n";
				}
			} else {
				foreach (Property p in _propcustom) {
					str += p.ToString(2) + "\n";
				}
			}
			return str;
		}
    }

}
