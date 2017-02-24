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
using System.Collections.Generic;
using EnvDTE80;
using Microsoft.VisualStudio.VCCodeModel;

namespace VS_Extension
{
    [PackageRegistration(UseManagedResourcesOnly = true)]
    [InstalledProductRegistration("#110", "#112", "1.0", IconResourceID = 400)] // Info on this package for Help/About
    [Guid(MainPackage.PackageGuidString)]
    [ProvideAutoLoad(UIContextGuids80.SolutionExists)]
    [ProvideMenuResource("Menus.ctmenu", 1)]
    public sealed class MainPackage : Package, IVsSolutionEvents3
    {
        public static MainPackage Instance { get; private set; }

        public const string PackageGuidString = "19abd3e3-d7cd-4675-8a73-f6c90ce7aa4f";

        public DTE2 dte { get; private set; }
        private Events dteEvents;
        private BuildEvents buildEvents;
        private CommandEvents commandEvents;
        private Commands2 commands;
        public IVsSolution Solution { get; private set; } = null;
        public List<Project> Projects { get; private set; }
        public Project MainProject
        {
            get
            {
                Projects = GetAllProjects();
                foreach (Project p in Projects)
                {
                    if (string.Compare(p.Name, fm3d_file.MainProjectName, false) == 0)
                    {
                        return p;
                    }
                }
                return null;
            }
        }
        private uint cookie = uint.MaxValue;
        private FM3DPropertyFile fm3d_file;

        public MainPackage()
        {
            if(Instance != null)
            {
                throw new InvalidOperationException("Only one object of MainPackage can be created");
            }
            Instance = this;
        }

        protected override void Initialize()
        {
            base.Initialize();
            MessageBox.Show("Package Loaded!", "FM3D-Extension-Info");

            this.dte = (DTE2)this.GetService(typeof(DTE));

            this.dteEvents = this.dte.Events;
            this.buildEvents = this.dteEvents.BuildEvents;
            this.buildEvents.OnBuildBegin += this.OnBuildBegin;
            this.buildEvents.OnBuildDone += this.OnBuildDone;
            this.commands = this.dte.Commands as Commands2;
            this.commandEvents = this.dteEvents.CommandEvents;
            this.commandEvents.AfterExecute += this.AfterExecute;
            this.commandEvents.BeforeExecute += this.BeforeExecute;
            this.Solution = this.GetService(typeof(SVsSolution)) as IVsSolution;
            if (this.Solution != null)
            {
                this.Solution.AdviseSolutionEvents(this, out cookie);
            } else
            {
                MessageBox.Show("Error on loading Solution!", "FM3D-Extension-Error");
            }
            Command1.Initialize(this);
        }

        protected override void Dispose(bool disposing)
        {
            if (this.Solution != null)
            {
                if (this.cookie != uint.MaxValue)
                {
                    this.Solution.UnadviseSolutionEvents(this.cookie);
                    this.cookie = uint.MaxValue;
                }

                this.Solution = null;
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

        #region Solution Events

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

            fm3d_file = new FM3DPropertyFile();
            if (fm3d_file.Load(this.Solution))
            {
                MessageBox.Show(fm3d_file.FM3DName + "  " + fm3d_file.MainProjectName + "  " + fm3d_file.PipeName, "FM3D-Extension-Info");

                if(MainProject == null)
                {
                    MessageBox.Show("Mainproject not found!", "FM3D-Extension Error");
                }

                PipeSystem.Start(fm3d_file.PipeName);
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

        private List<Project> GetAllProjects()
        {
            Projects projects = dte.Solution.Projects;
            List<Project> list = new List<Project>();
            var item = projects.GetEnumerator();
            while (item.MoveNext())
            {
                var project = item.Current as Project;
                if (project == null)
                {
                    continue;
                }

                if (project.Kind == ProjectKinds.vsProjectKindSolutionFolder)
                {
                    list.AddRange(GetSolutionFolderProjects(project));
                }
                else
                {
                    list.Add(project);
                }
            }

            return list;
        }

        private static IEnumerable<Project> GetSolutionFolderProjects(Project solutionFolder)
        {
            List<Project> list = new List<Project>();
            for (var i = 1; i <= solutionFolder.ProjectItems.Count; i++)
            {
                var subProject = solutionFolder.ProjectItems.Item(i).SubProject;
                if (subProject == null)
                {
                    continue;
                }

                // If this is another solution folder, do a recursive call, otherwise add
                if (subProject.Kind == ProjectKinds.vsProjectKindSolutionFolder)
                {
                    list.AddRange(GetSolutionFolderProjects(subProject));
                }
                else
                {
                    list.Add(subProject);
                }
            }
            return list;
        }
        #endregion

        #region Build Events
        void OnBuildBegin(vsBuildScope Scope, vsBuildAction Action)
        {
            MessageBox.Show("Build started!\n" + Scope.ToString() + "\n" + Action.ToString());
        }

        void OnBuildDone(vsBuildScope Scope, vsBuildAction Action)
        {
            MessageBox.Show("Build done!\n" + Scope.ToString() + "\n" + Action.ToString());
        }
        #endregion
        #region Command Events

        void BeforeExecute(string Guid, int ID, object CustomIn, object CustomOut, ref bool CancelDefault)
        {
            string name = GetCommandName(Guid, ID);
            
            if(name == "Debug.StartWithoutDebugging" || name == "Debug.Start")
            {

            }
       }

        void AfterExecute(string Guid, int ID, object CustomIn, object CustomOut)
        {
            //MessageBox.Show("After Execution!\n" + Guid + "\n" + ID + "\n" + CustomIn?.ToString() + "\n" + CustomOut?.ToString());
        }

        private string GetCommandName(string Guid, int ID)
        {
            if (Guid == null)
                return "null";

            string result = "";
            if (commands != null)
            {
                try
                {
                    return commands.Item(Guid, ID).Name;
                }
                catch (System.Exception)
                {
                }
            }
            return result;
        }

        public void SendBuildCommand()
        {
        }

        public void SendStartCommand(bool debugging)
        {
            //this.commands.
        }
        #endregion
    }
}
