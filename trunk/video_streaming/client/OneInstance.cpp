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

#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>

#include "OneInstance.h"

int OneInstance::_segmentId = 0;

OneInstance::OneInstance()
{
}

OneInstance::~OneInstance()
{
}

OneInstanceStatus 
OneInstance::check()
{
  const int SIZE = 4;

  _segmentId = shmget (0x2011, SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  if (_segmentId < 0)
  {
    return EXIT_NEEDED;
  }

  atexit(OneInstance::onExit);
  signal(SIGHUP,  OneInstance::onSignal); 
  signal(SIGINT,  OneInstance::onSignal); 
  //signal(SIGQUIT, OneInstance::onSignal); 
  //signal(SIGTRAP, OneInstance::onSignal); 
  signal(SIGKILL, OneInstance::onSignal); 
  signal(SIGTERM, OneInstance::onSignal); 

  return GOOD_TO_GO;
}

void 
OneInstance::onExit()
{
  if (_segmentId > 0)
  {
    shmctl (_segmentId, IPC_RMID, 0); 
    _segmentId = 0;
  }
}

void 
OneInstance::onSignal(int sig)
{
  onExit();
  exit(0);
}

