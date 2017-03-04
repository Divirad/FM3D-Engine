using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml;

namespace FM3D_Designer.src {
    static class SC {
        public static char SEPVAL = ';';  // Char for seperating Values
        public static char SEP_PC = '!';   // Seperates The Properties and Components in Lists
        public static char SEPENT = '|';  // Seperate: Name|List1|List2|List3
    };
    public class Entity {
        public Entity() {

        }
        //convert string to Entity
        public Entity(string entity) {

            // Split in 4 strings in array
            // [NAME] SC.SEPENT [COMPS] SC.SEPENT [PROPSAUTO] SC.SEPENT [PROPSCUSTOM]

            string[] rawdata = entity.Split(SC.SEPENT);
            name = rawdata[0];

            #region COMPONENT ANALYSE
            // Split in all Existing Comps
            // [COMPS] = [(COMP) ! (COMP) ! (COMP)]
            string[] compsraw = rawdata[1].Split(SC.SEP_PC);

            // Component-string splitting
            // (COMPS) = ({Name} {m_custom} {m_const} {m_standard})
            foreach (string comp in compsraw) {
                if (comp != "" && comp != "\n") { components.Add(new Component(comp)); }
            }
            #endregion
			
            #region AUTO PROPERTY ANALYSE
            string[] autoraw = rawdata[2].Split(SC.SEP_PC);
            // PropsAuto-string splitting
            // (COMPS) = ({Name} {m_custom} {m_const} {m_standard
            foreach (string prop in autoraw) {
                if (prop != "" && prop != "\n") { _propauto.Add(new Property(prop)); }
            }
            #endregion

            #region CUSTOM PROPERTY ANALYSE
            string[] customraw = rawdata[3].Split(SC.SEP_PC);
            // PropsAuto-string splitting
            // (COMPS) = ({Name} {m_custom} {m_const} {m_standard})
            foreach (string prop in customraw) {
                if (prop != "" && prop != "\n") { _propcustom.Add(new Property(prop)); }
            }
            #endregion
        }

		public Entity(string path, bool b) {

			string xmlfile = System.IO.File.ReadAllText(path);
			if (xmlfile.Contains("EntityPreset")) {
				XmlReaderSettings settings = new XmlReaderSettings();
				settings.IgnoreWhitespace = true;
				XmlReader xml = XmlReader.Create(path, settings);

				xml.ReadToDescendant("EntityPreset");

				XmlReader xml2 = xml.ReadSubtree();

				// LoadXmlFile(path, xml.ReadSubtree());
				while (xml2.Read()) {
					if ((xml2.NodeType == XmlNodeType.Element) && (xml2.Name == "EntityPreset") && (xml2.Depth == 0)) {
						xml2.MoveToAttribute("preset");
						this.name = xml2.Value;
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

									this.components.Add(temp);
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
										this._propauto.Add(temp);
									} else {
										this._propcustom.Add(temp);
									}
								}
							}
						}
					}
				}

				xml.Close();
			} else { MessageBox.Show("ERROR", "No Entityfile!"); }

		}

		public string name { get; set; }
        public List<Component> components = new List<Component>();
        public List<Property> _propauto = new List<Property>();
        public List<Property> _propcustom = new List<Property>();

        public override string ToString() {
            string result = "";
            result += name + SC.SEPENT;

            foreach (Component c in components) {
                result += c.ToString() + SC.SEP_PC;
            }

            result += SC.SEPENT;

            foreach (Property p in _propauto) {
                result += p.ToString() + SC.SEP_PC;
            }

            result += SC.SEPENT;

            foreach (Property p in _propcustom) {
                result += p.ToString() + SC.SEP_PC;
            }

            result += "\n";

            return result;
        }

        public string ToString(bool i) {
            string result = "";
            switch (i) {
                case true:
                    result += "------------\n"
                        + name + "\n" +
                        "------------\n";
                    foreach (Component c in components) {
                        result += c.ToString(1) + "\n" + "\n";
                    }
                    result += "------------\n";
                    break;
                case false:
                    result += "------------\n"
                        + name + "\n" +
                        "------------\n";
                    result += "CUSTOM" + "\n" +
                       "------------\n";
                    foreach (Property p1 in _propcustom) {
                        result += p1.ToString(1) + "\n" + "\n";
                    }
                    result += "------------\n";
                    result += "AUTO" + "\n" +
                       "------------\n";
                    foreach (Property p2 in _propauto) {
                        result +=  p2.ToString(1) + "\n" + "\n";
                    }
                    break;
            }
            return result;
        }
    }

}
