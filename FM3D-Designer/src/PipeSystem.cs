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

namespace FM3D_Designer.src
{
    public class PipeSystem
    { 
        private NamedPipeServerStream pipe;
        private byte[] readBuffer = new byte[4096];

        public event EventHandler ConnectEvent;
        public event EventHandler DisconnectEvent;

        private StreamWriter writer;
        private StreamReader reader;

        public void Start(string pipename)
        {
            pipe = new NamedPipeServerStream(pipename, PipeDirection.InOut, 1, PipeTransmissionMode.Message, PipeOptions.Asynchronous);
            pipe.BeginWaitForConnection(new AsyncCallback(OnConnected), pipe);
        }

        public void Close()
        {
            if (pipe != null)
            {
                if (pipe.IsConnected)
                    pipe.Disconnect();
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
            //Read();
        }

        private void Disconnected()
        {
            if (pipe != null)
            {
                pipe.Dispose();
                pipe = null;
            }
            if (DisconnectEvent != null) DisconnectEvent(this, new EventArgs());
        }

        public bool GetComponents(out ObservableCollection<string> components)
        {
            writer.WriteLine("GetComponents");
            //writer.Flush();
            components = new ObservableCollection<string>();
            int count = Convert.ToInt32(reader.ReadLine());
            for (int i = 0; i < count; i++)
            {
                components.Add(reader.ReadLine());
            }

            return true;
        }

        public void SendAddClass(string name, string file, string[] bases) {
            writer.WriteLine("AddClass");

            writer.WriteLine(name);
            //writer.Flush();
            writer.WriteLine(file);
           // writer.Flush();
            var result = reader.ReadLine();
            if(result == "InvalidFile")
            {
                throw new ArgumentException(file + " is not a valid code file", "file");
            }
            //if(bases != null)
            //{
            //    writer.WriteLine(bases.Length);
            //    foreach(var b in bases)
            //    {
            //        writer.WriteLine(b);
            //    }
            //} else
            //{
                writer.WriteLine("0");
            //}
            // writer.Flush();
        }

    }
}
