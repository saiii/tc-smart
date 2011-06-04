using System;
using System.Collections.Generic;
using Microsoft.Win32;
using System.Text;
using System.Security.Permissions;
using System.Windows.Forms;

namespace CsServer
{
    public class RegistryAccessor
    {
        public static string GetTranscode()
        {
            try
            {
                RegistryKey key = Registry.CurrentUser.OpenSubKey("TcSmartServer");
                if (key == null)
                {
                    key = Registry.CurrentUser.CreateSubKey("TcSmartServer");
                }

                object obj = key.GetValue("transcode");
                return obj == null ? "" : obj.ToString();
            }
            catch(Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            return "";
        }

        public static void PutTranscode(string value)
        {
            try
            {
                RegistryKey key = Registry.CurrentUser.OpenSubKey("TcSmartServer");
                if (key == null)
                {
                    key = Registry.CurrentUser.CreateSubKey("TcSmartServer");
                }

                key.SetValue("transcode", (object)value);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }
    }
}
