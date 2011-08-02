using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading;
using System.Text;
using System.Windows.Forms;

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

        unsafe public frmMain()
        {
            InitializeComponent();
            _bcastIndex = VLCLoader.VLCInterface_Bcast_Init();
            _playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "rtp://224.1.1.1:5004");
            //_playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "http://www.youtube.com/watch?v=vGvQ6LtkPwc");
            //_playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "http://v10.nonxt3.c.youtube.com/videoplayback?sparams=id%2Cexpire%2Cip%2Cipbits%2Citag%2Calgorithm%2Cburst%2Cfactor%2Coc%3AU0hQR1JLUV9FSkNOMF9KRVVH&algorithm=throttle-factor&itag=34&ip=0.0.0.0&burst=40&sver=3&signature=537E74A9A349F6692D169046B293F9755FDC061D.7210E2149BED4CF2CC713C799E17E804363BE217&expire=1312203600&key=yt1&ipbits=0&factor=1.25&id=cb58c007210235cd&redirect_counter=1");
            //_playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer(), "D:\\VdoTest\\Osen.avi");

            string first = RegistryAccessor.GetFirst();
            if (first.Length == 0)
            {
                RegistryAccessor.PutTranscode("transcode{vcodec=h264,vb=0,scale=0,acodec=mp3,ab=128,channels=2,samplerate=44100}");
                RegistryAccessor.PutFirst("false");
            }
        }

        private void frmMain_Resize(object sender, EventArgs e)
        {
            _sizeChanged = true;
        }

        private void tmrRefresh_Tick(object sender, EventArgs e)
        {
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
            Application.Exit();
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
            frmConfiguration config = new frmConfiguration();
            config.ShowDialog();
        }

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            frmShutdown s = new frmShutdown();
            s.ShowDialog();
            VLCLoader.VLCInterface_Destroy();
            SAILoader.Sai_Net_Stop();
            SAIThread.thread.Abort();
            Application.Exit();
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
                if (_playing)
                {
                    VLCLoader.VLCInterface_Bcast_Stop(_bcastIndex);
                    _bcastIndex = VLCLoader.VLCInterface_Bcast_Init();
                }

                string destination = "rtp{dst=224.1.1.1,port=5004,mux=ts}";
                string transcode = RegistryAccessor.GetTranscode();
                string comb = transcode.Length == 0 ? "#" + destination : "#" + transcode + ":" + destination;
                VLCLoader.VLCInterface_Bcast_Play(_bcastIndex, Global.URL, comb);
                btnPlay.Text = "Pause";
                _playing = true;
            }
        }
    }
}
