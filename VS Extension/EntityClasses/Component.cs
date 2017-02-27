using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VS_Extension {

    class Component {
        public Component() { }
        public Component(string comp_str) {
            string[] compdata = comp_str.Split(SC.SEPVAL);
            name = compdata[0];
            m_custom = Convert.ToBoolean(compdata[1]);
            m_const = Convert.ToBoolean(compdata[2]);
            m_standard = Convert.ToBoolean(compdata[3]);
        }
        public string name { get; set; }
        public bool m_custom { get; set; }
        public bool m_const { get; set; }
        public bool m_standard { get; set; }
        public bool m_selected { get; set; }

        public override string ToString() {
            string result = "";
            result +=
                name + SC.SEPVAL +
                m_custom + SC.SEPVAL +
                m_const + SC.SEPVAL +
                m_standard;
            return result;
        }
        public string ToString(int i) {
            string result = "";
            result +=
                "Name: " + name + "\n" +
                "Custom: " + m_custom + "\n" +
                "Const:" + m_const + "\n" +
                "Standard: " + m_standard;
            return result;
        }
    }

}
