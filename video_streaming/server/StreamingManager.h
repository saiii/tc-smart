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

#ifndef __TCSMART_SERVER_STREAMINGMANAGER__
#define __TCSMART_SERVER_STREAMINGMANAGER__

#include <string>
#include <net/TimerTask.h>
#include <EventNotifier.h>
#include <vlc/vlc.h>

typedef enum
{
  NONE,
  START,
  PLAYING,
  PAUSE,
  SHUTDOWN
}StreamState;

class VlcPlayer
{
  public:
    libvlc_instance_t *     instance;
    libvlc_media_player_t * player;

  public:
    VlcPlayer();
    ~VlcPlayer();
};

class VlcBroadcaster
{
  public:
    libvlc_instance_t *     instance;
  
  public:
    VlcBroadcaster();
    ~VlcBroadcaster();
};


class StreamingManager : public sai::net::TimerTask
{
private:
  static StreamingManager * _instance;
  EventNotifier *           _event;
  StreamState               _state;
  std::string               _transcode;
  std::string               _fileName;
  std::string               _addr;
  VlcPlayer*                _player;
  VlcBroadcaster*           _bcast;

private:
  StreamingManager();

public:
  static StreamingManager * GetInstance();
  ~StreamingManager();

  void start(std::string);
  void timerEvent();
};

#endif
