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
#include <wx/timer.h>
#include <vlc/vlc.h>

typedef enum
{
  NONE,
  START,
  PLAYING,
  PLAY,
  PAUSE,
  SEEK,
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


class StreamingManager : public wxTimer
{
private:
  static StreamingManager * _instance;
  StreamState               _state;
  std::string               _transcode;
  std::string               _fileName;
  std::string               _addr;
  VlcPlayer*                _player;
  VlcBroadcaster*           _bcast;
  bool                      _localStarted;
  int                       _seekPos;

private:
  StreamingManager();

public:
  static StreamingManager * GetInstance();
  ~StreamingManager();

  void start(std::string);
  void Notify() { timerEvent(); }
  void timerEvent();

  void play();
  void pause();
  void stop();
  void seek(int);
};

#endif
