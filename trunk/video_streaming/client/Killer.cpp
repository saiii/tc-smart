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

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char * argv[])
{
  const int SIZE = 8;

  int segmentId = shmget (0x2011, SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  if (segmentId >= 0)
  {
    // No such process
    shmctl (segmentId, IPC_RMID, 0); 
    return 1;
  }

  segmentId = shmget (0x2011, SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);

  char * mem = (char*) shmat(segmentId, 0, 0);
  uint64_t num = 0;
  memcpy(&num, mem, sizeof(num));
  shmdt(mem);

  pid_t pid = (pid_t) num;

  if (kill(pid, SIGTERM) != 0)
  {
    sleep (2);
    kill(pid, SIGKILL);
  }

  if (segmentId > 0)
  {
    shmctl (segmentId, IPC_RMID, 0); 
    segmentId = 0;
  }
  return 0;
}
