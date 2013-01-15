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

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>

#include "Command.h"

void
GetTime(std::string &rtn)
{
  struct timeval  tv;
  char buf[256];
  gettimeofday(&tv, NULL);
  struct tm *ptm;
  ptm = localtime(&tv.tv_sec);
  strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", ptm);
  rtn = buf;
}

Command::Command():
  _net(0),
  _vlc(0),
  _svrCnt(0),
  _fp(0)
{
  _fp = fopen("/var/tmp/video.client.log", "a+");
  
  std::string tm;
  GetTime(tm);
  fprintf(_fp, "[%s] Start\n", tm.c_str());
  fflush(_fp);
}

Command::~Command()
{
  fflush(_fp);
  fclose(_fp);
  delete _vlc;
}

void 
Command::initialize()
{
  std::string tm;
  GetTime(tm);
  fprintf(_fp, "[%s] Initilize\n", tm.c_str());
  fflush(_fp);
  _vlc = new Vlc();
  Net net;
  _net = &net;
  net.setListener(this);
  net.initialize();
  net.mainLoop();
  exit(0);
}

void 
Command::start(char * msg)
{
  if (_vlc->player)
  {
    return;
  }

  std::string tm;
  GetTime(tm);
  fprintf(_fp, "[%s] Command::start\n", tm.c_str());
  fflush(_fp);

  libvlc_media_t* media = 0;
  media        = libvlc_media_new_path(_vlc->instance, "rtp://224.1.1.1:5004");
  _vlc->player = libvlc_media_player_new_from_media(media);
  libvlc_set_fullscreen(_vlc->player, 1);
  libvlc_media_release(media);
  libvlc_media_player_play(_vlc->player);
}

void 
Command::shutdown()
{
  if (_vlc->player)
  {
    std::string tm;
    GetTime(tm);
    fprintf(_fp, "[%s] Command::shutdown\n", tm.c_str());
    fflush(_fp);
    libvlc_media_player_stop(_vlc->player);
    libvlc_media_player_release(_vlc->player);
    _vlc->player = 0;
  }
}

void
Command::timerEvent()
{
  if (++_svrCnt > 40)
  {
    std::string tm;
    GetTime(tm);
    fprintf(_fp, "[%s] Command::timerEvent (#1)\n", tm.c_str());
    fflush(_fp);
    shutdown();
    _svrCnt = 0;
  }

  std::stringstream txt;
  txt << "<?xml version=\"1.0\"?>\n";
  txt << "<tcsm>";
  txt <<   "<hb value=\"alive\"/>";
  txt << "</tcsm>";
  
  std::string tm;
  GetTime(tm);
  fprintf(_fp, "[%s] Command::timerEvent (#2: send beat)\n", tm.c_str());
  fflush(_fp);
  _net->send((char*)txt.str().c_str(), txt.str().length());
}

void
Command::startEvent(char * msg)
{
  std::string tm;
  GetTime(tm);
  fprintf(_fp, "[%s] Command::startEvent\n", tm.c_str());
  fflush(_fp);
  start(msg);
}

void
Command::updateEvent(char * msg)
{
  if (!_vlc->player)
  {
    //printf("No Player\n");
    start(msg);
  }
  _svrCnt = 0;
  std::string tm;
  GetTime(tm);
  fprintf(_fp, "[%s] Command::updateEvent\n", tm.c_str());
  fflush(_fp);
  //printf("UPDATE\n");
}

void
Command::shutdownEvent()
{
  std::string tm;
  GetTime(tm);
  fprintf(_fp, "[%s] Command::shutdownEvent\n", tm.c_str());
  fflush(_fp);
  shutdown();
}

Command::Vlc::Vlc():
  instance(0),
  player(0)
{
  instance = libvlc_new(0, 0);
}

Command::Vlc::~Vlc()
{
  if (player)
  {
    libvlc_media_player_stop(player);
    libvlc_media_player_release(player);
    player = 0;
  }

  if (instance)
  {
    libvlc_release(instance);
    instance = 0;
  }
}

