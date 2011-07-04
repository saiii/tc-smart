using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace CsServer
{
    class SAILoader
    {
        public delegate void MsgCallback(string addr, string message);

        private MsgCallback _cb;
        private static SAILoader _instance = null;

        private SAILoader()
        { 
        }

        public static SAILoader GetInstance()
        {
            if (_instance == null)
            {
                _instance = new SAILoader();
            }
            return _instance;
        }

        [DllImport("SaiWrapper.dll", EntryPoint = "Sai_Get_Version")]
        public static extern string Sai_Get_Version();

        [DllImport("SaiWrapper.dll", EntryPoint = "Sai_Net_GetNicList")]
        public static extern string Sai_Net_GetNicList();

        [DllImport("SaiWrapper.dll", EntryPoint = "Sai_Net_Start")]
        public static extern void Sai_Net_Start(UInt32 port, string localAddress, string sendMcast, string recvMcast);

        [DllImport("SaiWrapper.dll", EntryPoint = "Sai_Net_Stop")]
        public static extern void Sai_Net_Stop();

        [DllImport("SaiWrapper.dll", EntryPoint = "Sai_Net_Send")]
        public static extern void Sai_Net_Send(string msg);

        [DllImport("SaiWrapper.dll", EntryPoint = "Sai_Net_SetCallback")]
        private static extern void Sai_Net_SetCallback(MsgCallback cb);

        public void Sai_SetCallback(MsgCallback cb)
        {
            _cb = new MsgCallback(cb);
            Sai_Net_SetCallback(_cb);
        }
    }

    public class SAIThread
    {
        public static Thread thread = null;
        public static void start()
        {
            SAIThread t = new SAIThread();
            thread = new Thread(new ThreadStart(t.run));
            thread.Start();
        }

        public void run()
        {
            try
            {
                string ip = RegistryAccessor.GetIP();
                if (ip.Length == 0)
                {
                    ip = "0.0.0.0";
                    RegistryAccessor.PutIP("0.0.0.0");
                }
                SAILoader.Sai_Net_Start(8010, ip, "225.1.1.1", "225.2.2.2");
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
    }
}
