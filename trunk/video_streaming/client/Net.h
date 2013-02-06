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

#ifndef __TCSMART_NET__
#define __TCSMART_NET__

#include <vector>
#include <utils/ThreadPool.h>

class EventListener
{
public:
  virtual void timerEvent() = 0;
  virtual void startEvent(char *) = 0;
  virtual void updateEvent(char *) = 0;
  virtual void shutdownEvent() = 0;
};

typedef enum
{
  START = 0,
  UPDATE = 1,
  SHUTDOWN = 2
}EventQueueType;

typedef struct
{
  EventQueueType type;
  char *         msg;
}EventQueue;

class Agent;
typedef std::vector<Agent*>           AgentList;
typedef std::vector<Agent*>::iterator AgentListIterator;
typedef std::vector<int>           EventQueueList;
typedef std::vector<int>::iterator EventQueueListIterator;

class Net 
{
private:
  EventListener * _listener;
  AgentList       _list;
  EventQueueList  _eList;

public:
  Net();
  virtual ~Net();
  
  void setListener(EventListener* listener) { _listener = listener; }

  void initialize();
  void mainLoop();
  void send(char * buf, int size);
  EventQueueList* getEventList() { return &_eList; }
};

class Agent : public sai::utils::ThreadTask
{
private:
  int _fd;
  Net * _net;

public:
  Agent(Net * net);
  ~Agent();

  void initialize(char * addr);
  void threadEvent();
  void send(char * buf, int size);
};

#endif
