using MahApps.Metro.Controls;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows;

namespace FM3D_Designer.src.Dialogs
{
    class NewResourceLogic : INotifyPropertyChanged
    {
        public DialogBase Dialog { get; set; }

        #region Commands
        public Command TypeCommand { get; private set; }
        private void OnRadioChanged(object param)
        {
            selectedType = Convert.ToInt32(param as string);
        }
        private int selectedType;

        private void OnPathClick(object param)
        {
            var fileDialog = new OpenFileDialog();
            const string textureFiles = "Texture files|*.BMP;*.DDS;*.EXR;*.GIF;*.HDR;*.ICO;*.IFF;*.JNG;*.JPG;*.JPEG;*.MNG;*.PCX;*.PBM;*.PGM;*.PPM;*.PFM;*.PNG;*.PICT;*.PSD;*.SGI;*.TARGA;*.TIFF;*.WBMP;*.XBM;*.XPM";
            const string modelFiles = "Mesh files|*.FBM;*.DAE;*.GLTF;*.GLB;*.BLEND;*.3DS;*.ASE;*.OBJ;*.IFC;*.XGL;*.ZGL;*.PLY;*.DXF;*.LWO;*.LWS;*.LXO;*.STL;*.X;*.AC;*.MS3D;*.COB;*.SCN";
            const string allFiles = "All files|*.*";
            fileDialog.Filter = textureFiles + "|" + modelFiles + "|" + allFiles;
            switch(selectedType)
            {
                case 1:
                    fileDialog.FilterIndex = 1;
                    break;
                case 2:
                    fileDialog.FilterIndex = 2;
                    break;
                default:
                    fileDialog.FilterIndex = 3;
                    break;
            }
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                this.Path = fileDialog.FileName;
                OnPropertyChanged("Path");
            }
        }
        public Command PathCommand { get; private set; }

        private void OnAddClick(object param)
        {
            Dialog.Close();
            switch (selectedType)
            {
                case 0:
                    throw new NotImplementedException("Texture loading not implemented");
                case 1:
                    var window = System.Windows.Application.Current.MainWindow as MetroWindow;
                    window.ShowModelDialog(this.Path);
                    break;
            }
        }
        public Command AddCommand { get; private set; }
        #endregion

        public string Path { get; set; } = "";
        public NewResourceLogic()
        {
            TypeCommand = new Command(this.OnRadioChanged, null);
            PathCommand = new Command(this.OnPathClick, null);
            AddCommand = new Command(this.OnAddClick, null);
        }

        #region NotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name)
        {
            if (this.PropertyChanged != null) this.PropertyChanged(this, new PropertyChangedEventArgs(name));
        }
        #endregion
    }
}
