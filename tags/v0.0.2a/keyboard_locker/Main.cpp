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
#include <unistd.h>
#include <stdint.h>
#include <ctype.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/regex.hpp>

#include <net/Net.h>
#include <net/DataBus.h>
#include <utils/XmlReader.h>
#include <net/DataHandler.h>
#include <net/DataDescriptor.h>
#include <net/TimerTask.h>

#include <Message.h>

#include "Daemonizer.h"
#include "Cmd.h"

using namespace sai::net;

typedef std::vector<uint32_t>           IList;
typedef std::vector<uint32_t>::iterator IListIterator;

class Locker : public DataHandler,
               public TimerTask
{
private:
  IList _mList;
  IList _kList;
  int   _cnt;

private:

public:
  Locker();
  ~Locker();

  void load();
  void lock();
  void unlock();

  void initialize();
  void processDataEvent(DataDescriptor& desc, std::string& msg);
  void timerEvent();
};

int main(int argc, char* argv[])
{
  printf("KeyboardLockerClient Version: 0.0.2a\n"); 
  // Become a daemon
  Daemonizer daemon;
  if (!daemon.initialize())
  {
    return 0;
  }

  chdir("/usr/share/tc-smart/");

#if TEST
  Locker locker;
  if (argc == 2)
  {
    if (strcmp(argv[1], "lock") == 0) locker.lock();
    sleep(10);
    locker.unlock();
  }
#endif 

  Locker locker;
  locker.initialize();

  return 0;
}

Locker::Locker():
  _cnt(0)
{
}

Locker::~Locker()
{
}

class Default : public DataHandler
{
public:
  void processDataEvent(DataDescriptor& desc, std::string& msg)
  {
  }
};

void
Locker::load()
{
  std::string list = Cmd().execute("xinput --list");
  if (list.compare(0, 29, "Unable to connect to X server") == 0)
  {
    return;
  }

  _mList.clear();
  _kList.clear();

  std::vector<char*> stringList;

  char * ptr = 0;
  char * all = (char*) list.c_str();
  char * end = all + list.length();
  for (char * cur = all; cur < end; cur += 1)
  {
    if (ptr == 0)
    {
      ptr = cur;
    }
 
    if (*cur == '\n')
    {
      *cur = 0;
      char * t = strdup(ptr);
      ptr = 0;
      stringList.push_back(t);
    }
  }
  if (ptr)
  {
    char * t = strdup(ptr);
    stringList.push_back(t);
  }

  boost::basic_regex<char> *ePointer  = new boost::basic_regex<char>(".*slave[ ]+pointer.*");
  boost::basic_regex<char> *eKeyboard    = new boost::basic_regex<char>(".*slave[ ]+keyboard.*");
  boost::basic_regex<char> *eKeyboardExp = new boost::basic_regex<char>(".*(Power|Sleep).*");
  std::vector<char*>::iterator iter;
  for(iter  = stringList.begin();        
      iter != stringList.end();
      iter ++)
  {
    char * ch = *iter;
    char * idToken = 0;
    if (boost::regex_match(ch, *ePointer) && (idToken = strstr(ch, "id=")) != 0)
    {
      idToken += 3;
      char id [5] = {idToken[0], idToken[1], idToken[2], idToken[3], 0};
      for (int i = 0; i < 5; i += 1)
      {
        if (isblank(id[i]))
        {
          id[i] = 0;
        }
      }
      _mList.push_back(atoi(id));
    }
    else if (boost::regex_match(ch, *eKeyboard) && 
             (idToken = strstr(ch, "id=")) != 0 && 
             !boost::regex_match(ch, *eKeyboardExp))
    {
      idToken += 3;
      char id [5] = {idToken[0], idToken[1], idToken[2], idToken[3], 0};
      for (int i = 0; i < 5; i += 1)
      {
        if (isblank(id[i]))
        {
          id[i] = 0;
        }
      }
      _kList.push_back(atoi(id));
    }
  }
  delete eKeyboard;
  delete ePointer;
}

void
Locker::initialize()
{
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

  schedule(2, 0);

  Default def;
  bus->setDefaultHandler(&def);

  bus->registerHandler(TCSM_SVR_LOCKER,  this);
  bus->listen(TCSM_VS_SERVER_MESSAGE);
  bus->activate();

  Net::GetInstance()->mainLoop();
  exit(0);
}

void
Locker::processDataEvent(DataDescriptor& desc, std::string& msg)
{
  sai::utils::XmlReader reader;
  reader.parseMem(msg);
  reader.moveTo("ls_msg");
  std::string lck = reader.get("lock", "value");
  if (lck.length() > 0)
  {
    _cnt = 0;
    if (lck.compare("true") == 0)
    {
      lock();
    }
    else if (lck.compare("false") == 0)
    {
      unlock();
    }
  }
}

void 
Locker::timerEvent()
{
  if (_cnt < 100)
  {
    _cnt += 1;
    if (_cnt >= 30)
    {
      unlock();
      _cnt = 100;
    }
  }
  schedule();
}

void 
Locker::lock()
{
  if (_mList.size() == 0 || _kList.size() == 0)
  {
    load();
  }

  Cmd cmd;
  for (int i = 0; i < _mList.size(); i += 1)
  {
    int value = _mList.at(i);
    
    std::stringstream txt;
    txt << "xinput set-int-prop " << value << " \"Device Enabled\" 8 0" << std::endl;
    cmd.execute(txt.str()); 
  }

  for (int i = 0; i < _kList.size(); i += 1)
  {
    int value = _kList.at(i);

    std::stringstream txt;
    txt << "xinput set-int-prop " << value << " \"Device Enabled\" 8 0" << std::endl;
    cmd.execute(txt.str()); 
  }
}

void 
Locker::unlock()
{
  if (_mList.size() == 0 || _kList.size() == 0)
  {
    load();
  }

  Cmd cmd;
  for (int i = 0; i < _mList.size(); i += 1)
  {
    int value = _mList.at(i);

    std::stringstream txt;
    txt << "xinput set-int-prop " << value << " \"Device Enabled\" 8 1" << std::endl;
    cmd.execute(txt.str()); 
  }

  for (int i = 0; i < _kList.size(); i += 1)
  {
    int value = _kList.at(i);

    std::stringstream txt;
    txt << "xinput set-int-prop " << value << " \"Device Enabled\" 8 1" << std::endl;
    cmd.execute(txt.str()); 
  }
  _mList.clear();
  _kList.clear();
}

