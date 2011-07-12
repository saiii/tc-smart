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

#include "ClientMsgHandler.h"

ClientMsgHandler* ClientMsgHandler::_instance = 0;

ClientMsgHandler::ClientMsgHandler():
  _cb(0)
{
}

ClientMsgHandler* 
ClientMsgHandler::GetInstance()
{
  if (_instance == 0)
  {
    _instance = new ClientMsgHandler();
  }
  return _instance;
}

ClientMsgHandler::~ClientMsgHandler()
{
}

void 
ClientMsgHandler::setCallback(MsgCallback cb)
{
  _cb = cb;
}

void 
ClientMsgHandler::processDataEvent(sai::net::DataDescriptor& desc, std::string& msg)
{
  if (_cb)
  {
    std::string addr;
    desc.from.toString(addr, sai::net::Address::RAW_MSG);

    _cb(addr.c_str(), msg.c_str());
  }
}

