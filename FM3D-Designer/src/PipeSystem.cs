using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using MahApps.Metro.Controls.Dialogs;
using MahApps.Metro.Controls;
using System.Threading;

namespace FM3D_Designer.src
{
    public class PipeSystem
    {
        #region Pipe stuff
        private const string COMMAND = "Command: ";

        private NamedPipeServerStream pipe;
        private byte[] readBuffer = new byte[4096];

        public event EventHandler ConnectEvent;
        public event EventHandler DisconnectEvent;

        private StreamWriter writer;
        private StreamReader reader;

        private Mutex actionMutex = new Mutex();
        private Mutex readMutex = new Mutex();
        private string readString;
        private Thread readThread;
        private string ReadString
        {
            get
            {
                while (true)
                {
                    lock (actionMutex)
                    {
                        if (readString.Length > 0)
                        {
                            string local = readString;
                            readString = "";
                            return local;
                        }
                    }
                    Thread.Sleep(2);
                }
            }
        }

        public void Start(string pipename)
        {
            pipe = new NamedPipeServerStream(pipename, PipeDirection.InOut, 1, PipeTransmissionMode.Message, PipeOptions.Asynchronous);
            pipe.BeginWaitForConnection(new AsyncCallback(OnConnected), pipe);
        }

        ~PipeSystem()
        {
            //Close pipe in destructor for safetiness
            Close();
        }

        public void Close()
        {
            readThread?.Abort();
            readThread = null;
            if (pipe?.IsConnected == true) { 
                writer?.Close();
                reader?.Close();
                writer?.Dispose();
                reader?.Dispose();
                pipe.Disconnect();
            }
            writer = null;
            reader = null;
            if (pipe != null)
            {
                pipe.Close();
                pipe.Dispose();
                pipe = null;
            }
        }

        private void OnConnected(IAsyncResult res)
        {
            try
            {
                ((NamedPipeServerStream)res.AsyncState).EndWaitForConnection(res);
            }
            catch (ObjectDisposedException)
            {
                Disconnected();
                return;
            }

            if (ConnectEvent != null) ConnectEvent(this, new EventArgs());
            writer = new StreamWriter(pipe);
            writer.AutoFlush = true;
            reader = new StreamReader(pipe);
            Read();
        }

        private void Disconnected()
        {
            Close();
            if (DisconnectEvent != null) DisconnectEvent(this, new EventArgs());
        }

        private void Read()
        {
            readThread = Thread.CurrentThread;

            try
            {
                while (pipe != null)
                {
                    string s = reader.ReadLine();
                    if (s == null) continue;
                    if (s.StartsWith(COMMAND))
                    {
                        lock (actionMutex)
                        {
                            switch (s.Substring(COMMAND.Length))
                            {
                                default:
                                    MainWindow.Instance.ShowMessageAsync("Connection failure", "Received unreadable message from Visual Studio");
                                    break;
                            }
                        }
                    }
                    else
                    {
                        lock (readMutex)
                        {
                            readString = s;
                        }
                    }
                }
            } catch(ThreadAbortException)
            {
                return;
            }
        }
        #endregion

        #region Actions
        public bool GetComponents(out ObservableCollection<string> components)
        {
            lock (actionMutex)
            {
                writer.WriteLine(COMMAND + "GetComponents");
                components = new ObservableCollection<string>();
                int count = Convert.ToInt32(ReadString);
                for (int i = 0; i < count; i++)
                {
                    components.Add(ReadString);
                }

                return true;
            }
        }

        public void SendAddClass(string name, string file, string[] bases)
        {
            lock (actionMutex)
            {
                writer.WriteLine(COMMAND + "AddClass");

                writer.WriteLine(name);
                writer.WriteLine(file);
                var result = ReadString;
                if (result == "InvalidFile")
                {
                    throw new ArgumentException(file + " is not a valid code file", "file");
                }
                if (bases != null)
                {
                    writer.WriteLine(bases.Length);
                    foreach (var b in bases)
                    {
                        writer.WriteLine(b);
                    }
                }
                else
                {
                    writer.WriteLine("0");
                }
            }
        }

        public void SendStart(bool debugging)
        {
            lock (actionMutex)
            {
                writer.WriteLine(COMMAND + "Start");
                writer.WriteLine(debugging.ToString());
            }
        }

        public void SendBuild()
        {
            lock (actionMutex)
            {
                writer.WriteLine(COMMAND + "Build");
            }
        }

        #endregion

    }
}
