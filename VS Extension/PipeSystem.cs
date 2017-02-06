using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO.Pipes;
using System.Windows.Forms;
using System.IO;
using Microsoft.VisualStudio.VCCodeModel;

namespace VS_Extension
{
    public static class PipeSystem
    {

        private static NamedPipeClientStream pipe;
        private static byte[] readBuffer = new byte[4096];
        private static Thread thread;

        private static StreamWriter writer;
        private static StreamReader reader;
        public static bool Start(string pipename)
        {
            var current = Process.GetCurrentProcess();
            string id = current.Id.ToString();

            pipe = new NamedPipeClientStream(".", pipename, PipeDirection.InOut);
            try
            {
                pipe.Connect(1000);
            } catch(TimeoutException e)
            {
                MessageBox.Show("Connection to FM3D-Designer timed out\n" + e.Message + "\n\nTry to restart Visual Studio. Changes you make to the solution while not connected to the Designer can break your project!", "FM3D-Extension-Error");
                return false;
            }

            MessageBox.Show("Succesfully established a connection to the Designer!", "FM3D-Extension-Info");
            thread = new Thread(Communicate);
            thread.Start();
            return true;
        }

        private static void Communicate()
        {
            writer = new StreamWriter(pipe);
            reader = new StreamReader(pipe);

            string type = reader.ReadLine();
            switch(type)
            {
                case "GetComponents":
                    SendComponents();
                    break;
                case "AddClass":
                    AddClassPipe();
                    break;
            }
        }

        private static void SendComponents()
        {
            CodeAnalyzer code = new CodeAnalyzer(MainPackage.Instance.MainProject);
            var strings = code.GetComponents();

            writer.WriteLine(strings.Count.ToString());

            foreach(string s in strings)
            {
                writer.WriteLine(s);
            }
            writer.Flush();
        }

        private static void AddClassPipe()
        {
            string name = reader.ReadLine();
            string file = reader.ReadLine();

            CodeManipulator manipulator = null;
            try
            {
                manipulator = new CodeManipulator(file);
            }
            catch (ArgumentException e)
            {
                if (e.ParamName == "filename")
                {
                    writer.WriteLine("InvalidFile");
                    writer.Flush();
                    return;
                }
            }
            writer.WriteLine("ValidFile");
            writer.Flush();
            int baseCount = Convert.ToInt32(reader.ReadLine());

            var bases = new string[baseCount];
            for (int i = 0; i < baseCount; i++)
            {
                bases[i] = reader.ReadLine();
            }

            manipulator.AddClass(name, bases);
        }
    }
}
