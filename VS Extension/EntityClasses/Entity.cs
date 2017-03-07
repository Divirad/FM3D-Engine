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
			
			string namee = rawdata[0];
			name = namee;
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

		//Dusnt wurk
		//public Entity(XmlReader xml) {

		//	xml.ReadToDescendant("EntityPreset");
		//	xml.MoveToAttribute("preset");
		//	name = xml.Value;
		//	MessageBox.Show(xml.Value);

		//	xml.ReadToDescendant("Project");

		//	while (xml.Read()) {
		//		if ((xml.NodeType == XmlNodeType.Element) && (xml.Name == "Component") && (xml.Depth == 1)) {
		//			xml.MoveToAttribute("name");
		//			name = xml.Value;
		//			MessageBox.Show(xml.Value + "Custom");
		//			//LoadProperties(xml);
		//		}
		//		if ((xml.NodeType == XmlNodeType.Element) && (xml.Name == "CustomProperty") && (xml.Depth == 1)) {
		//			xml.MoveToAttribute("name");
		//			name = xml.Value;
		//			MessageBox.Show(xml.Value + "Custom");
		//			//LoadProperties(xml);
		//			//LoadProperties(xml);
		//		}
		//	}
		//}

		//public void load1(XmlReader xml) {
		//	Component lastcomp = new Component();
		//	while (xml.Read()) {
		//		if ((xml.NodeType == XmlNodeType.Element) && (xml.Name == "Component") && (xml.Depth == 1)) {
		//			xml.MoveToAttribute("name");
		//			MessageBox.Show(xml.Value + "Custom");
		//			while (xml.Read() && xml.Name == "Property") {
						
		//					xml.MoveToAttribute("name");
		//					MessageBox.Show(xml.Value + " Property");
		//			}
		//		}
		//		else if ((xml.NodeType == XmlNodeType.Element) && (xml.Name == "CustomProperty") && (xml.Depth == 1)) {
		//			xml.MoveToAttribute("name");
		//			name = xml.Value;
		//			MessageBox.Show(xml.Value + "Custom");
		//			//LoadProperties(xml);
		//			//LoadProperties(xml);
		//		}
		//	}
		//	xml.Close();
		////}

		//private static void LoadProperties(XmlReader xml) {
		//	while (xml.Read()) {
		//		//if (xml.NodeType == XmlNodeType.Element) {

		//			if (xml.Name.Contains("Property")) {
		//				xml.MoveToAttribute("name");
		//				MessageBox.Show(xml.Value + "Custom");
		//				//var xf = new File(xml.Value);
		//				//folder.Content.Add(xf);
		//				//folder.Files.Add(xf);
		//			} 
		//			//else if (xml.Name == "Directory") {
		//			//	xml.MoveToAttribute("name");
		//			//	//Directory f = new Directory(xml.Value);
		//			//	xml.MoveToElement();
		//			//	//if (xml.IsStartElement())
		//			//	if (!xml.IsEmptyElement) {
		//			//		xml.MoveToContent();
		//			//		//LoadProjectFiles(f, xml);
		//			//	}
		//			//	//folder.Content.Add(f);
		//			//	//folder.SubDirectories.Add(f);
		//		//	//}
		//		//} else if (xml.NodeType == XmlNodeType.EndElement) {
		//		//	return;
		//		//}
		//	}
		//}


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
					writer.WriteStartElement("CustomProperty");
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
