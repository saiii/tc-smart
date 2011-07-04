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

#include <net/Net.h>
#include <net/DataBus.h>
#include <net/DataHandler.h>

#include <Message.h>
#include "ServerMsg.h"
#include <ClientMsgHandler.h>

#ifdef _DLL
  #ifndef DllPrefix
  #define DllPrefix extern "C" __declspec(dllexport)
  #endif
#else
  #ifndef DllPrefix
  #define DllPrefix extern "C" __declspec(dllimport)
  #endif
#endif

typedef void (__stdcall * MsgCallback)(const char* ip, const char * msg);

using namespace sai::net;

DllPrefix const char * __stdcall 
Sai_Get_Version()
{
  static std::string ret = "0.0.2b"; // just for now
  return ret.c_str();
}

DllPrefix 
const char * __stdcall Sai_Net_GetNicList()
{
  static std::string ret = "";
  Net * net = Net::GetInstance();
  ret = net->getNicList(ret); 
  return ret.c_str();
}

class DummyPrinter : public DataHandler
{
public:
  void processDataEvent(DataDescriptor& desc, std::string& msg) {}
};

DllPrefix void 
Sai_Net_Start(unsigned int port, 
              const char * localAddress, 
              const char * sendMcast, 
              const char * recvMcast)
{
  Net::GetInstance()->setPreferredAddress(localAddress);
  Net::GetInstance()->initialize();

  // Communication initialization
  McastDataBusChannel channel;
  channel.setPort(port);
  channel.setLocalAddress(Net::GetInstance()->getLocalAddress());
  channel.setSendMcast(sendMcast);
  channel.addRecvMcast(recvMcast);

  DataBus *bus = DataBus::GetInstance();
  bus->setChannel(&channel);

  DummyPrinter dummy;
  bus->setDefaultHandler(&dummy);

  ClientMsgHandler * msg = ClientMsgHandler::GetInstance();

  bus->registerHandler(TCSM_CLI_GENERIC, msg);

  bus->listen(TCSM_VS_CLIENT_MESSAGE);
  bus->activate();

  Net::GetInstance()->mainLoop();
}

DllPrefix void 
Sai_Net_Stop()
{
  Net::GetInstance()->shutdown();
}

DllPrefix void __stdcall 
Sai_Net_Send(const char * msg)
{
  ServerMsg * server = ServerMsg::GetInstance();
  server->send(msg);
}

DllPrefix void __stdcall 
Sai_Net_SetCallback(MsgCallback cb)
{
  ClientMsgHandler * msg = ClientMsgHandler::GetInstance();
  msg->setCallback(cb);
}

#endif
