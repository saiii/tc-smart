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

#include "StreamingManager.h"

StreamingManager::StreamingManager():
  _event(0),
  _state(NONE)
{
  _event = new EventNotifier();
  schedule(1, 0);
}

StreamingManager::~StreamingManager()
{
  delete _event;
}

void 
StreamingManager::start(std::string fileName)
{
  if (_state != NONE)
  {
    return;
  }

  // Detect video + audio encoding information
  // Find the best transcode

  _event->start(_transcode);

  _state = START;
}

void 
StreamingManager::timerEvent()
{
  switch (_state)
  {
    case NONE:
      break;
    case START:
      if (_player.player)
      {
        libvlc_media_player_stop(_player.player);
        libvlc_media_player_release(_player.player);
        _player.player = 0;
      }

      {
        libvlc_media_t* media = 0;
        media       = libvlc_media_new_path(_player.instance, _transcode.c_str());
        _player.player = libvlc_media_player_new_from_media(media);

        //libvlc_set_fullscreen(_player.player, 1);
        libvlc_media_release(media);

        libvlc_media_player_play(_player.player);
      }

      _state = PLAYING;
      break;
    case PLAYING:
      // TODO : End of stream detection? yes -> state := shutdown
      break;
    case PAUSE:
      // TODO : Send pause event
      break;
    case SHUTDOWN:
      if (_player.player)
      {
        libvlc_media_player_stop(_player.player);
        libvlc_media_player_release(_player.player);
        _player.player = 0;
      }

      _event->shutdown();
      _state = NONE;
      break;
  }
  schedule();
}

VlcPlayer::VlcPlayer():
  instance(0),
  player(0)
{
  instance = libvlc_new(0, 0);
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
