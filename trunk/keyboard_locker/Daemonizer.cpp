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

#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#endif

#include <stdio.h>
#include "Daemonizer.h"

Daemonizer::Daemonizer()
{

}

Daemonizer::~Daemonizer()
{
}

bool
Daemonizer::initialize()
{
#ifndef _WIN32
  pid_t pid;

  if ((pid = fork()) < 0)
  {
    fprintf(stderr, "Failed to fork the process.\n");
    return false;
  }
  else if (pid)
  {
    // Parent
    return false;    
  }

  if (setsid() < 0)
  {
    fprintf(stderr, "Failed to setsid to the process.\n");
    return false;
  }

  signal(SIGHUP, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);

  if ((pid = fork()) < 0)
  {
    fprintf(stderr, "Failed to fork the process.\n");
    return false;
  }
  else if (pid)
  {
    // First child
    return false;    
  }

  uint16_t MAXFD = getdtablesize();
  for (uint16_t i = 0; i < MAXFD; i += 1)
  {
    if (i != 1 && i != 2) // we still need stdout and stderr
      close(i);
  }
  // redirect stdin to /dev/null
  open("/dev/null", O_RDONLY);
#endif

  return true;
}

