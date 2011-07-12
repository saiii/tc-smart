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

#ifdef _WIN32
#include <Windows.h>
#endif
#include "Main.h"
#include "StreamingManager.h"

StreamingManager * StreamingManager::_instance = 0;

StreamingManager::StreamingManager():
  wxTimer(),
  _state(NONE),
  _player(0),
  _bcast(0),
  _localStarted(false),
  _seekPos(0)
{
  Start(1000, false);
}

StreamingManager * 
StreamingManager::GetInstance()
{
  if (_instance == 0)
  {
    _instance = new StreamingManager();
  }
  return _instance;
}

StreamingManager::~StreamingManager()
{
  delete _player;
  delete _bcast;
}

void 
StreamingManager::start(std::string name)
{
  if (!(_state == NONE || _state == PLAYING))
  {
    return;
  }

  _fileName = name;

  //_transcode = "#rtp{dst=224.1.1.1,port=5004,mux=ts}";
  //_transcode = "#rtp{dst=224.1.1.1,port=5004,mux=ts,name=\"tc_smart\"}";
  //_transcode = "#transcode{acodec=mp4a,ab=128,channels=2,samplera te=44100}:rtp{dst=224.1.1.1,port=5004,mux=ts}";
  //_transcode = "#transcode{vcodec=h264,vb=0,scale=0,acodec=mp4a,ab=128,channels=2,samplerate=44100}:rtp{dst=224.1.1.1,port=5004,mux=ts}";
  _transcode = "#transcode{vcodec=h264,vb=0,scale=0,acodec=mp3,ab=128,channels=2,samplerate=44100}:rtp{dst=224.1.1.1,port=5004,mux=ts}";
  //_transcode = "#transcode{vcodec=mp4v,acodec=mpga,vb=1200,ab=128,deinterlace}:rtp{mux=ts,dst=224.1.1.1,port=5004,sdp=sap://,name=\"tc_smart\"}";

  // flash -> mpeg, vb=1200, mp3
  //_transcode = "#transcode{vcodec=flv1,vb=1600,acodec=mp3,ab=128,channels=2,samplerate=44100}:rtp{dst=224.1.1.1,port=5004,mux=ts}";
  _addr = "rtp://@224.1.1.1:5004";

  _state = START;
}

void 
StreamingManager::timerEvent()
{
  switch (_state)
  {
    case NONE:
      if (!_player) _player = new VlcPlayer();
	  if (!_bcast)  _bcast  = new VlcBroadcaster();
      break;
    case START:
#if 0
      if (_player->player)
      {
        libvlc_media_player_stop(_player->player);
        libvlc_media_player_release(_player->player);
        _player->player = 0;
      }
#endif

	  if (!_localStarted)
      {
        _localStarted = true;
        libvlc_media_t* media = 0;
        media           = libvlc_media_new_path(_player->instance, _addr.c_str());
        _player->player = libvlc_media_player_new_from_media(media);

#if _WIN32
        HWND* handle = (HWND*)MainWindow::GetInstance()->getMainPanelHandle();
		libvlc_media_player_set_hwnd(_player->player, handle);
#else
        //GtkWidget* handle = (GtkWidget*)MainWindow::GetInstance()->getMainPanelHandle();
        //GdkWindow* gdkwindow = gtk_widget_get_window(handle);
        //XID xid = GDK_WINDOW_XID(gdkwindow);
        //libvlc_media_player_set_xwindow(_player.player, xid);
#endif
		libvlc_media_player_play(_player->player);
        libvlc_media_release(media);
      }

      {
        char *vlcOptions[] = {""};
		libvlc_vlm_add_broadcast(_bcast->instance, "tc_smart", _fileName.c_str(), _transcode.c_str(), 0, vlcOptions, 1, 0);
        libvlc_vlm_play_media(_bcast->instance, "tc_smart");
      }
      _state = PLAYING;
      break;
    case PLAYING:
      // TODO : End of stream detection? yes -> state := shutdown
      {
        //float position = libvlc_vlm_get_media_instance_position(_bcast->instance, "tc_smart", 0);
		//int position = libvlc_vlm_get_media_instance_time(_bcast->instance, "tc_smart", 0); 
		//int total = libvlc_vlm_get_media_instance_length(_bcast->instance, "tc_smart", 0);
		//MainWindow::GetInstance()->setStreamPosition(position, total);
        // libvlc_vlm_seek_media(_bcast.instance, "tc-smart", position);
      }
      break;
	case PLAY:
	  libvlc_vlm_play_media(_bcast->instance, "tc_smart");
	  _state = PLAYING;
	  break;
    case PAUSE:
      // TODO : Send pause event
      libvlc_vlm_pause_media(_bcast->instance, "tc_smart");
      break;
	case SEEK:
	  break;
    case SHUTDOWN:
      if (_player->player)
      {
        libvlc_media_player_stop(_player->player);
        libvlc_media_player_release(_player->player);
        _player->player = 0;
      }
      delete _player;
	  _localStarted = false;

      libvlc_vlm_del_media(_bcast->instance, "tc_smart");
      delete _bcast;

      //_event->shutdown();
      _state = NONE;
      break;
  }
}

void 
StreamingManager::play()
{
  switch (_state)
  {
  case PAUSE:
	  _state = PLAY;
  default:
	  break;
  }
}

void 
StreamingManager::pause()
{
  switch (_state)
  {
  case PLAYING:
	  _state = PAUSE;
  default:
	  break;
  }
}

void 
StreamingManager::stop()
{
  switch (_state)
  {
  case PLAYING:
	  _state = SHUTDOWN;
  default:
	  break;
  }
}

void 
StreamingManager::seek(int pos)
{
  switch (_state)
  {
  case PLAYING:
	  _state = SEEK;
	  _seekPos = pos;
  default:
	  break;
  }
}

VlcPlayer::VlcPlayer():
  instance(0),
  player(0)
{
  char *vlcOptions[] = {""};
  instance = libvlc_new(1, vlcOptions);
}

VlcPlayer::~VlcPlayer()
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

VlcBroadcaster::VlcBroadcaster():
  instance(0)
{
  char *vlcOptions[] = {""};
  instance = libvlc_new(1, vlcOptions);
}

VlcBroadcaster::~VlcBroadcaster()
{
  if (instance)
  {
    libvlc_release(instance);
    instance = 0; 
  }
}
