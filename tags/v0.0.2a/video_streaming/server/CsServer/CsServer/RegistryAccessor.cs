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
        private const string _PATH = "Software\\tc-smart\\Settings";

        private static string GetReg(string name)
        {
            try
            {
                RegistryKey reg = Registry.CurrentUser.CreateSubKey(_PATH);

                string val = (string)reg.GetValue(name);
                return val == null ? "" : val;
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            return "";
        }

        private static void PutReg(string name, string value)
        {
            try
            {
                RegistryKey reg = Registry.CurrentUser.CreateSubKey(_PATH);
                reg.SetValue(name, value);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        public static string GetFirst()
        {
            return GetReg("first");
        }

        public static void PutFirst(string val)
        {
            PutReg("first", val);
        }

        public static string GetTranscode()
        {
            return GetReg("transcode");
        }

        public static void PutTranscode(string value)
        {
            PutReg("transcode", value);
        }

        public static string GetIP()
        {
            return GetReg("ip");
        }

        public static void PutIP(string value)
        {
            PutReg("ip", value);
        }
    }
}
