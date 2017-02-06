using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.VCCodeModel;
using EnvDTE;
using System.Windows.Forms;

namespace VS_Extension
{
    public class CodeManipulator
    {
        VCFileCodeModel model;
        public CodeManipulator(string filename)
        {
            if (!FindModel(MainPackage.Instance.MainProject.ProjectItems, filename))
                throw new ArgumentException("Not a valid filename for a code file", "filename");
        }

        private bool FindModel(ProjectItems p, string filename)
        {

            foreach (ProjectItem pi in p)
            {
                if (pi.Name == filename)
                {
                    model = pi.FileCodeModel as VCFileCodeModel;
                    return true;
                }
                else
                {
                    if (FindModel(pi.ProjectItems, filename)) return true;
                }
            }
            return false;
        }

        public CodeClass AddClass(string name, object bases = null)
        {
            return model.AddClass(name, 0, bases);
        }
    }
}
