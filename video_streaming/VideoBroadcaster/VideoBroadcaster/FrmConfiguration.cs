using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VideoBroadcaster
{
    public partial class FrmConfiguration : Form
    {
        public delegate void ConfigurationChangedCallback();
        private ConfigurationChangedCallback cb = null;
        private string origTranscode = "";
        public static string DEFAULT = "transcode{vcodec=h264,vb=0,scale=0,acodec=mpga,ab=128,channels=2,samplerate=44100}";
        private VLCInfo info = null;

        public FrmConfiguration()
        {
            InitializeComponent();
            txtTranscoding.Text = RegistryAccessor.GetTranscode();
            origTranscode = txtTranscoding.Text;
        }

        public ConfigurationChangedCallback Callback
        {
            get { return cb; }
            set { cb = value; }
        }

        private void txtTranscoding_KeyDown(object sender, KeyEventArgs e)
        {
            rbtnCustom.Checked = true;
        }

        private void rbtnMp4_Click(object sender, EventArgs e)
        {
            txtTranscoding.Text = DEFAULT;
        }

        private void rbtnAsf_Click(object sender, EventArgs e)
        {
            txtTranscoding.Text = "transcode{vcodec=WMV2,vb=800,scale=1,acodec=wma2,ab=128,channels=2,samplerate=44100}";
        }

        private void rbtnTs_Click(object sender, EventArgs e)
        {
            txtTranscoding.Text = "transcode{vcodec=h264,vb=800,scale=1,acodec=mpga,ab=128,channels=2,samplerate=44100}";
        }

        private void rbtnWebm_Click(object sender, EventArgs e)
        {
            txtTranscoding.Text = "transcode{vcodec=VP80,vb=2000,scale=0,acodec=vorb,ab=128,channels=2,samplerate=44100}";
        }

        private void rbtnCustom_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (origTranscode.CompareTo(txtTranscoding.Text) != 0 && cb != null)
            {
                RegistryAccessor.PutTranscode(txtTranscoding.Text);
                cb();
            }
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void txtTranscoding_TextChanged(object sender, EventArgs e)
        {
            txtTTranscoding.Text = txtTranscoding.Text;
        }

        private void txtOutput_TextChanged(object sender, EventArgs e)
        {
            if (txtOutput.Text.Length > 0)
            {
                btnConvert.Enabled = true;
            }
            else
            {
                btnConvert.Enabled = false;
            }
        }

        private void btnConvert_Click(object sender, EventArgs e)
        {
            progress.Visible = true;
            timer.Enabled = true;

            string destination = ":file{dst="+txtOutput.Text+"} ";
            string transcode = RegistryAccessor.GetTranscode();
            string comb = transcode.Length == 0 ? "#" + destination : "#" + transcode + ":" + destination;

            if (info == null)
            {
                info = new VLCInfo();
            }
            info.sender.SetOptions(txtInput.Text, comb);
            info.sender.Play();
            progress.Maximum = 10000;
            progress.Value = 0;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            VLCInfo.MediaInfo mInfo = info.sender.ShowMediaObject();
            if (mInfo.instances.state.CompareTo("playing") == 0)
            {
                btnConvert.Enabled = false;
                btnOK.Enabled = false;
                btnCancel.Enabled = false;

                int val = (int)(mInfo.instances.position * 100.0f);
                progress.Value = val;
                if (mInfo.instances.position >= 99.99f)
                {
                    timer.Enabled = false;
                    progress.Visible = false;
                    btnConvert.Enabled = true;
                    btnOK.Enabled = true;
                    btnCancel.Enabled = true;
                    info.player.Destroy();
                    info.sender.Destroy();
                    info = null;
                }
                else if (!info.sender.IsPlaying())
                {
                    timer.Enabled = false;
                    progress.Visible = false;
                    btnConvert.Enabled = true;
                    btnOK.Enabled = true;
                    btnCancel.Enabled = true;
                    info.player.Destroy();
                    info.sender.Destroy();
                    info = null;
                }
            }
            else
            {
                btnConvert.Enabled = true;
                btnOK.Enabled = true;
                btnCancel.Enabled = true;
            }
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            OpenFileDialog odialog = new OpenFileDialog();
            odialog.Title = "Select Input file";
            odialog.Filter = "All files (*.*)|*.*";
            odialog.FilterIndex = 1;
            odialog.RestoreDirectory = true;

            if (odialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtInput.Text = odialog.FileName;

                SaveFileDialog dialog = new SaveFileDialog();
                dialog.Title = "Select Output file";
                dialog.Filter = "All files (*.*)|*.*";
                dialog.FilterIndex = 1;
                dialog.RestoreDirectory = true;
                if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    txtOutput.Text = dialog.FileName;
                }
            }
        }
    }
}
