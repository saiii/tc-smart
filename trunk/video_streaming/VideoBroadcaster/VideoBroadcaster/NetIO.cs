using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Timers;
using System.Text.RegularExpressions;
using System.Net.NetworkInformation;
using System.Net;

namespace VideoBroadcaster
{
    class NetIO
    {
        private LinkedList<Sender> list = null;
        private Refresher refresher = null;

        public NetIO()
        {
            list = new LinkedList<Sender>();
            refresher = new Refresher(this);
        }

        public void Initialize()
        {
            string[] nics = GetNicList();
            foreach (string nic in nics)
            {
                Sender sender = new Sender();
                if (sender.Initialize(nic))
                {
                    list.AddLast(sender);
                }
                else 
                {
                    sender.Shutdown();
                }
            }
            refresher.Start();
        }

        public void Send(string msg)
        {
            foreach (Sender sender in list)
            {
                sender.Send(msg);
            }
        }

        public void Repeat(string msg, int times)
        {
            for (int i = 0; i < times; i += 1)
            {
                refresher.list.AddLast(msg);
            }
        }

        public class Refresher
        {
            private System.Timers.Timer tmr = null;
            private NetIO io = null;
            public LinkedList<string> list = null;

            public Refresher(NetIO io)
            {
                this.io = io;
                tmr = new System.Timers.Timer(500);
                tmr.Elapsed += new ElapsedEventHandler(OnTimer);
                list = new LinkedList<string>();
            }

            public void Start()
            {
                tmr.Interval = 500;
                tmr.Enabled = true;
            }

            public void OnTimer(object source, ElapsedEventArgs e)
            {
                if (list.Count > 0)
                {
                    string msg = list.ElementAt<string>(0);
                    list.RemoveFirst();
                    io.Send(msg);
                }
            }
        }

        class Sender
        {
            private ASCIIEncoding enc = null;
            private Socket socket = null;
            public Sender()
            {
                enc = new ASCIIEncoding();
            }

            public bool Initialize(string address)
            {
                bool ret = false;
                try
                {
                    socket = new Socket(AddressFamily.InterNetwork, System.Net.Sockets.SocketType.Dgram, System.Net.Sockets.ProtocolType.Udp);

                    System.Net.IPAddress ip2 = System.Net.IPAddress.Parse(address);
                    byte [] intf = ip2.GetAddressBytes();
                    socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.MulticastInterface, intf);
                    
                    System.Net.IPAddress ip = System.Net.IPAddress.Parse("225.1.1.1");
                    IPEndPoint ipep = new IPEndPoint(ip, 8010);
                    socket.Connect(ipep);

                    ret = Send("<?xml version='1.0'?>\n<tcsm><vs_msg><mode value=\"start\"/></vs_msg></tcsm>");
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                    ret = false;
                }
                return ret;
            }

            public void Shutdown()
            {
                try
                {
                    socket.Close();
                }
                catch (Exception)
                { }
            }

            public bool Send(string msg)
            {
                bool ret = false;
                try
                {
                    byte[] buf = enc.GetBytes(msg);
                    int bytes = socket.Send(buf, buf.Length, SocketFlags.None);
                    ret = (bytes == buf.Length);
                }
                catch (Exception)
                {
                    ret = false;
                }
                return ret;
            }
        }

        public string [] GetNicList()
        {
            ArrayList ret = new ArrayList();
            Regex regex = new Regex("^[0-9]+[.][0-9]+[.][0-9]+[.][0-9]+$");
            foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
            {
                IPInterfaceProperties prop = nic.GetIPProperties();
                if (nic.Supports(NetworkInterfaceComponent.IPv4) && nic.SupportsMulticast)
                {
                    UnicastIPAddressInformationCollection uni = prop.UnicastAddresses;
                    if (uni != null)
                    {
                        foreach (IPAddressInformation i in uni)
                        {
                            string realIP = i.Address.ToString();
                            if (regex.Match(realIP).Success && realIP.CompareTo("127.0.0.1") != 0)
                            {
                                ret.Add(realIP);
                            }
                        }
                    }
                }
            }

            return (string[])ret.ToArray(typeof(string));
        }
    }
}
