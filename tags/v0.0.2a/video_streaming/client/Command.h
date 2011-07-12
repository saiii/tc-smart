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

#ifndef __TCSMART_VSCLIENT_COMMAND__
#define __TCSMART_VSCLIENT_COMMAND__

#include <vlc/vlc.h>
#include <string>

#include <net/DataHandler.h>
#include <net/DataDescriptor.h>
#include <net/TimerTask.h>

class Command : public sai::net::DataHandler,
                public sai::net::TimerTask
{
private:
  class Vlc
  {
    public:
      libvlc_instance_t *     instance;
      libvlc_media_player_t * player;

    public:
      Vlc();
      ~Vlc();
  };

private:
  Vlc*     _vlc;
  uint32_t _svrCnt;

public:
  Command();
  ~Command();

  void initialize();

  void timerEvent();

  // Events from server
  void processDataEvent(sai::net::DataDescriptor& desc, std::string& msg);
  void start();
  void shutdown();
};

#endif
