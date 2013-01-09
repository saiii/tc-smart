using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace VideoBroadcaster
{
    class VLCLoader
    {
        #region core
        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_new", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr libvlc_new(int argc, IntPtr argv);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_new", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr libvlc_new(int argc, [MarshalAs(UnmanagedType.LPArray)] String[] argv);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_new", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr libvlc_new(int argc, IntPtr[] argv);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_get_version", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        private static extern IntPtr libvlc_get_version();

        public static String GetVersion()
        {
            IntPtr ptr = libvlc_get_version();
            return Marshal.PtrToStringAnsi(ptr);
        }

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_media_new_path", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        private static extern IntPtr libvlc_media_new_path(IntPtr p_instance, IntPtr psz_mrl);

        public static IntPtr MediaNewPath(IntPtr p_instance, string path)
        {
            IntPtr ptr = IntPtr.Zero;
            try
            {
                byte[] bytes = Encoding.UTF8.GetBytes(path);
                ptr = Marshal.AllocHGlobal(bytes.Length + 1);
                Marshal.Copy(bytes, 0, ptr, bytes.Length);
                Marshal.WriteByte(ptr, bytes.Length, 0);
                //
                return (libvlc_media_new_path(p_instance, ptr));
            }
            finally
            {
                if (ptr != IntPtr.Zero)
                {
                    Marshal.FreeHGlobal(ptr);
                }
            }
        }

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_media_player_new_from_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr libvlc_media_player_new_from_media(IntPtr libvlc_media);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_media_player_set_hwnd", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void libvlc_media_player_set_hwnd(IntPtr libvlc_mediaplayer, IntPtr libvlc_drawable);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_media_player_play", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_media_player_play(IntPtr libvlc_mediaplayer);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_media_release", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void libvlc_media_release(IntPtr libvlc_media_inst);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_media_player_stop", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void libvlc_media_player_stop(IntPtr libvlc_mediaplayer);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_media_player_release", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void libvlc_media_player_release(IntPtr libvlc_mediaplayer);

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_release", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void libvlc_release(IntPtr libvlc_instance_t);

        #endregion

        #region VLM
        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_release", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void libvlc_vlm_release(IntPtr p_instance);
        // Release the vlm instance related to the given libvlc_instance_t.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_add_broadcast", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_add_broadcast(IntPtr p_instance, string psz_name, string psz_input, string sz_output, int i_options, [MarshalAs(UnmanagedType.LPArray)] String[] ppsz_options, int b_enabled, int b_loop);
        // Add a broadcast, with one input.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_add_vod", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_add_vod(IntPtr p_instance, string psz_name, string psz_input, int i_options, [MarshalAs(UnmanagedType.LPArray)] String[] ppsz_options, int b_enabled, string psz_mux); 
        // Add a vod, with one input.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_del_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_del_media(IntPtr p_instance, string psz_name);
        // Delete a media (VOD or broadcast).

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_set_enabled", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_set_enabled(IntPtr p_instance, string psz_name, int b_enabled);
 	    // Enable or disable a media (VOD or broadcast).

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_set_output", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_set_output(IntPtr p_instance, string psz_name, string psz_output);
 	    // Set the output for a media.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_set_input", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_set_input(IntPtr p_instance, string psz_name, string psz_input);
 	    // Set a media's input MRL.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_add_input", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_add_input(IntPtr p_instance, string psz_name, string psz_input);
 	    // Add a media's input MRL.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_set_loop", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_set_loop(IntPtr p_instance, string psz_name, int b_loop);
 	    // Set a media's loop status.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_set_mux", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_set_mux(IntPtr p_instance, string psz_name, string psz_mux);
 	    // Set a media's vod muxer.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_change_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_change_media(IntPtr p_instance, string psz_name, string psz_input, string psz_output, int i_options, [MarshalAs(UnmanagedType.LPArray)] String[] ppsz_options, int b_enabled, int b_loop);
 	    // Edit the parameters of a media.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_play_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_play_media(IntPtr p_instance, string psz_name);
 	    // Play the named broadcast.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_stop_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_stop_media(IntPtr p_instance, string psz_name);
 	    // Stop the named broadcast.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_pause_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_pause_media(IntPtr p_instance, string psz_name);
        // Pause the named broadcast.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_seek_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_seek_media(IntPtr p_instance, string psz_name, float f_percentage);
 	    // Seek in the named broadcast.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_show_media", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr libvlc_vlm_show_media(IntPtr p_instance, string psz_name);
 	    // Return information about the named media as a JSON string representation.

        public static String ShowMedia(IntPtr p_instance, string psz_name)
        {
            IntPtr ptr = libvlc_vlm_show_media(p_instance, psz_name);
            return Marshal.PtrToStringAnsi(ptr);
        }

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_get_media_instance_position", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_get_media_instance_position(IntPtr p_instance, string psz_name, int i_instance);
 	    // Get vlm_media instance position by name or instance id.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_get_media_instance_time", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_get_media_instance_time(IntPtr p_instance, string psz_name, int i_instance);
 	    // Get vlm_media instance time by name or instance id.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_get_media_instance_length", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_get_media_instance_length(IntPtr p_instance, string psz_name, int i_instance);
 	    // Get vlm_media instance length by name or instance id.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_get_media_instance_rate", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int libvlc_vlm_get_media_instance_rate(IntPtr p_instance, string psz_name, int i_instance);
 	    // Get vlm_media instance playback rate by name or instance id.

        [DllImport("libvlc.dll", ExactSpelling = true, EntryPoint = "libvlc_vlm_get_event_manager", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr libvlc_vlm_get_event_manager(IntPtr p_instance);
        // Get libvlc_event_manager from a vlm media. 
        #endregion
    }

    class VLCInfo
    {
        public Player player = null;
        public Sender sender = null;

        public VLCInfo()
        {
            player = new Player();
            sender = new Sender();            
        }

        public class MediaInfo
        {
            public string name = "";
            public string type = "";
            public bool enabled = false;
            public string loop = "";
            public string [] inputs = null;
            public string output = "";
            public string [] options = null;
            public Instance instances = null;
            public class Instance
            {
                public string name = "";
                public string state = "";
                public float position = 0.0f;
                public long time = 0L;
                public long length = 0L;
                public float rate = 0.0f;
                public string title = "";
                public string chapter = "";
                public bool canSeek = false;
                public int playListIndex = 0;
            }

            public void FromJObject(JObject json)
            {
                try
                {
                    name = (string)json["name"];
                    type = (string)json["type"];
                    enabled = ((string)json["enabled"]).CompareTo("yes") == 0 ? true : false;
                    loop = (string)json["loop"];
                    JArray array = (JArray)json["inputs"];
                    inputs = new string[array.Count];
                    for (int i = 0; i < inputs.Length; i += 1)
                    {
                        inputs[i] = (string)array[i];
                    }
                    output = (string)json["output"];
                    //array = (JArray)json["options"];
                    //options = new string[array.Count];
                    //for (int i = 0; i < options.Length; i += 1)
                    //{
                    //    options[i] = (string)array[i];
                    //}
                    if (instances == null)
                    {
                        instances = new Instance();
                    }
                    json = (JObject)json["instances"];
                    if (json != null)
                    {
                        json = (JObject)json["instance"];
                        instances.name = (string)json["name"];
                        instances.state = (string)json["state"];
                        instances.position = float.Parse((string)json["position"]) * 100.0f;
                        instances.time = long.Parse((string)json["time"]);
                        instances.length = long.Parse((string)json["length"]);
                        instances.rate = float.Parse((string)json["rate"]);
                        instances.title = (string)json["title"];
                        instances.chapter = (string)json["chapter"];
                        instances.canSeek = ((string)json["can-seek"]).CompareTo("1") == 0 ? true : false;
                        instances.playListIndex = int.Parse((string)json["playlistindex"]);
                    }
                }
                catch (Exception)
                {
                    //Console.WriteLine(e.ToString());
                }
            }
        }

        public class Sender
        {
            private IntPtr dataOut = IntPtr.Zero;
            private bool playing = false;
            private MediaInfo info = null;

            byte[] mem = new byte[64];
            GCHandle pData;
            private static string NAME = "";

            public Sender()
            {
                string nm = "tc_smart";
                ASCIIEncoding enc = new ASCIIEncoding();
                byte[] tmem = enc.GetBytes(nm);
                Array.Copy(tmem, mem, tmem.Length);

                pData = GCHandle.Alloc(mem, GCHandleType.Pinned);
                IntPtr ptr = pData.AddrOfPinnedObject();
                NAME = Marshal.PtrToStringAnsi(ptr);

                string[] options = { "" };
                dataOut = VLCLoader.libvlc_new(0, options);
                if (dataOut == IntPtr.Zero)
                {
                    MessageBox.Show("Error! Cannot create an instance of VLC!");
                    Application.Exit();
                }

                info = new MediaInfo();
            }

            public void SetOptions(string fileName, string transcode)
            {
                if (playing)
                {
                    Stop();
                    VLCLoader.libvlc_vlm_del_media(dataOut, NAME);
                }
                string[] options = { "" };
                VLCLoader.libvlc_vlm_add_broadcast(dataOut, NAME, fileName, transcode, 0, options, 1, 0);
            }

            public void Play()
            {
                if (playing)
                {
                    Stop();
                }
                VLCLoader.libvlc_vlm_play_media(dataOut, NAME);                
                playing = true;
            }

            public void Pause()
            {
                VLCLoader.libvlc_vlm_pause_media(dataOut, NAME);
                playing = false;
            }

            public void Stop()
            {
                if (playing)
                {
                    VLCLoader.libvlc_vlm_stop_media(dataOut, NAME);
                    playing = false;

                    Destroy();
                    string[] options = { "" };
                    dataOut = VLCLoader.libvlc_new(0, options);
                    if (dataOut == IntPtr.Zero)
                    {
                        MessageBox.Show("Error! Cannot create an instance of VLC!");
                        Application.Exit();
                    }
                }
            }

            public string ShowMedia()
            {
                return VLCLoader.ShowMedia(dataOut, NAME);
            }

            public MediaInfo ShowMediaObject()
            {
                string txt = ShowMedia();
                txt = txt.Replace("\\", "\\\\");
                Console.WriteLine(txt);
                if (playing && txt.Contains("instances\": null"))
                {
                    Stop();
                }
                try
                {
                    JObject json = JObject.Parse(txt);
                    info.FromJObject(json);
                }
                catch (Exception e)
                {
                    Console.WriteLine(txt);
                    Console.WriteLine(e.ToString());
                }
                return info;
            }

            public bool IsPlaying()
            {
                return playing;
            }

            public int GetLenth()
            {
                return VLCLoader.libvlc_vlm_get_media_instance_length(dataOut, NAME, 0);
            }

            public int GetRate()
            {
                return VLCLoader.libvlc_vlm_get_media_instance_rate(dataOut, NAME, 0);
            }

            public int GetTime()
            {
                return VLCLoader.libvlc_vlm_get_media_instance_time(dataOut, NAME, 0);
            }

            public int GetPosition()
            {
                return VLCLoader.libvlc_vlm_get_media_instance_position(dataOut, NAME, 0);
            }

            public void Seek(float percent)
            {
                VLCLoader.libvlc_vlm_seek_media(dataOut, NAME, percent);
            }

            public void Destroy()
            {
                if (dataOut != IntPtr.Zero)
                {
                    VLCLoader.libvlc_release(dataOut);
                }
            }
        }

        public class Player
        {
            private IntPtr dataIn = IntPtr.Zero;
            private IntPtr player = IntPtr.Zero;
            private IntPtr media = IntPtr.Zero;

            public Player()
            {
                string[] options = { "" };
                dataIn = VLCLoader.libvlc_new(1, options);
                if (dataIn == IntPtr.Zero)
                {
                    MessageBox.Show("Error! Cannot create an instance of VLC!");
                    Application.Exit();
                }
            }

            private void SetHWND(IntPtr hwnd)
            {
                VLCLoader.libvlc_media_player_set_hwnd(player, hwnd);
            }

            private void Play()
            {
                VLCLoader.libvlc_media_player_play(player);
            }

            public void Start(IntPtr hwnd)
            {
                media = VLCLoader.MediaNewPath(dataIn, "rtp://224.1.1.1:5004");
                if (player != IntPtr.Zero)
                {
                    VLCLoader.libvlc_media_player_release(player);
                }
                player = VLCLoader.libvlc_media_player_new_from_media(media);
                SetHWND(hwnd);
                Play();
                VLCLoader.libvlc_media_release(media);
                media = IntPtr.Zero;
            }

            public void Stop()
            {
                VLCLoader.libvlc_media_player_stop(player);
            }

            public void Destroy()
            {
                if (player != IntPtr.Zero)
                {
                    VLCLoader.libvlc_media_player_release(player);
                }

                if (dataIn != IntPtr.Zero)
                {
                    VLCLoader.libvlc_release(dataIn);
                }
            }
        }
    }
}
