using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;

namespace FM3D_Designer.src {

    public class Property {
        public Property() {

        }
        public Property(string props_str) {
			MessageBox.Show(props_str);
			if (props_str != "" && props_str != "\n" && props_str!=" ") {
				MessageBox.Show(props_str);
				string[] propdata = props_str.Split(SC.VAL);
				name = propdata[0];
				type = propdata[1];
				m_get = Convert.ToBoolean(propdata[2]);
				m_set = Convert.ToBoolean(propdata[3]);
			}
            
        }
        public string name { get; set; }
        public string type { get; set; }
        public bool m_get { get; set; }
        public bool m_set { get; set; }
        public bool m_selected { get; set; }

        public override string ToString() {
            string result = "";
            result +=
                name + SC.VAL +
                type + SC.VAL +
                m_get + SC.VAL +
                m_set;
            return result;
        }
        public string ToString(int i) {
            string result = "";
            result +=
                "Name: "+name +"\n"+
                "Type: " + type + "\n" +
                "Get: " + m_get + "\n" +
                "Set: "+m_set+ "\n";
            return result;
        }
    }
}
