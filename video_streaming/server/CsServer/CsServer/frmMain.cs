using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Text.RegularExpressions;

using System.Net.Sockets;

namespace CsServer
{
    public partial class frmMain : Form
    {
        private bool _sizeChanged = false;
        private bool _playing = false;
        private UInt32 _bcastIndex = 0;
        private UInt32 _playerIndex = 0;
        private UInt32 _startMessages = 0;
        private Int64 _movieLength = 0;

        private frmConfiguration _frmConfig = null;

        unsafe public frmMain()
        {
            InitializeComponent();
            _bcastIndex = VLCLoader.VLCInterface_Bcast_Init();
            _playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "rtp://224.1.1.1:5004");
            //_playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "http://www.youtube.com/watch?v=vGvQ6LtkPwc");
            //_playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "http://v10.nonxt3.c.youtube.com/videoplayback?sparams=id%2Cexpire%2Cip%2Cipbits%2Citag%2Calgorithm%2Cburst%2Cfactor%2Coc%3AU0hQR1JLUV9FSkNOMF9KRVVH&algorithm=throttle-factor&itag=34&ip=0.0.0.0&burst=40&sver=3&signature=537E74A9A349F6692D169046B293F9755FDC061D.7210E2149BED4CF2CC713C799E17E804363BE217&expire=1312203600&key=yt1&ipbits=0&factor=1.25&id=cb58c007210235cd&redirect_counter=1");
            //                                                                                   "http://v15.nonxt2.c.youtube.com/videoplayback?sparams=id%2Cexpire%2Cip%2Cipbits%2Citag%2Calgorithm%2Cburst%2Cfactor%2Coc%3AU0hQR1dNU19FSkNOMF9PR1dH&algorithm=throttle-factor&itag=34&ip=0.0.0.0&burst=40&sver=3&signature=158B8A0871965C1E84448292F58B9EAFC7C564B8.1CDA71B1E61F510F987F9EC4B43102AF7150B3B1&expire=1312725600&key=yt1&ipbits=0&factor=1.25&id=bc6bd0e8bb643f07&redirect_counter=1"
            //                                                        "http://o-o.preferred.jastel-bkk1.v9.lscache2.c.youtube.com/videoplayback?sparams=id%2Cexpire%2Cip%2Cipbits%2Citag%2Cratebypass%2Coc%3AU0hQR1lNTl9FSkNOMF9RR1JB&itag=43&ip=0.0.0.0&signature=D078A8D2639C6A3F53C5F9FD22DBA6FF6B34276B.5FBAF2BD0FB10D297F48A42BEF9F3ACBA99CBE58&sver=3&ratebypass=yes&expire=1312920000&key=yt1&ipbits=0&id=bc6bd0e8bb643f07"
            //                                                        "http://o-o.preferred.jastel-bkk1.v9.lscache2.c.youtube.com/videoplayback?sparams=id%2Cexpire%2Cip%2Cipbits%2Citag%2Calgorithm%2Cburst%2Cfactor%2Coc%3AU0hQR1lNTl9FSkNOMF9RR1JB&algorithm=throttle-factor&itag=43&ip=0.0.0.0&burst=40&sver=3&signature=D078A8D2639C6A3F53C5F9FD22DBA6FF6B34276B.5FBAF2BD0FB10D297F48A42BEF9F3ACBA99CBE58&expire=1312920000&key=yt1&ipbits=0&factor=1.25&id=bc6bd0e8bb643f07&redirect_counter=1"
            //_playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "D:\\VdoTest\\Osen.avi");

            string first = RegistryAccessor.GetFirst();
            if (first.Length == 0)
            {
                RegistryAccessor.PutTranscode("transcode{vcodec=h264,vb=0,scale=0,acodec=mp3,ab=128,channels=2,samplerate=44100}");
                RegistryAccessor.PutFirst("false");
            }

            //getVideoLink("http://www.youtube.com/watch?v=vGvQ6LtkPwc");
        }

        private void frmMain_Resize(object sender, EventArgs e)
        {
            _sizeChanged = true;
        }

        private void tmrRefresh_Tick(object sender, EventArgs e)
        {
            if (_startMessages > 3 && _frmConfig == null)
            {
                _frmConfig = new frmConfiguration();
            }

            if (_sizeChanged)
            {
                _sizeChanged = false;
                tlpMain.Width = this.Width - 8;
                tlpMain.Height = this.Height;
                tlpMain.Location = new Point(0, 24);
            }

            if (++_startMessages < 5)
            {
                string xmlStartup = "<?xml version='1.0'?>\n";
                xmlStartup = xmlStartup + "<tcsm>";
                xmlStartup = xmlStartup + "<vs_msg>";
                xmlStartup = xmlStartup + "<mode value=\"start\" />";
                xmlStartup = xmlStartup + "</vs_msg>";
                xmlStartup = xmlStartup + "</tcsm>";
                SAILoader.Sai_Net_Send(100, xmlStartup);
            }

            string xml = "<?xml version='1.0'?>\n";
            xml = xml + "<tcsm>";
            xml = xml + "<vs_msg>";
            xml = xml + "<time value=\"" + DateTime.Now.ToString() + "\" />";
            xml = xml + "</vs_msg>";
            xml = xml + "</tcsm>";

            SAILoader.Sai_Net_Send(100, xml);

            if (_playing)
            {
                string xmlLock = "<?xml version='1.0'?>\n";
                xmlLock = xmlLock + "<tcsm>";
                xmlLock = xmlLock + "<ls_msg>";
                xmlLock = xmlLock + "<lock value=\"true\" />";
                xmlLock = xmlLock + "</ls_msg>";
                xmlLock = xmlLock + "</tcsm>";
                SAILoader.Sai_Net_Send(101, xmlLock);
                /*
                if (_movieLength == 0)
                {
                    _movieLength = (Int64)VLCLoader.VLCInterface_Bcast_GetLength(_bcastIndex);
                    trackBar.Minimum = 0;
                    trackBar.Maximum = 20000;
                }
                else
                {
                    Int64 test = VLCLoader.VLCInterface_Bcast_GetLength(_bcastIndex);
                    Int64 val = VLCLoader.VLCInterface_Player_GetPosition(_bcastIndex);
                    if (val > _movieLength)
                    {
                        Console.WriteLine("Oh Shit");
                    }
                    float value = ((val * 20000.0f) / _movieLength);
                    trackBar.Value = (int)value;
                }
                 * */
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _movieLength = 0;
            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.Filter = "All files (*.*)|*.*";
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                if (_playing)
                {
                    VLCLoader.VLCInterface_Bcast_Stop(_bcastIndex);
                    _bcastIndex = VLCLoader.VLCInterface_Bcast_Init();
                }

                string destination = "rtp{dst=224.1.1.1,port=5004,mux=ts}";
                string transcode = RegistryAccessor.GetTranscode();
                string comb = transcode.Length == 0 ? "#" + destination : "#" + transcode + ":" + destination;
                VLCLoader.VLCInterface_Bcast_Play(_bcastIndex, openFileDialog.FileName, comb);
                btnPlay.Text = "Pause";
                _playing = true;

                _movieLength = VLCLoader.VLCInterface_Bcast_GetLength(_bcastIndex);
                trackBar.Minimum = 0;
                trackBar.Maximum = 20000;
                trackBar.Value = 0;
            }
            
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frmShutdown s = new frmShutdown();
            s.ShowDialog();
            this.Close();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox about = new AboutBox();
            about.ShowDialog();
        }

        private void btnPlay_Click(object sender, EventArgs e)
        {
            if (btnPlay.Text == "Resume")
            {
                btnPlay.Text = "Pause";
                VLCLoader.VLCInterface_Bcast_Resume(_bcastIndex);
            }
            else if (btnPlay.Text == "Pause")
            {
                btnPlay.Text = "Resume";
                VLCLoader.VLCInterface_Bcast_Pause(_bcastIndex);
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            VLCLoader.VLCInterface_Bcast_Stop(_bcastIndex);
            _bcastIndex = VLCLoader.VLCInterface_Bcast_Init();
            _playing = false;

            string xmlLock = "<?xml version='1.0'?>\n";
            xmlLock = xmlLock + "<tcsm>";
            xmlLock = xmlLock + "<ls_msg>";
            xmlLock = xmlLock + "<lock value=\"false\" />";
            xmlLock = xmlLock + "</ls_msg>";
            xmlLock = xmlLock + "</tcsm>";
            SAILoader.Sai_Net_Send(101, xmlLock);
        }

        private void configurationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmrRefresh.Enabled = false;
            Global.DISABLE_NET = true;

            if (_frmConfig == null)
            {
                _frmConfig = new frmConfiguration();
            }
            _frmConfig.ShowDialog();

            MessageBox.Show("Changing configuration requires restart application", "Warning", MessageBoxButtons.OK);
            frmShutdown s = new frmShutdown();
            s.ShowDialog();
            this.Close();
        }

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                Global.EXIT = true;
                Thread.Sleep(1000);
                VLCLoader.VLCInterface_Destroy();
                SAILoader.Sai_Net_Stop();
                //MessageBox.Show("Exit laew!!");
                Thread.Sleep(500);
                SAIThread.thread.Abort();
                Application.Exit();
            }catch(Exception exp)
            {}
        }

        public void processDataEvent(string addr, string msg)
        {
            this.Invoke((MethodInvoker)delegate
            {
                this.dataEvent(addr, msg);
            });
        }

        private void dataEvent(string addr, string msg)
        {
            //MessageBox.Show("Received data -> " + addr + " " + msg);
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            try
            {
                SAILoader.GetInstance().Sai_SetCallback(processDataEvent);
            }
            catch (DllNotFoundException dnfe)
            {
                MessageBox.Show("Could not load the dll file!");
                Application.Exit();
            }
        }

        private void trackBar_Scroll(object sender, EventArgs e)
        {
            if (_playing)
            {
                //float current = (((float)trackBar.Value * 100.0f) / 20000.0f);
                //Console.WriteLine(">> " + (UInt32)current);
                //VLCLoader.VLCInterface_Bcast_Pause(_bcastIndex);
                //_playing = false;
                //Thread.Sleep(1000);
                //Int32 ret = VLCLoader.VLCInterface_Bcast_SetPosition(_bcastIndex, (UInt32)30);
                //Thread.Sleep(1000);
                //VLCLoader.VLCInterface_Bcast_Resume(_bcastIndex);
                //Console.WriteLine("### " + ret);
                //_movieLength = 0;
                //_playing = true;
            }
        }

        private void openURLToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frmOpenURL frm = new frmOpenURL();
            frm.ShowDialog();

            if (Global.URL.Length > 0)
            {
                string tmp = Global.URL;
                Global.URL = getVideoLink(Global.URL);
                if (Global.URL.Length == 0)
                {
                    Global.URL = tmp;
                }

                if (Global.URL.Length > 0)
                {
                    if (_playing)
                    {
                        VLCLoader.VLCInterface_Bcast_Stop(_bcastIndex);
                        _bcastIndex = VLCLoader.VLCInterface_Bcast_Init();
                    }

                    Console.WriteLine(">> " + Global.URL);

                    string destination = "rtp{dst=224.1.1.1,port=5004,mux=ts}";
                    string transcode = RegistryAccessor.GetTranscode();
                    string comb = transcode.Length == 0 ? "#" + destination : "#" + transcode + ":" + destination;
                    VLCLoader.VLCInterface_Bcast_Play(_bcastIndex, Global.URL, comb);
                    btnPlay.Text = "Pause";
                    _playing = true;
                }
            }
        }

        private string getVideoLink(string baseURL)
        {
            //HttpWebRequest request = (HttpWebRequest)WebRequest.Create(baseURL);
            //request.UserAgent = "User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:5.0) Gecko/20100101 Firefox/5.0";
            //request.Referer = baseURL;
            //request.KeepAlive = true;

            //request.Accept = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nCookie: VISITOR_INFO1_LIVE=80fwYlvmisI; PREF=f1=50000000&fms2=10000&fv=10.3.181&fms1=10000";
            ////request.Accept = "*/*";
            ////CookieContainer cookie = new CookieContainer();
            ////request.CookieContainer = cookie;
            //HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            //Stream stream = response.GetResponseStream();

            //MyHttpWebRequest client = new MyHttpWebRequest();
            //Stream stream = client.OpenRead(baseURL);

            IPAddress [] addr = Dns.GetHostAddresses("www.youtube.com");
            byte[] data = new byte[402400];
            IPEndPoint ipep = new IPEndPoint(addr[0], 80);
            Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);
            }
            catch (SocketException e)
            {
                Console.WriteLine("Unable to connect to server.");
            }

            string req = "GET /watch?v=vGvQ6LtkPwc HTTP/1.1\r\n";
            req = req + "HOST: www.youtube.com\r\n";
            req = req + "User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:5.0) Gecko/20100101 Firefox/5.0\r\n";
            req = req + "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
            req = req + "Accept-Language: en-us,en;q=0.5\r\n";
            req = req + "Accept-Encoding: us-ascii\r\n";
            req = req + "Connection: keep-alive\r\n";
            req = req + "Cookie: VISITOR_INFO1_LIVE=80fwYlvmisI; PREF=f1=50000000&fms2=10000&fv=10.3.181&fms1=10000\r\n";
            req = req + "\r\n";

            System.Text.ASCIIEncoding enc = new ASCIIEncoding();
            byte [] b = enc.GetBytes(req);
            server.Send(b);

            Thread.Sleep(2000);
            int receive = server.Receive(data);

            string str = Encoding.ASCII.GetString(data, 0, receive);
            server.Shutdown(SocketShutdown.Both);
            server.Close();

            int index = str.IndexOf("\r\n\r\n");
            if (index > 0)
            {
                str = str.Substring(index+10);
            }

            bool start = false;
            Regex ex1 = new Regex("embed.*type=\"application/x-shockwave-flash");
            Regex ex2 = new Regex(".*>.*");

            String ret = "";

            //StreamReader reader = new StreamReader(stream, Encoding.ASCII);
            StringReader reader = new StringReader(str);
            while (reader.Peek() >= 0)
            {
                String line = reader.ReadLine();
                MatchCollection matches = ex1.Matches(line);
                bool newlyAdded = false;
                if (!start && matches.Count > 0)
                {
                    ret += line;
                    start = true;
                    newlyAdded = true;
                }

                if (start)
                {
                    matches = ex2.Matches(line);
                    if (!newlyAdded)
                    {
                        ret += line;
                    }
                    
                    if (matches.Count > 0)
                    {
                        break;
                    }
                }
            }

            string[] parts = ret.Split(new string[] { " " }, StringSplitOptions.None);
            foreach (string txt in parts)
            {
                if (txt.StartsWith("flashvars="))
                {
                    ret = Uri.UnescapeDataString(txt);
                    string tmp = ret;

                    int point = tmp.IndexOf("url_encoded_fmt_stream_map=");
                    tmp = tmp.Substring(point + 31);
                    point = tmp.IndexOf("fallback_host");
                    tmp = tmp.Substring(0, point - 1);

                    point = tmp.IndexOf("quality");
                    if (point > 0)
                    {
                        tmp = tmp.Substring(0, point-1);
                    }

                    string [,] mapping = {{"&amp;", "&"}, 
                                         {"%21", "!"}, {"%22", "\""}, {"%23", "#"}, {"%24", "$"}, 
                                         {"%25", "%"}, {"%26", "&"}, {"%27", "'"}, {"%28", "("}, 
                                         {"%29", ")"}, {"%2A", "*"}, {"%2B", "+"}, /*{"%2C", ","},*/ 
                                         {"%2D", "-"}, {"%2E", "."}, {"%2F", "/"},  
                                         /*{"%3A", ":"},*/ {"%3B", ";"}, {"%3C", "<"}, {"%3D", "="}, {"%3E", ">"},
                                         {"%3F", "?"}, {"%40", "@"}, {"%5B", "["}, {"%5C", "\\"},
                                         {"%5D", "]"}, {"%5E", "^"}, {"%5F", "_"}, {"%60", "`"},
                                         {"%7B", "{"}, {"%7C", "|"}, {"%7D", "}"}, {"%7E", "~"}};
                    int size = mapping.Length / 2;
                    for (int i = 0; i < size; i += 1)
                    {
                        string m  = mapping[i, 0];
                        string m1 = m;
                        string m2 = m.ToLower();
                        tmp = tmp.Replace(m1, mapping[i, 1]);
                        tmp = tmp.Replace(m2, mapping[i, 1]);
                    }

                    string p1, p2;
                    p1 = tmp.Substring(0, 10);
                    p2 = tmp.Substring(10);
                    p1 = p1.Replace("%3A", ":");
                    tmp = p1 + p2;
                    //Console.WriteLine(tmp);
                    ret = tmp;
                    break;
                }
            }
            
            return ret;
        }
    }
}
