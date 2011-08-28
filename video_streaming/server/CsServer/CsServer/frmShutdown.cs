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
    public partial class frmShutdown : Form
    {
        const int MAX = 100;
        const int STEP = 25;

        public frmShutdown()
        {
            InitializeComponent();
        }

        private void frmShutdown_Load(object sender, EventArgs e)
        {
            this.timer.Enabled = true;

            pgStatus.Maximum = MAX;
            pgStatus.Value = 0;
            this.Visible = true;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if (Global.EXIT)
            {
                timer.Enabled = false;
                this.Close();
                return;
            }

            if (!Global.DISABLE_NET)
            {
                pgStatus.Value += STEP;

                string xmlStartup = "<?xml version='1.0'?>\n";
                xmlStartup = xmlStartup + "<tcsm>";
                xmlStartup = xmlStartup + "<vs_msg>";
                xmlStartup = xmlStartup + "<mode value=\"shutdown\" />";
                xmlStartup = xmlStartup + "</vs_msg>";
                xmlStartup = xmlStartup + "</tcsm>";
                SAILoader.Sai_Net_Send(100, xmlStartup);

                string xmlLock = "<?xml version='1.0'?>\n";
                xmlLock = xmlLock + "<tcsm>";
                xmlLock = xmlLock + "<ls_msg>";
                xmlLock = xmlLock + "<lock value=\"false\" />";
                xmlLock = xmlLock + "</ls_msg>";
                xmlLock = xmlLock + "</tcsm>";
                SAILoader.Sai_Net_Send(101, xmlLock);
            }
            else
            {
                this.Close();
            }

            if (pgStatus.Value >= MAX)
            {
                this.Close();
            }
        }
    }
}
