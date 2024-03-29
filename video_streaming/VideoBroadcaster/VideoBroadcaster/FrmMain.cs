﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace VideoBroadcaster
{
    public partial class FrmMain : Form
    {
        private VLCInfo info = null;
        private NetIO net = null;
        public static string DST = "rtp{dst=224.1.1.1,port=5004,mux=ts}";

        public FrmMain()
        {
            InitializeComponent();

            string first = RegistryAccessor.GetFirst();
            if (first.Length == 0)
            {
                RegistryAccessor.PutTranscode(FrmConfiguration.DEFAULT);
                RegistryAccessor.PutFirst("false");
            }
            net = new NetIO();
        }

        private void FrmMain_SizeChanged(object sender, EventArgs e)
        {
            layoutTable.Size = new Size(this.Width, this.Height - this.menu.Height);
            layoutTable.Location = new Point(0, this.menu.Height);
        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            FrmMain_SizeChanged(null, null);
            info = new VLCInfo();
            info.player.Start(pnlMain.Handle);
            net.Initialize();

            string xml = "<?xml version='1.0'?>\n<tcsm><vs_msg><mode value=\"start\"/><detail value=\""+ DST +"\"/></vs_msg></tcsm>";
            net.Repeat(xml, 6);
        }

        private void OnExit()
        {
            info.player.Stop();
            info.player.Destroy();

            info.sender.Stop();
            info.sender.Destroy();

            string xml = "<?xml version='1.0'?>\n<tcsm><vs_msg><mode value=\"shutdown\"/></vs_msg></tcsm>";
            net.Repeat(xml, 5);

            try
            {
                Thread.Sleep(1000);
                Application.Exit();
            }
            catch (Exception)
            { }
        }

        private void menuAbout_Click(object sender, EventArgs e)
        {
            FrmAbout about = new FrmAbout();
            about.ShowDialog();
            about = null;
        }

        private void menuOpen_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.Filter = "All files (*.*)|*.*";
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                if (timer.Enabled)
                {
                    btnStop_Click(null, null);
                }
                string destination = DST;
                string transcode = RegistryAccessor.GetTranscode();
                string comb = transcode.Length == 0 ? "#" + destination : "#" + transcode + ":" + destination;
                info.sender.SetOptions(openFileDialog.FileName, comb);

                trackBar.Minimum = 0;
                trackBar.Maximum = 10000;
                trackBar.Value = 0;

                info.sender.Play();
                timer.Enabled = true;
            }
        }

        private void menuOpenURL_Click(object sender, EventArgs e)
        {
            FrmOpenURL openURL = new FrmOpenURL();
            openURL.Callback = OpenURL;
            openURL.ShowDialog();
        }

        public void OpenURL(string url)
        {
            if (url.Length > 0)
            {
                if (timer.Enabled)
                {
                    btnStop_Click(null, null);
                }

                string destination = "rtp{dst=224.1.1.1,port=5004,mux=ts}";
                string transcode = RegistryAccessor.GetTranscode();
                string comb = transcode.Length == 0 ? "#" + destination : "#" + transcode + ":" + destination;
                info.sender.SetOptions(url, comb);

                trackBar.Minimum = 0;
                trackBar.Maximum = 10000;
                trackBar.Value = 0;

                info.sender.Play();
                timer.Enabled = true;
            }
        }

        private void menuConfig_Click(object sender, EventArgs e)
        {
            FrmConfiguration config = new FrmConfiguration();
            config.Callback = ConfigurationChanged;
            config.ShowDialog();
        }

        public void ConfigurationChanged()
        {
            MessageBox.Show("Configuration changed the application needs to be restarted...");
            string xml = "<?xml version='1.0'?>\n<tcsm><vs_msg><mode value=\"shutdown\"/></vs_msg></tcsm>";
            net.Repeat(xml, 5);
            FrmShutdown frmShutdown = new FrmShutdown();
            frmShutdown.ShowDialog();
        }

        private void menuExit_Click(object sender, EventArgs e)
        {
            string xml = "<?xml version='1.0'?>\n<tcsm><vs_msg><mode value=\"shutdown\"/></vs_msg></tcsm>";
            net.Repeat(xml, 5);
            FrmShutdown frmShutdown = new FrmShutdown();
            frmShutdown.ShowDialog();
        }

        private void FrmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            OnExit();
        }

        private void btnPlay_Click(object sender, EventArgs e)
        {
            info.sender.Play();
        }

        private void btnPause_Click(object sender, EventArgs e)
        {
            info.sender.Pause();
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            info.sender.Stop();
            btnPlay.Enabled = true;
            btnPause.Enabled = false;
            btnStop.Enabled = false;
            trackBar.Enabled = false;
            trackBar.Value = 0;
            timer.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            info.sender.Pause();
            info.sender.Seek(0.50f);
            info.sender.Play();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            VLCInfo.MediaInfo mInfo = info.sender.ShowMediaObject();
            if (mInfo.instances.state.CompareTo("playing") == 0)
            {
                string xml = "<?xml version='1.0'?>\n<tcsm><vs_msg><time value=\""+ DateTime.Now.ToString() +"\"/></vs_msg></tcsm>";
                net.Send(xml);

                btnPlay.Enabled = false;
                trackBar.Enabled = true;
                btnPause.Enabled = true;
                btnStop.Enabled = true;
                int val = (int)(mInfo.instances.position * 100.0f);
                bool validPos = false;
                if (val >= trackBar.Minimum && val < trackBar.Maximum)
                {
                    trackBar.Value = val;
                    validPos = true;
                }
                if ((validPos && mInfo.instances.position >= 99.99f) || !info.sender.IsPlaying())
                {
                    timer.Enabled = false;
                    trackBar.Enabled = false;
                    trackBar.Value = trackBar.Maximum;
                }
            }
            else
            {
                btnPlay.Enabled = true;
                btnPause.Enabled = false;
                btnStop.Enabled = false;
            }
        }

        private void trackBar_MouseUp(object sender, MouseEventArgs e)
        {
            if (trackBar.Maximum > trackBar.Minimum)
            {
                float percent = (100.0f * trackBar.Value) / trackBar.Maximum;
                percent /= 100.0f;
                info.sender.Pause();
                info.sender.Seek(percent);
                info.sender.Play();
            }
        }
    }
}
