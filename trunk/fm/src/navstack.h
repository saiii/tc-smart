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

#ifndef __TCSMART_FM_NAVSTACK__
#define __TCSMART_FM_NAVSTACK__

typedef void* NavStack;

typedef struct
{
  char * path;
  int    pos;
}NavStackElement;

NavStack *       NavStack_new(void);
void             NavStack_destroy(NavStack*);
void             NavStack_push(NavStack*, char*, int pos);
void             NavStack_back(NavStack*);
void             NavStack_next(NavStack*);
NavStackElement* NavStack_get(NavStack*);
unsigned int     NavStack_size(NavStack*);
unsigned int     NavStack_left_size(NavStack*);
unsigned int     NavStack_right_size(NavStack*);
void             NavStack_clear(NavStack*);

#endif
