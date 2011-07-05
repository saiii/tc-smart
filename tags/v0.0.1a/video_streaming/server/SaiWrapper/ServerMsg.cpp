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

#include <sstream>
#include <net/DataBus.h>

#include "Message.h"
#include "ServerMsg.h"

ServerMsg* ServerMsg::_instance = 0;

ServerMsg::ServerMsg()
{
}

ServerMsg* 
ServerMsg::GetInstance()
{
  if (_instance == 0)
  {
    _instance = new ServerMsg();
  }
  return _instance;
}

ServerMsg::~ServerMsg()
{
}

void 
ServerMsg::send(const char * msg)
{
  std::string txt = msg;
  sai::net::DataBus::GetInstance()->send(TCSM_VS_SERVER_MESSAGE, TCSM_SVR_GENERIC, txt);
}


