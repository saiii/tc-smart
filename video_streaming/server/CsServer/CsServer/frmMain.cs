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

        public frmMain()
        {
            InitializeComponent();
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
                MessageBox.Show(openFileDialog.FileName + ", Sure?");
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
            if (btnPlay.Text == "Play")
            {
                btnPlay.Text = "Pause";
            }
            else
            {
                btnPlay.Text = "Play";
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {

        }
    }
}
