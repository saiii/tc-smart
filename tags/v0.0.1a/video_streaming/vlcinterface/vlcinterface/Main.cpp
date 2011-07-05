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
#include <vector>
#include <windows.h>
#include "Main.h"

#ifdef _DLL
  #ifndef DllPrefix
  #define DllPrefix extern "C" __declspec(dllexport)
  #endif
#else
  #ifndef DllPrefix
  #define DllPrefix extern "C" __declspec(dllimport)
  #endif
#endif

typedef std::vector<VlcBroadcaster*>           VlcBcastList;
typedef std::vector<VlcBroadcaster*>::iterator VlcBcastListIterator;

typedef std::vector<VlcPlayer*>           VlcPlayerList;
typedef std::vector<VlcPlayer*>::iterator VlcPlayerListIterator;


VlcPlayerList PlayerList;
VlcBcastList BcastList;

DllPrefix 
void __stdcall 
VLCInterface_Init()
{
}

DllPrefix 
void __stdcall 
VLCInterface_Destroy()
{
  while (PlayerList.size() > 0)
  {
    VlcPlayer * player = PlayerList.front();
	PlayerList.erase(PlayerList.begin());
	delete player;
  }

  while (BcastList.size() > 0)
  {
    VlcBroadcaster * bcast = BcastList.front();
	BcastList.erase(BcastList.begin());
	delete bcast;
  }
}

DllPrefix 
unsigned int __stdcall 
VLCInterface_Bcast_Init()
{
  unsigned int ret = BcastList.size();
  VlcBroadcaster * bcast = new VlcBroadcaster();
  BcastList.push_back(bcast);
  
  char *vlcOptions[] = {""};
  bcast->instance = libvlc_new(1, vlcOptions);
  
  return ret;
}

DllPrefix 
void __stdcall 
VLCInterface_Bcast_Play(unsigned int index, const char * name, const char * transcode)
{
  if (BcastList.size() == 0)
  {
    return;
  }

  VlcBroadcaster * bcast = BcastList.at(index);
  char *vlcOptions[] = {""};
  libvlc_vlm_add_broadcast(bcast->instance, "tc_smart", name, transcode, 0, vlcOptions, 1, 0);
  libvlc_vlm_play_media(bcast->instance, "tc_smart");
}

DllPrefix 
void __stdcall 
VLCInterface_Bcast_Pause(unsigned int index)
{
  if (BcastList.size() == 0)
  {
    return;
  }

  VlcBroadcaster * bcast = BcastList.at(index);
  libvlc_vlm_pause_media(bcast->instance, "tc_smart");
}

DllPrefix 
void __stdcall 
VLCInterface_Bcast_Resume(unsigned int index)
{
  if (BcastList.size() == 0)
  {
    return;
  }

  VlcBroadcaster * bcast = BcastList.at(index);
  libvlc_vlm_play_media(bcast->instance, "tc_smart");
}

DllPrefix 
void __stdcall 
VLCInterface_Bcast_Stop(unsigned int index)
{
  if (BcastList.size() == 0)
  {
    return;
  }

  VlcBroadcaster * bcast = BcastList.at(index);
  libvlc_vlm_del_media(bcast->instance, "tc_smart");
  bcast->instance = 0;
}

DllPrefix 
unsigned int __stdcall 
VLCInterface_Player_Init(void * hwnd)
{
  unsigned int ret = PlayerList.size();
  VlcPlayer * player = new VlcPlayer();
  PlayerList.push_back(player);
  
  char *vlcOptions[] = {""};
  player->instance = libvlc_new(1, vlcOptions);

  libvlc_media_t* media = 0;
  media = libvlc_media_new_path(player->instance, "rtp://224.1.1.1:5004");
  player->player = libvlc_media_player_new_from_media(media);
  libvlc_media_player_set_hwnd(player->player, (HWND*)hwnd);
  libvlc_media_player_play(player->player);
  libvlc_media_release(media);

  return ret;
}

DllPrefix 
void __stdcall 
VLCInterface_Player_Stop(unsigned int index)
{
  if (PlayerList.size() == 0)
  {
    return;
  }

  VlcPlayer * player = PlayerList.at(index);

  libvlc_media_player_stop(player->player);
  libvlc_media_player_release(player->player);
  player->player = 0;
}

DllPrefix 
unsigned int __stdcall 
VLCInterface_Player_GetPosition(unsigned int index)
{
  if (BcastList.size() == 0)
  {
    return 0;
  }

  VlcBroadcaster * bcast = BcastList.at(index);
  return libvlc_vlm_get_media_instance_time(bcast->instance, "tc_smart", 0/* FIXME : What is this? */);
}

DllPrefix 
unsigned int __stdcall 
VLCInterface_Bcast_GetLength(unsigned int index)
{
  if (BcastList.size() == 0)
  {
    return 0;
  }

  VlcBroadcaster * bcast = BcastList.at(index);
  return libvlc_vlm_get_media_instance_length(bcast->instance, "tc_smart", 0 /*FIXME : What is this?*/);
}

DllPrefix 
void __stdcall 
VLCInterface_Bcast_SetPosition(unsigned int index, unsigned int pos)
{
  if (BcastList.size() == 0)
  {
    return;
  }

  VlcBroadcaster * bcast = BcastList.at(index);
  libvlc_vlm_seek_media(bcast->instance, "tc_smart", (float)pos);
}