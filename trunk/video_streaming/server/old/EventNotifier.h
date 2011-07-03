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

#ifndef __TCSMART_SERVER_EVENTNOTIFIER__
#define __TCSMART_SERVER_EVENTNOTIFIER__

#include <string>
#include <net/DataBus.h>

class ClientMsgHandler;
class DefaultMsgHandler;
class EventNotifier
{
private:
  ClientMsgHandler                *_clientMsg;
  DefaultMsgHandler               *_defaultMsg;
  sai::net::McastDataBusChannel   *_channel;

public:
  EventNotifier();
  ~EventNotifier();

  void start(std::string);
  void shutdown();
};

#endif
