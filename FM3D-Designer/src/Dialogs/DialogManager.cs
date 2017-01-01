using MahApps.Metro.Controls;
using MahApps.Metro.Controls.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FM3D_Designer.src.Dialogs
{
    public static class DialogManager
    {
        public static void ShowNewResourceDialog(this MetroWindow window, String path)
        {
            window.ShowMetroDialogAsync(new NewResourceDialog(window, path));
        }
    }
}
