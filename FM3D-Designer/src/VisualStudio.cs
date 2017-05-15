using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Windows;
using MahApps.Metro.Controls.Dialogs;
using MahApps.Metro.Controls;
using System.IO;
using System.Collections.ObjectModel;
using System.Windows.Media;

namespace FM3D_Designer.src
{
    public class VisualStudio
    {
        private Mutex mutex = new Mutex();
        private bool _IsStarting = false;
        private bool _IsStarted = false;

        public bool IsStarting
        {
            get
            {
                lock (mutex)
                {
                    return _IsStarting;
                }
            }
        }
        public bool IsStarted
        {
            get
            {
                lock (mutex)
                {
                    return _IsStarted;
                }
            }
        }
        private bool IsActive
        {
            get
            {
                return IsStarting || IsStarted;
            }
        }

        private Process process;
        private PipeSystem pipeSystem = new PipeSystem();

        public void Start(string pipename, string solution)
        {
            if (IsActive) return;
            lock (mutex)
            {
                _IsStarting = true;
            }
            try
            {
                process = Process.Start("devenv.exe", "\"" + solution + "\"");
                process.Exited += OnClosing;
                process.EnableRaisingEvents = true;
            }
            catch (Exception e)
            {
                lock (mutex)
                {
                    _IsStarting = false;
                }
                MainWindow.Instance.Invoke(new Action(() => { MainWindow.Instance.ShowMessageAsync("ERROR: 0205-01", "Could not start Visual Studio!\n" + e.Message, MessageDialogStyle.Affirmative); }));
                return;
            }
            pipeSystem.ConnectEvent += this.OnConnected;
            pipeSystem.DisconnectEvent += this.OnDisconnected;

            pipeSystem.Start(pipename);
        }

        public void Close()
        {
            lock (mutex)
            {
                if (process != null)
                {
                    if(!process.HasExited)
                    {
                        process.Exited -= this.OnClosing;

                        process.CloseMainWindow();
                        process.Close();
                    }
                    process.Dispose();
                    process = null;
                }

                _IsStarting = false;
                _IsStarted = false;

                pipeSystem.Close();
            }
        }

        private void OnClosing(object sender, EventArgs e)
        {
			//Close();
			//MainWindow.Instance.Invoke(new Action(() => {
			//	MainWindow.Instance.StatusColor = new SolidColorBrush(Color.FromRgb(255, 00, 00));
			//}));
			//MainWindow.Instance.Invoke(new Action(() => {
			//	MainWindow.Instance.tb_statbar.Text = "Please Start VisualStudio";
			//}));

			MainWindow.Instance.Invoke(new Action(() => {
				MainWindow.Instance.StatusColor = new SolidColorBrush(Color.FromRgb(255, 00, 00));
				MainWindow.Instance.tb_statbar.Text = "Please Start VisualStudio";
				MainWindow.Instance.ShowMessageAsync("Visual Studio Info", "Lost Connection of Visual Studio. Maybe it was closed?\nYou can restart it from the toolbar.", MessageDialogStyle.Affirmative);

			}));
        }



        private void OnConnected(object sender, EventArgs args)
        {
            lock(mutex)
            {
                _IsStarting = false;
                _IsStarted = true;
            }
        }

        private void OnDisconnected(object sender, EventArgs args)
        {
            Close();
        }

        public void AddClass(string name, string file, string[] bases = null) {
            lock (mutex)
            {
                if (!_IsStarted)
                    throw new InvalidOperationException("ERROR: 0205-00"); 
                pipeSystem.SendAddClass(name, file, bases);
            }
        }

        public bool GetComponents(out ObservableCollection<string> components)
        {
            lock (mutex)
            {
                if (!_IsStarted)
                    throw new InvalidOperationException("ERROR: 0205-00");
                return pipeSystem.GetComponents(out components);
            }

        }

        public void Start(bool debugging)
        {
            lock (mutex)
            {
                if (!_IsStarted)
                    throw new InvalidOperationException("ERROR: 0205-00");
                
                pipeSystem.SendStart(debugging);
            }
        }

        public void Build()
        {
            lock (mutex)
            {
                if (!_IsStarted)
                    throw new InvalidOperationException("ERROR: 0205-00");
                pipeSystem.SendBuild();
            }
        }

        public void SendEntities(List<string> entities) {
            lock (mutex) {
                    if (!_IsStarted)
                        throw new InvalidOperationException("ERROR: 0205-00");
                    pipeSystem.SendAllEntities(entities);
            }
        }
    }
}

