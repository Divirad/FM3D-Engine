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

namespace VS_Extension
{
    public static class PipeSystem
    {
        enum Message : ushort
        {
            GET_COMPONENTS,
        }

        private static NamedPipeClientStream pipe;
        private static byte[] readBuffer = new byte[4096];

        public static bool Start(string pipename)
        {
            var current = Process.GetCurrentProcess();
            string id = current.Id.ToString();

            pipe = new NamedPipeClientStream(".", pipename, PipeDirection.InOut, PipeOptions.Asynchronous);
            try
            {
                pipe.Connect(1000);
            } catch(TimeoutException e)
            {
                MessageBox.Show("Connection to FM3D-Designer timed out\n" + e.Message + "\n\nTry to restart Visual Studio. Changes you make to the solution while not connected to the Designer can break your project!", "FM3D-Extension-Error");
                return false;
            }

            MessageBox.Show("Succesfully established a connection to the Designer!", "FM3D-Extension-Info");
            Read();
            return true;
        }

        private static void Read()
        {
            try
            {
                pipe.BeginRead(readBuffer, 0, 4, ReadCallback, null);
            }
            catch (InvalidOperationException) //disconnected/disposed
            {
                return;
            }
        }

        private static void ReadCallback(IAsyncResult ar)
        {
            int bytesRead;

            try
            {
                bytesRead = pipe.EndRead(ar);
            }
            catch (IOException) //closed
            {
                return;
            }

            MessageBox.Show(bytesRead.ToString(), "FM3D-Extension-INFO");

            Read();
        }
    }
}
