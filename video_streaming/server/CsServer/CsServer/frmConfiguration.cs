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
    public partial class frmConfiguration : Form
    {
        public frmConfiguration()
        {
            InitializeComponent();
        }

        private void frmConfiguration_Load(object sender, EventArgs e)
        {
            txtTranscode.Text = RegistryAccessor.GetTranscode();
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            RegistryAccessor.PutTranscode(txtTranscode.Text);
            this.Hide();
        }
    }
}
