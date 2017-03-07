using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.VCCodeModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VS_Extension
{
    class CodeAnalyzer
    {
        private VCCodeModel model;
        private Project p;

        public CodeAnalyzer(Project p)
        {
            model = p.CodeModel as VCCodeModel;
            this.p = p;
        }

        public List<string> GetComponents()
        {
            List<string> result = new List<string>();
            result.AddRange(GetComponentClasses(model.Classes));
            result.AddRange(GetComponentNamespace(model.Namespaces));
            result.Sort();
            return result;
        }

        private List<string> GetComponentClasses(CodeElements classes)
        {
            if (classes == null) return new List<string>();
            List<string> result = new List<string>();
            var enumerator = classes.GetEnumerator();
            while (enumerator.MoveNext())
            {
                var c = enumerator.Current as VCCodeClass;
                if (c != null)
                {
                    c.Bases.Cast<CodeElement>().Any(b => (b as VCCodeClass)?.FullName == "FM3D::Component");
                    result.Add(c.FullName);
                }
            }
            return result;
        }

        private List<string> GetComponentNamespace(CodeElements name_space)
        {
            if (name_space == null) return new List<string>();
            List<string> result = new List<string>();

            var enumer = name_space.GetEnumerator();
            while (enumer.MoveNext())
            {
                var ns = enumer.Current as VCCodeNamespace;
                if (ns.Classes != null) result.AddRange(GetComponentClasses(ns.Classes));

                if (ns.Namespaces != null) result.AddRange(GetComponentNamespace(ns.Namespaces));
            }
            return result;
        }

        public void AddClassAnalyzer(string name) {
            var file = p.ProjectItems.Item(1).FileCodeModel;
            file.AddClass("");
            AddClassExample2(file);

        }
		

    }
}
