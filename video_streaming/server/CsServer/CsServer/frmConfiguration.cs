using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text.RegularExpressions;
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
            System.Windows.Forms.ToolTip ToolTip1 = new System.Windows.Forms.ToolTip();
            ToolTip1.SetToolTip(this.lstIP, "In case of multiple network interface cards, a selection of network interface card to be used is required");

            txtTranscode.Text = RegistryAccessor.GetTranscode();

            string list = SAILoader.Sai_Net_GetNicList();
            string[] entry = list.Split(new Char[] { '!' });

            lstIP.BeginUpdate();
            lstIP.Items.Clear();
            foreach (string et in entry)
            {
                string[] part = et.Split(new Char[] { ',' });
                if (part.Length == 3)
                {
                    if (part[1] == "127.0.0.1")
                    {
                        continue;
                    }

                    lstIP.Items.Add(part[1]);
                }
                else
                {
                    if (part[0] == "127.0.0.1")
                    {
                        continue;
                    }

                    lstIP.Items.Add(part[0]);
                }
            }
            lstIP.EndUpdate();

            string ip = RegistryAccessor.GetIP();
            if (ip.Length == 0 || ip == "0.0.0.0")
            {
                lstIP.SelectedItem = lstIP.Items[0];
            }
            else
            {
                bool found = false;
                Regex reg = new Regex(ip);
                for (int i = 0; i < lstIP.Items.Count; i += 1)
                {
                    string txt = lstIP.Items[i].ToString();
                    if (reg.IsMatch(txt))
                    {
                        lstIP.SelectedItem = lstIP.Items[i];
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    lstIP.SelectedItem = lstIP.Items[0];
                }
            }
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            RegistryAccessor.PutTranscode(txtTranscode.Text);

            string selected = lstIP.SelectedItem.ToString();
            System.Collections.ArrayList list = new System.Collections.ArrayList();
            foreach (object obj in lstIP.Items)
            {
                string sobj = (string)obj;
                if (sobj != selected)
                {
                    list.Add(sobj);
                }
            }

            string[] r = selected.Split(new Char[] { '.' });
            int max = 0;
            System.Collections.ArrayList list2 = new System.Collections.ArrayList();
            foreach (string s in list)
            {
                int cnt = 0;
                string[] part = s.Split(new Char[] { '.' });
                for (Int32 i = 0; i < 4; i += 1)
                {
                    if (part[i] == r[i])
                    {
                        cnt += 1;
                    }
                    else
                    {
                        break;
                    }
                }
                if (cnt > max)
                {
                    max = cnt;
                }
            }

            string result = "";
            switch (max)
            {
                case 0:
                    // No duplication at all
                    result = r[0] + "[.]" + r[1] + "[.]" + r[2] + "[.].*";
                    break;
                case 1:
                    // Duplicate only the first part
                    result = r[0] + "[.]" + r[1] + "[.].*";
                    break;
                case 2:
                    // Duplicate the first two parts
                    result = r[0] + "[.]" + r[1] + "[.]" + r[2] + "[.].*";
                    break;
                case 3:
                    // Duplicate the first three parts
                    result = selected;
                    break;
                default:
                    result = selected;
                    break;
            }

            RegistryAccessor.PutIP(result);

            this.Close();
        }
    }
}
