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
                if(c != null) result.Add(c.FullName);
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


        public void AddClassExample2(FileCodeModel bruh)
        {
            try
            {
                object[] bases = { ConvertFullName(bruh, "Hallu") };
          
                // Create a new class.
                bruh.AddClass("TestClass", -1, 0, 0, vsCMAccess.vsCMAccessPublic);
            } catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        string ConvertFullName(FileCodeModel cm, string fullName)
        {
            // Convert a .NET type name into a C++ type name.
            if ((cm.Language == CodeModelLanguageConstants.vsCMLanguageVC) ||
                (cm.Language == CodeModelLanguageConstants.vsCMLanguageMC))
                return fullName.Replace(".", "::");
            else
                return fullName;
        }

        //######################################################################

        //public void AddClassExample2(DTE2 dte)
        //{
        //     Before running this example, open a code document from 
        //     a project.
        //    try
        //    {
        //        ProjectItem projItem = dte.ActiveDocument.ProjectItem;
        //        CodeModel cm = projItem.ContainingProject.CodeModel;

        //         Initialize the base classes array and the implemented 
        //         interfaces array.
        //        object[] bases = { ConvertFullName(cm, "System.Object") };
        //        object[] interfaces =   {
        //                                    ConvertFullName(cm, "System.IDisposable"),
        //                                    ConvertFullName(cm, "System.IComparable")
        //                                };

        //         Create a new class.
        //        projItem.FileCodeModel.AddClass("TestClass", -1, bases,
        //            interfaces, vsCMAccess.vsCMAccessPublic);
        //    } catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.Message);
        //    }
        //}

        //string ConvertFullName(CodeModel cm, string fullName)
        //{
        //     Convert a .NET type name into a C++ type name.
        //    if ((cm.Language == CodeModelLanguageConstants.vsCMLanguageVC) ||
        //        (cm.Language == CodeModelLanguageConstants.vsCMLanguageMC))
        //        return fullName.Replace(".", "::");
        //    else
        //        return fullName;
        //}


    }
}
