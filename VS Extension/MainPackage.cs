//------------------------------------------------------------------------------
// <copyright file="MainPackage.cs" company="Company">
//     Copyright (c) Company.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.ComponentModel.Design;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.OLE.Interop;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.Win32;
using System.Windows.Forms;
using EnvDTE;
using System.Linq;
using VSLangProj;

namespace VS_Extension
{
    [PackageRegistration(UseManagedResourcesOnly = true)]
    [InstalledProductRegistration("#110", "#112", "1.0", IconResourceID = 400)] // Info on this package for Help/About
    [Guid(MainPackage.PackageGuidString)]
    [ProvideAutoLoad(UIContextGuids80.SolutionExists)]
    public sealed class MainPackage : Package, IVsSolutionEvents3
    {

        public const string PackageGuidString = "19abd3e3-d7cd-4675-8a73-f6c90ce7aa4f";

        private DTE dte;
        private IVsSolution solution = null;
        private uint cookie = uint.MaxValue;

        public MainPackage()
        {

        }

        protected override void Initialize()
        {
            base.Initialize();
            MessageBox.Show("Package Loaded!", "FM3D-Extension-Info");

            this.dte = (DTE)this.GetService(typeof(DTE));
            this.solution = this.GetService(typeof(SVsSolution)) as IVsSolution;
            if (this.solution != null)
            {
                this.solution.AdviseSolutionEvents(this, out cookie);
            } else
            {
                MessageBox.Show("Error on loading Solution!", "FM3D-Extension-Error");
            }
        }

        protected override void Dispose(bool disposing)
        {
            if (this.solution != null)
            {
                if (this.cookie != uint.MaxValue)
                {
                    this.solution.UnadviseSolutionEvents(this.cookie);
                    this.cookie = uint.MaxValue;
                }

                this.solution = null;
            }

            base.Dispose(disposing);
        }

        private Project[] GetProjects()
        {
            return this.dte.Solution.Projects
                .Cast<Project>()
                .Select(x => ((VSProject)x.Object).Project)
                .ToArray();
        }

        public int OnAfterLoadProject(IVsHierarchy pStubHierarchy, IVsHierarchy pRealHierarchy)
        {
            // Do something
            return VSConstants.S_OK;
        }

        public int OnAfterOpenSolution(object pUnkReserved, int fNewSolution)
        {
            //foreach (var project in GetProjects())
            //{
            //    MessageBox.Show("Project: " + project.Name, "FM3D-Extension-Info");
            //}

            var fm3d_file = new FM3DPropertyFile();
            if (fm3d_file.Load(this.solution))
            {
                MessageBox.Show(fm3d_file.FM3DName + "  " + fm3d_file.MainProjectName + "  " + fm3d_file.PipeName, "FM3D-Extension-Info");
                if(!PipeSystem.Start(fm3d_file.PipeName)) return VSConstants.S_FALSE;
            }
            
            return VSConstants.S_OK;
        }

        public int OnBeforeUnloadProject(IVsHierarchy pRealHierarchy, IVsHierarchy pStubHierarchy)
        {
            // Do something
            return VSConstants.S_OK;
        }

        public int OnAfterCloseSolution(object pUnkReserved)
        {
            return VSConstants.S_OK;
        }

        public int OnAfterClosingChildren(IVsHierarchy pHierarchy)
        {
            return VSConstants.S_OK;
        }

        public int OnAfterMergeSolution(object pUnkReserved)
        {
            return VSConstants.S_OK;
        }

        public int OnAfterOpenProject(IVsHierarchy pHierarchy, int fAdded)
        {
            return VSConstants.S_OK;
        }

        public int OnAfterOpeningChildren(IVsHierarchy pHierarchy)
        {
            return VSConstants.S_OK;
        }

        public int OnBeforeCloseProject(IVsHierarchy pHierarchy, int fRemoved)
        {
            return VSConstants.S_OK;
        }

        public int OnBeforeClosingChildren(IVsHierarchy pHierarchy)
        {
            return VSConstants.S_OK;
        }

        public int OnBeforeOpeningChildren(IVsHierarchy pHierarchy)
        {
            return VSConstants.S_OK;
        }

        public int OnBeforeCloseSolution(object pUnkReserved)
        {
            return VSConstants.S_OK;
        }

        public int OnQueryCloseProject(IVsHierarchy pHierarchy, int fRemoving, ref int pfCancel)
        {
            return VSConstants.S_OK;
        }

        public int OnQueryCloseSolution(object pUnkReserved, ref int pfCancel)
        {
            return VSConstants.S_OK;
        }

        public int OnQueryUnloadProject(IVsHierarchy pRealHierarchy, ref int pfCancel)
        {
            return VSConstants.S_OK;
        }
    }
}
