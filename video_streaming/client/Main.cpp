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
#include <unistd.h>
#include <vlc/vlc.h>

#include "OneInstance.h"
#include "Daemonizer.h"
#include "Command.h"

int main(int argc, char* argv[])
{
  printf("LibVLC Version: %s\n", libvlc_get_version()); 
  printf("VideoStreamingClient Version: 0.1.4a\n"); 
  // Become a daemon
  Daemonizer daemon;
  if (!daemon.initialize())
  {
    return 0;
  }

  // Make sure there is no other instance of the program running
  OneInstance one;
  if (one.check() == EXIT_NEEDED)
  {
    printf("only one instance at a time\n");
    return 1;
  }

  chdir("/usr/share/tc-smart/");

  Command command;
  command.initialize();
  return 0;
}
