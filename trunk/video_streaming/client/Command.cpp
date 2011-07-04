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
#include <sstream>

#include <net/Net.h>
#include <net/DataBus.h>
#include <utils/XmlReader.h>

#include <Message.h>
#include "Command.h"

class Default : public sai::net::DataHandler
{
public:
  void processDataEvent(sai::net::DataDescriptor& desc, std::string& msg)
  {
  }
};

//=============================================================================

using namespace sai::net;

Command::Command():
  _vlc(0),
  _svrCnt(0)
{
  schedule(1, 0);
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
  channel.setPort(8010);
  channel.setLocalAddress("0.0.0.0");
  channel.setSendMcast("225.2.2.2");
  channel.addRecvMcast("225.1.1.1");

  DataBus *bus = DataBus::GetInstance();
  bus->setChannel(&channel);

  Default def;
  bus->setDefaultHandler(&def);

  bus->registerHandler(TCSM_SVR_GENERIC,  this);
  bus->listen(TCSM_VS_SERVER_MESSAGE);
  bus->activate();

  Net::GetInstance()->mainLoop();
  exit(0);
}

void 
Command::start()
{
  if (_vlc->player)
  {
    shutdown();
  }

  _vlc = new Vlc();
  libvlc_media_t* media = 0;
  media        = libvlc_media_new_path(_vlc->instance, "rtp://@224.1.1.1:5004");
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
    libvlc_media_player_stop(_vlc->player);
    libvlc_media_player_release(_vlc->player);
    _vlc->player = 0;
  }
}

void 
Command::processDataEvent(sai::net::DataDescriptor& desc, std::string& msg)
{
  sai::utils::XmlReader reader;
  reader.parseMem(msg);
  reader.moveTo("vs_msg");
  std::string time = reader.get("time", "value");
  if (time.length() > 0)
  {
    _svrCnt = 0;
  }
  else
  {
    std::string mode = reader.get("mode", "value");
    if (mode.length() > 0)
    {
      if (mode.compare("start") == 0)
      {
        start();
      }
      else if (mode.compare("shutdown") == 0)
      {
        shutdown();
      }
    }
  }
}

void
Command::timerEvent()
{
  if (++_svrCnt > 10)
  {
    _svrCnt = 0;
    shutdown();
  }

  std::stringstream txt;
  txt << "<?xml version=\"1.0\"?>\n";
  txt << "<tcsm>";
  txt <<   "<hb>";
  txt <<     "<addr value=\"" << Net::GetInstance()->getLocalAddress() << "\" />";
  txt <<   "</hb>";
  txt << "</tcsm>";
  
  DataBus::GetInstance()->send(TCSM_VS_CLIENT_MESSAGE, TCSM_CLI_GENERIC, txt.str());

  //printf("%s\n", Net::GetInstance()->getLocalAddress().c_str());
  //printf("%s\n", txt.str().c_str());
  schedule();
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

