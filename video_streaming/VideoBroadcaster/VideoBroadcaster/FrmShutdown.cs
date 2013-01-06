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
    public partial class FrmShutdown : Form
    {
        public FrmShutdown()
        {
            InitializeComponent();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if (progress.Value > 0)
            {
                progress.Value -= 1;
            }
            else
            {
                timer.Enabled = false;
                Application.Exit();
            }
        }
    }
}
