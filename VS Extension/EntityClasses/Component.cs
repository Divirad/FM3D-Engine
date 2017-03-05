
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FM3D_Designer.src {

    public class Component {
		
		public Component() { }

		public Component(string str) {
			List<Property> ps = new List<Property>();
			Component a = new Component(str,out ps);
			this.name = a.name;
			this.m_const = a.m_const;
			this.m_selected = a.m_selected;
		}

		public Component(string str, out List<Property> a) {
			List<Property> ps = new List<Property>();
			if (str != "" && str != "\n") {

				string[] parts = str.Split(SC.cSEPp);

				string[] comp = parts[0].Split(SC.COMPSEP);
				name = comp[0];
				// Convert.ToBoolean
				m_const = Convert.ToBoolean(comp[1]);
				m_standard = Convert.ToBoolean(comp[2]);

				string[] props = parts[1].Split(SC.COMPSEP);
				foreach (string p in props) {
					if (p != "" && p != "\n" && p != " ") {
						Property temp = new Property(p);
						ps.Add(temp);
						_propauto.Add(temp);
					}
					
				}
			}

			a = ps;
		}

		public string name { get; set; }
        public bool m_const { get; set; }
        public bool m_standard { get; set; }
        public bool m_selected { get; set; }

		public List<Property> _propauto = new List<Property>();

		public override string ToString() {
			string str = "";
			str += name;
			str += SC.COMPSEP;
			str += m_const;
			str += SC.COMPSEP;
			str += m_standard;
			str += SC.COMPSEP;
			str += SC.cSEPp;    // #

			foreach (Property p in _propauto) {
				str += p.ToString() + SC.COMPSEP;
			}

			return str;
		}

		public string ToString(int a) {
			string str = "";
			str += name;
			str += "\n";
			str += m_const;
			str += "\n";
			str += m_standard;
			str += "\n";
			str += "Properites";
			foreach (Property p in _propauto) {
				str += p.ToString(2) + "\n";
			}
			return str;
		}
	}

}
