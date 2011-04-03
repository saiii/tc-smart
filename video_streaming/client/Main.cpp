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

#include "OneInstance.h"
#include "Daemonizer.h"

int main(int argc, char* argv[])
{
  // Make sure there is no other instance of the program running
  OneInstance one;
  if (one.check() == EXIT_NEEDED)
  {
    printf("need to exit now\n");
    return 1;
  }

  // Become a daemon
  Daemonizer daemon;
  daemon.initialize();

  while (1) sleep(1);
  // Init session
  // Use the given argument as port and listening address
  // Otherwise, use 2012 as default

  // Wait transcode and play command from server
  // play
  // there might be pause or stop ??
  // get shutdown command from server and turn off the window

  return 0;
}
