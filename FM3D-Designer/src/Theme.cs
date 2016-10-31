using DevComponents.WPF.Metro;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace FM3D_Designer
{
    public class Theme : INotifyPropertyChanged
    {
        public MetroTheme MetroStyle { get; set; }
        public Brush EditorBackGroundBrush { get; set; }
        public Brush ToolWindowBackGroundBrush { get; set; }
        public Brush MainFontBrush { get; set; }
        public Brush NoFocusFontBrush { get; set; }
        public Brush HighLightFontBrush { get; set; }
        public Brush NoFocusHighLightFontBrush { get; set; }
        public Color MainFontColor { get; set; }
        public Color NoFocusFontColor { get; set; }
        public Color HighLightFontColor { get; set; }
        public Color NoFocusHighLightFontColor { get; set; }
        public Brush MenuBackGroundBrush { get; set; }
        public Brush MenuSelectedBrush { get; set; }
        public Brush HighLightBrush { get; set; }
        public Brush NoFocusHighLightBrush { get; set; }
        public Color HighLightColor { get; set; }
        public Color NoFocusHighLightColor { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

        public void UpdateAllProperties()
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs("MetroStyle"));
                PropertyChanged(this, new PropertyChangedEventArgs("EditorBackGroundBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("ToolWindowBackGroundBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("MainFontBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("NoFocusFontBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("HighLightFontBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("NoFocusHighLightFontBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("MenuBackGroundBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("MenuSelectedBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("HighLightBrush"));
                PropertyChanged(this, new PropertyChangedEventArgs("NoFocusHighLightBrush"));
            }
        }

        private static Theme _Current = new Theme();

        public static Theme Current
        {
            get
            {
                return _Current;
            }
        }

        private Theme()
        {

        }
    }
}
