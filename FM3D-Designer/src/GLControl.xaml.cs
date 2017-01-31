using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using DesignerLib;
using System.Runtime.InteropServices;

namespace FM3D_Designer.src
{
    /// <summary>
    /// Interaction logic for GLControl.xaml
    /// </summary>
    public partial class GLControl : UserControl
    {
        private OpenGL gl = new OpenGL();
        public Renderable renderable { get; private set; }
        public Camera camera { get; private set; }  = new Camera(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        public Mesh mesh { get; set; }

        public GLControl()
        {
            InitializeComponent();
        }

        private void GLControl_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            lock(gl)
            {
                //gl.ChangeSize(e.NewSize);
            }
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            lock(gl)
            {
                this.renderable = gl.Initialize(100, 100, camera, mesh);
            }
        }

        protected override void OnRender(DrawingContext drawingContext)
        {
            base.OnRender(drawingContext);

            lock(gl)
            {
                gl.Update(renderable);
                gl.Render(this.image);
            }
        }
    }
}
