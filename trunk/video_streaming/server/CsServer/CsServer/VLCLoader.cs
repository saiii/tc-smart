using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;
using System.Text;

namespace CsServer
{
    public class VLCLoader
    {
        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Init")]
        public static extern void VLCInterface_Init();

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Destroy")]
        public static extern void VLCInterface_Destroy();

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Bcast_Init")]
        public static extern UInt32 VLCInterface_Bcast_Init();

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Bcast_Play")]
        public static extern void VLCInterface_Bcast_Play(UInt32 index, string name, string transcode);

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Bcast_Pause")]
        public static extern void VLCInterface_Bcast_Pause(UInt32 index);

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Bcast_Resume")]
        public static extern void VLCInterface_Bcast_Resume(UInt32 index);

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Bcast_Stop")]
        public static extern void VLCInterface_Bcast_Stop(UInt32 index);

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Player_Init")]
        unsafe public static extern UInt32 VLCInterface_Player_Init(void * hwnd);

        [DllImport("vlcinterface.dll", EntryPoint = "VLCInterface_Player_Stop")]
        public static extern void VLCInterface_Player_Stop(UInt32 index);
    }
}
