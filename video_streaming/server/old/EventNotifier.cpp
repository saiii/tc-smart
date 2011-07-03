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

#include <Message.h>
#include "EventNotifier.h"

using namespace sai::net;

class ClientMsgHandler : public DataHandler
{
public:
  void processDataEvent(DataDescriptor& desc, std::string& msg)
  {
  }
};

class DefaultMsgHandler : public DataHandler
{
public:
  void processDataEvent(DataDescriptor& desc, std::string& msg)
  {
  }
};

EventNotifier::EventNotifier():
  _clientMsg(0),
  _defaultMsg(0),
  _channel(0)
{
  _clientMsg = new ClientMsgHandler();
  _defaultMsg = new DefaultMsgHandler();

  Net * net = Net::GetInstance();
  net->initialize();

  // Communication initialization
  _channel = new McastDataBusChannel();
  _channel->setPort(2010);
  _channel->setLocalAddress("0.0.0.0");
  _channel->setSendMcast("225.2.2.2");
  _channel->addRecvMcast("225.1.1.1");

  DataBus *bus = DataBus::GetInstance();
  bus->setChannel(_channel);

  bus->setDefaultHandler(_defaultMsg);
  bus->registerHandler(TCSM_VS_CLIENT_MSG, _clientMsg);

  bus->listen(TCSM_VS_CLIENT_MESSAGE);
  bus->activate();
}

EventNotifier::~EventNotifier()
{
  delete _defaultMsg;
  delete _clientMsg;
  delete _channel;
}

void 
EventNotifier::start(std::string transcode)
{
  DataBus::GetInstance()->send(TCSM_VS_SERVER_MESSAGE, TCSM_VS_START, transcode);
}

void 
EventNotifier::shutdown()
{
  DataBus::GetInstance()->send(TCSM_VS_SERVER_MESSAGE, TCSM_VS_SHUTDOWN, "");
}

