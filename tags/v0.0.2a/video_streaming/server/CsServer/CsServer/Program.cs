using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace CsServer
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            try
            {
                System.Reflection.Assembly a = System.Reflection.Assembly.GetEntryAssembly();
                string dir = System.IO.Path.GetDirectoryName(a.Location);
                System.IO.Directory.SetCurrentDirectory(dir);
                VLCLoader.VLCInterface_Init();
                SAIThread.start();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
                return;
            }           

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frmMain());
        }
    }
}
