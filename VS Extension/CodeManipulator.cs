using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.VCCodeModel;
using EnvDTE;
using System.Windows.Forms;

namespace VS_Extension {

    public class CodeManipulator {
        VCFileCodeModel model;
        public CodeManipulator(string filename) {
            if (!FindModel(MainPackage.Instance.MainProject.ProjectItems, filename))
                throw new ArgumentException("Not a valid filename for a code file", "filename");
        }

        private bool FindModel(ProjectItems p, string filename) {

            foreach (ProjectItem pi in p) {
                if (pi.Name == filename) {
                    model = pi.FileCodeModel as VCFileCodeModel;
                    return true;
                } else {
                    if (FindModel(pi.ProjectItems, filename)) return true;
                }
            }
            return false;
        }

        //DIS DUS ALSO WURK
        public void AddNamespace(string namespacename) {
            bool isthere = false;
            foreach (CodeElement namespace_ in model.Namespaces) {

                if (namespacename == namespace_.FullName) {
                    isthere = true;
                }
            }
            if (isthere) {
            } else {
                model.AddNamespace(namespacename);
            }
        }

        //DIS DUS WURK
        public void AddClass(string name, string namespacename, object bases = null) {
            bool isthere = false;

            foreach(VCCodeNamespace space in model.Namespaces) {
                if (space.Name==namespacename) {

                    foreach (VCCodeClass class_ in space.Classes) {
                        if (name == class_.Name) {
                            isthere = true;
                        }
                    }
                    if (isthere) {
                    } else {
                        space.AddClass(name);
                    }
                    break;
                }
            }

        }

        public void AddMethod(string namespacename, string clazzname, string name, vsCMFunction kind, object type, vsCMAccess access = vsCMAccess.vsCMAccessDefault, object bases = null) {
            bool isthere = false;
             
            foreach (VCCodeNamespace space in model.Namespaces) {
                if (space.Name == namespacename) {

                    foreach (VCCodeClass clazz in space.Classes) {
                        if (clazzname == clazz.Name) {
                            foreach(VCCodeFunction funk in clazz.Functions) {

                            }
                            if (isthere) {
                            } else {
                                space.AddFunction(name, kind, type, null, access);
                            }
                        }
                    }
                    break;
                }
            }
        }

        public void AddVariable(string classname, string namespacename, string name, object type, object position, vsCMAccess access, object location) {
            bool isthere = false;
            
            foreach(VCCodeNamespace space in model.Namespaces) {
                if (space.Name==namespacename) {
                    foreach(VCCodeClass class_ in space.Classes) {
                        if (class_.Name==classname) {
                            foreach (VCCodeVariable variable in class_.Variables) {
                                if (variable.Name==classname) {
                                    isthere = true;
                                }
                            }
                            if (isthere) {
                            } else {
                                class_.AddVariable(classname, type, position, access, location);
                            }

                        }

                    }
                }
            }
        }



        public void AddClass(string name, object bases = null) {
            bool isthere = false;
            foreach (CodeElement class_ in model.Classes) {
                if (name == class_.FullName) {
                    isthere = true;
                }
            }
            if (isthere) {
            } else {
                model.AddClass(name);
            }
        }


    }
}
