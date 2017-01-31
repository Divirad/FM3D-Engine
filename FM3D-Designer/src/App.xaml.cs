using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace FM3D_Designer.src
{
    /// <summary>
    /// Interaktionslogik für "App.xaml"
    /// </summary>
    public partial class App : Application
    {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            if (e.Args.Length == 1)
            {
                FileInfo file = new FileInfo(e.Args[0]);
                if (file.Exists) 
                {
                    FM3D_Designer.src.WindowLayout.start_path = e.Args[0];
                }
            }
        }
    }
}
