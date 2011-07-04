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
        public frmShutdown()
        {
            InitializeComponent();
        }

        private void frmShutdown_Load(object sender, EventArgs e)
        {
            const int MAX = 100;
            const int STEP = 25;
            pgStatus.Maximum = MAX;
            pgStatus.Value = 0;
            this.Visible = true;
            for (int i = 0; i < MAX; i += STEP)
            {
                pgStatus.Value += STEP;

                string xmlStartup = "<?xml version='1.0'?>\n";
                xmlStartup = xmlStartup + "<tcsm>";
                xmlStartup = xmlStartup + "<vs_msg>";
                xmlStartup = xmlStartup + "<mode value=\"shutdown\" />";
                xmlStartup = xmlStartup + "</vs_msg>";
                xmlStartup = xmlStartup + "</tcsm>";
                SAILoader.Sai_Net_Send(xmlStartup);

                Thread.Sleep(800);
            }
            this.Close();
        }
    }
}
