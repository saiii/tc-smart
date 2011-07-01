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

#include <stdio.h>
#include <stdlib.h>

#include <net/Net.h>
#include <net/DataBus.h>

#include <Message.h>
#include "Command.h"

class Default : public sai::net::DataHandler
{
public:
  void processDataEvent(sai::net::DataDescriptor& desc, std::string& msg)
  {
  }
};

class CommandClient
{
protected:
  Command * _command;

public:
  CommandClient(Command * cmd) : _command(cmd) {}
  virtual ~CommandClient() {}
};

class Start : public sai::net::DataHandler,
              public CommandClient
{
public:
  Start(Command * cmd) : CommandClient(cmd) {}
  ~Start() {}

  void processDataEvent(sai::net::DataDescriptor& desc, std::string& msg)
  {
    // TODO : process message
    _command->start(msg);
  }
};

class Shutdown : public sai::net::DataHandler,
                 public CommandClient
{
public:
  Shutdown(Command * cmd) : CommandClient(cmd) {}
  ~Shutdown() {}

  void processDataEvent(sai::net::DataDescriptor& desc, std::string& msg)
  {
    _command->shutdown();
  }
};

//=============================================================================

using namespace sai::net;

Command::Command():
  _vlc(0)
{
}

Command::~Command()
{
  delete _vlc;
}

void 
Command::initialize()
{
  // General start-up
  /*
  Config* config = Config::GetInstance();
  config->initialize("VideoStreamingClient");

  Logger* logger = Logger::GetInstance();
  logger->print(LVL_DEBUG, "Start...");
  */

  time_t t = time(0);
  t += (60 * 15);
  Net * net = Net::GetInstance();
  for (;;)
  {
    net->initialize();
    std::string addr = net->getLocalAddress();
    if (addr.length() == 0 || addr.compare("127.0.0.1") == 0)
    {
      time_t now = time(0);
      if (now < t)
      {
        sleep(1);
      }
      else
      {
        break;
      }
    }
    else
    {
      break;
    }
  }

  // Communication initialization
  McastDataBusChannel channel;
  channel.setPort(2010);
  channel.setLocalAddress("0.0.0.0");
  channel.setSendMcast("225.1.1.1");
  channel.addRecvMcast("225.2.2.2");

  DataBus *bus = DataBus::GetInstance();
  bus->setChannel(&channel);

  Default def;
  bus->setDefaultHandler(&def);

  Start start(this);
  Shutdown shutdown(this);
  
  bus->registerHandler(TCSM_VS_START,    &start);
  bus->registerHandler(TCSM_VS_SHUTDOWN, &shutdown);

  bus->listen(TCSM_VS_SERVER_MESSAGE);

  // Wait transcode and play command from server
  // play
  // there might be pause or stop ??
  // get shutdown command from server and turn off the window

  bus->activate();

  _vlc = new Vlc();
  libvlc_media_t* media = 0;
  media        = libvlc_media_new_path(_vlc->instance, "rtp://@224.1.1.1:5004");
  _vlc->player = libvlc_media_player_new_from_media(media);
  libvlc_set_fullscreen(_vlc->player, 1);
  libvlc_media_release(media);
  libvlc_media_player_play(_vlc->player);

  Net::GetInstance()->mainLoop();
  exit(0);
}

void 
Command::start(std::string msg)
{
#if 0
  if (_vlc->player)
  {
    shutdown();
  }
#endif

  printf("Get start command at addr = %s\n", msg.c_str());
}

void 
Command::shutdown()
{
  if (_vlc->player)
  {
    libvlc_media_player_stop(_vlc->player);
    libvlc_media_player_release(_vlc->player);
    _vlc->player = 0;
  }
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

