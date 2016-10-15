using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DevComponents.WPF.Metro;

namespace FM3D_Designer.Themes.Dark_Theme
{
    public class DarkMetroTheme
    {
        public static MetroTheme MetroStyle
        {
            get
            {
                return new MetroTheme("#2d2d30", "#00A7FF", "Dark Theme");
            }
        }
    }
}
