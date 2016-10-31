using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DevComponents.WPF.Metro;
using System.Windows.Media;

namespace FM3D_Designer.Themes
{
    public static class DarkTheme
    {
        
        public static void SetTheme()
        {
            Theme t = Theme.Current;

            t.MetroStyle = new MetroTheme("#2d2d30", "#00A7FF", "Dark Theme");

            //Colors
            t.MainFontColor = (Color)new ColorConverter().ConvertFrom("#ffffff");
            t.NoFocusFontColor = (Color)new ColorConverter().ConvertFrom("#ffffff");
            t.HighLightFontColor = (Color)new ColorConverter().ConvertFrom("#ffffff");
            t.NoFocusHighLightFontColor = (Color)new ColorConverter().ConvertFrom("#ffffff");
            t.HighLightColor = (Color)new ColorConverter().ConvertFrom("#3399ff");
            t.NoFocusHighLightColor = (Color)new ColorConverter().ConvertFrom("#4f4f56");

            //Brushes
            t.EditorBackGroundBrush = new BrushConverter().ConvertFrom("#1e1e1e") as Brush;
            t.ToolWindowBackGroundBrush = new BrushConverter().ConvertFrom("#252526") as Brush;                    
            t.MenuBackGroundBrush = new BrushConverter().ConvertFrom("#2d2d30") as Brush;
            t.MenuSelectedBrush = new BrushConverter().ConvertFrom("#3399ff") as Brush;

            //Brushes from Color
            t.MainFontBrush = new SolidColorBrush(t.MainFontColor);
            t.NoFocusFontBrush = new SolidColorBrush(t.NoFocusFontColor);
            t.HighLightFontBrush = new SolidColorBrush(t.HighLightFontColor);
            t.NoFocusHighLightFontBrush = new SolidColorBrush(t.NoFocusHighLightFontColor);
            t.HighLightBrush = new SolidColorBrush(t.HighLightColor);
            t.NoFocusHighLightBrush = new SolidColorBrush(t.NoFocusHighLightColor);

            t.UpdateAllProperties();
        }
    }
}
