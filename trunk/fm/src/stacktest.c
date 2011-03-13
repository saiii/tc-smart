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
#include "navstack.h"

int main(int argc, char * argv[])
{
  NavStack * stack = NavStack_new();
  
  char *data [] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
  int i = 0;
  for (i = 0; i < 9; i += 1)
  {
    NavStack_push(stack, data[i], i);
  }
  printf("stack size = %d\n", NavStack_size(stack));

  for (i = 0; i < 9; i += 1)
  {
    NavStackElement* data = NavStack_get(stack);
    NavStack_back(stack);

    printf("[%d] = %s\n", i, data->path);
  }
  printf("stack size = %d\n", NavStack_size(stack));

  for (i = 0; i < 9; i += 1)
  {
    NavStack_push(stack, data[i], i);
  }
  printf("stack size = %d\n", NavStack_size(stack));

  for (i = 0; i < 4; i += 1)
  {
    NavStackElement * data = NavStack_get(stack);
    NavStack_back(stack);

    printf("[%d] = %s\n", i, data->path);
  }
  printf("stack size = %d\n", NavStack_size(stack));

  char *v2 [] = {"20", "21", "22", "23"};
  for (i = 0; i < 4; i += 1)
  {
    NavStack_push(stack, v2[i], i);
  }
  printf("stack size = %d\n", NavStack_size(stack));

  for (i = 0; i < 9; i += 1)
  {
    NavStackElement * data = NavStack_get(stack);
    NavStack_back(stack);

    printf("[%d] = %s\n", i, data->path);
  }
  printf("stack size = %d\n", NavStack_size(stack));

  for (i = 0; i < 9; i += 1)
  {
    NavStack_push(stack, data[i], i);
  }
  NavStackElement* top = NavStack_get(stack);
  printf("top element is = %s\n", top->path);
  printf("stack size = %d\n", NavStack_size(stack));

  NavStack_clear(stack);
  printf("stack size = %d\n", NavStack_size(stack));

  NavStack_destroy(stack);
  return 0;
}
