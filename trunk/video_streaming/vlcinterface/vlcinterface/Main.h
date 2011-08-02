//=============================================================================
// Copyright (C) 2011 Athip Rooprayochsilp <athipr@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//              
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//=============================================================================

#ifndef __TCSMART_MAIN__
#define __TCSMART_MAIN__

#include <vlc/vlc.h>

#ifdef _DLL
  #ifndef DllPrefix
  #define DllPrefix extern "C" __declspec(dllexport)
  #endif
#else
  #ifndef DllPrefix
  #define DllPrefix extern "C" __declspec(dllimport)
  #endif
#endif

typedef struct
{
  libvlc_instance_t     *instance;
  libvlc_media_player_t *player;
}VlcPlayer;

typedef struct 
{
  libvlc_instance_t     *instance;
}VlcBroadcaster;


DllPrefix void __stdcall VLCInterface_Init();
DllPrefix void __stdcall VLCInterface_Destroy();
DllPrefix unsigned int __stdcall VLCInterface_Bcast_Init();
DllPrefix int          __stdcall VLCInterface_Bcast_Play(unsigned int index, const char * name, const char * transcode);
DllPrefix void         __stdcall VLCInterface_Bcast_Pause(unsigned int index);
DllPrefix void         __stdcall VLCInterface_Bcast_Resume(unsigned int index);
DllPrefix void         __stdcall VLCInterface_Bcast_Stop(unsigned int index);

DllPrefix unsigned int __stdcall VLCInterface_Player_Init(void *, const char *);
DllPrefix void         __stdcall VLCInterface_Player_Stop(unsigned int);


DllPrefix long long    __stdcall VLCInterface_Bcast_GetPosition(unsigned int);
DllPrefix long long    __stdcall VLCInterface_Bcast_GetLength(unsigned int);
DllPrefix int          __stdcall VLCInterface_Bcast_SetPosition(unsigned int, unsigned int);

#endif