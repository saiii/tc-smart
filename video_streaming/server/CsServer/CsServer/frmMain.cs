using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
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

        unsafe public frmMain()
        {
            InitializeComponent();
            _bcastIndex = VLCLoader.VLCInterface_Bcast_Init();
            _playerIndex = VLCLoader.VLCInterface_Player_Init(this.pnlMain.Handle.ToPointer());

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
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
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
        }

        private void configurationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frmConfiguration config = new frmConfiguration();
            config.ShowDialog();
        }

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            VLCLoader.VLCInterface_Destroy();
        }
    }
}
