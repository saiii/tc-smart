//=============================================================================
// Copyright (C) 2013 Athip Rooprayochsilp <athipr@gmail.com>
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

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#include <net2/Net.h>
#include <net2/Nic.h>
#include <net2/NicList.h>

#include "Net.h"

Net::Net():
  _listener(0)
{
}

Net::~Net()
{
  while (_list.size() > 0)
  {
    Agent * agent = _list.front();
    _list.erase(_list.begin());
    delete agent;
  }
}

void 
Net::initialize()
{
  sai::net2::NicList * nList = new sai::net2::NicList();
  nList->detect();
  for (int i = 0; i < nList->size(); i += 1)
  {
    std::string nic;
    nList->getNic(i)->toString(nic);
    Agent * agent = new Agent(this);
    agent->initialize((char*)nic.c_str());
    agent->schedule();
    _list.push_back(agent);
  }
  delete nList;
}

void 
Net::mainLoop()
{

  int count = 0;
  for(;;)
  {
    //fd_set readfds;
    //FD_ZERO(&readfds);
    //FD_SET(0, &readfds);
    //struct timeval timeout;
    //timeout.tv_sec  = 0;
    //timeout.tv_usec = 500000;
    //select(1, &readfds, 0, 0, &timeout);
    struct timespec ts;
    ts.tv_sec  = 0;
    ts.tv_nsec = 500000000;

    nanosleep(&ts, 0);
    if (_listener && ++count >= 4)
    {
      _listener->timerEvent();
      count = 0;
    }

    if (_eList.size() > 0)
    {
      EventQueue * event = _eList.front();
      _eList.erase(_eList.begin());

      if (_listener)
      {
        switch(event->type)
        {
          case START:
            _listener->startEvent(0);
            break;
          case UPDATE:
            _listener->updateEvent(0);
            break;
          case SHUTDOWN:
            _listener->shutdownEvent();
            break;
        }
      }

      delete event;
    }
  }
}

void 
Net::send(char * buf, int size)
{
  AgentListIterator iter;
  for(iter  = _list.begin();
      iter != _list.end();
      iter ++)
  {
    Agent * agent = *iter;
    agent->send(buf, size);
  }
}

Agent::Agent(Net * net):
  _fd(-1),
  _net(net)
{
}

Agent::~Agent()
{
}

void 
Agent::initialize(char * addr)
{
  _fd = socket(AF_INET,SOCK_DGRAM,0);

  struct in_addr intf;
  intf.s_addr = inet_addr(addr);
  setsockopt(_fd, IPPROTO_IP, IP_MULTICAST_IF, (const char*)&intf, sizeof(intf));

  struct sockaddr_in svrAddress;
  memset(&svrAddress, 0, sizeof(svrAddress));
  svrAddress.sin_family = AF_INET;
  svrAddress.sin_addr.s_addr=htonl(INADDR_ANY);
  svrAddress.sin_port = htons(8010);

  int optval = 1;
  setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

  bind(_fd,(struct sockaddr *)&svrAddress, sizeof(svrAddress));

  // Join
  struct ip_mreq imreq;
  memset(&imreq, 0, sizeof(struct ip_mreq));
  imreq.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
  imreq.imr_interface.s_addr = inet_addr(addr);
  setsockopt(_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&imreq, sizeof(struct ip_mreq));

  memset(&imreq, 0, sizeof(struct ip_mreq));
  imreq.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
  imreq.imr_interface.s_addr = inet_addr(addr);
  setsockopt(_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&imreq, sizeof(struct ip_mreq));
}

void 
Agent::threadEvent()
{
  struct timeval timeout;
  timeout.tv_sec = 2;
  timeout.tv_usec= 0;
  setsockopt(_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

  char buf[1024] = {0};
  for(;;)
  {
    struct sockaddr_in remoteAddress;
    socklen_t len = sizeof(remoteAddress);
    ssize_t bytes = recvfrom(_fd, buf, sizeof(buf), 0, (struct sockaddr *)&remoteAddress, &len);
    if (bytes > 0)
    {
      buf[bytes] = 0;
      EventQueueList* queue = _net->getEventList();
      EventQueue * event = new EventQueue();
      //event->msg = strdup(buf);
      if (strstr(buf, "start")) 
      {
        event->type = START; 
      }
      else if (strstr(buf, "time")) 
      {
        event->type = UPDATE; 
      }
      else if (strstr(buf, "shutdown")) 
      {
        event->type = SHUTDOWN; 
      }
      queue->push_back(event);
    }
  }

  // Leave
  close(_fd);
}

void 
Agent::send(char * buf, int size)
{
  struct sockaddr_in svrAddress;
  memset(&svrAddress, 0, sizeof(svrAddress));
  svrAddress.sin_family = AF_INET;
  svrAddress.sin_addr.s_addr = inet_addr("225.2.2.2");
  svrAddress.sin_port = htons(8011);

  sendto(_fd, buf, size, 0, (struct sockaddr *)&svrAddress, sizeof(svrAddress));
}

