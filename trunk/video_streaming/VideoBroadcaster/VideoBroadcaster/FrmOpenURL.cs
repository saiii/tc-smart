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
    public partial class FrmOpenURL : Form
    {
        public delegate void URLCallback(string url);
        private URLCallback cb = null;

        public FrmOpenURL()
        {
            InitializeComponent();
        }

        public URLCallback Callback
        {
            get { return cb; }
            set { cb = value; }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (cb != null)
            {
                cb(txtURL.Text);
            }
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
