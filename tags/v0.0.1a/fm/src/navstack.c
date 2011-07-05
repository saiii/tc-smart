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

#include <stdlib.h>
#include "navstack.h"

typedef struct _StackElement
{
  struct _StackElement *down;  
  NavStackElement      *data;
}StackElement;

typedef struct
{
  StackElement * head;
  StackElement * tail;
  unsigned int   size;
}_Stack;

_Stack *         Stack_new(void);
void             Stack_destroy(_Stack*);
void             Stack_push(_Stack*, NavStackElement*);
NavStackElement* Stack_pop(_Stack*);
NavStackElement* Stack_top(_Stack*);
unsigned int     Stack_size(_Stack*);
void             Stack_clear(_Stack*);

_Stack *   
Stack_new(void)
{
  _Stack * stack = (_Stack*) malloc (sizeof(_Stack));
  stack->head = (StackElement*) malloc (sizeof(StackElement));
  stack->head->down = 0;
  stack->head->data = 0;
  stack->tail = stack->head;
  stack->size       = 0;
  return (_Stack*) stack;
}

void         
Stack_destroy(_Stack* stck)
{
  _Stack * stack = (_Stack*)stck;
  if (stack && stack->head)
  {
    if (stack->size > 0)
    {
      Stack_clear(stck);
    }
    free(stack->head);
    free(stack);
  }
}

void         
Stack_push(_Stack* stck, NavStackElement* data)
{
  _Stack* stack = (_Stack*)stck;
  StackElement * elem = (StackElement*) malloc (sizeof(StackElement));
  elem->down = stack->tail;
  elem->data = data;
  stack->tail  = elem;
  stack->size += 1;
}

NavStackElement*        
Stack_pop(_Stack* stck)
{
  _Stack* stack = (_Stack*)stck;
  NavStackElement* ret = 0;
  if (stack->size > 0)
  {
    StackElement * tmp = stack->tail->down;
    ret = stack->tail->data;
    free(stack->tail);
    stack->size -= 1;
    stack->tail  = tmp;
  }
  return ret;
}

NavStackElement*        
Stack_top(_Stack* stck)
{
  _Stack* stack = (_Stack*)stck;
  NavStackElement* ret = 0;
  if (stack->size > 0)
  {
    ret = stack->tail->data;
  }
  return ret;
}

unsigned int 
Stack_size(_Stack* stck)
{
  _Stack* stack = (_Stack*)stck;
  return stack->size;
}

void         
Stack_clear(_Stack* stck)
{
  _Stack* stack = (_Stack*)stck;
  while (stack->size > 0)
  {
    NavStackElement* elem = Stack_pop(stck);
    free(elem->path);
    free(elem);
  }
}

//=============================================================================

typedef struct
{
  _Stack * left;
  _Stack * right;
}_NavStack;

NavStack *   
NavStack_new(void)
{
  _NavStack * ret = (_NavStack*) malloc (sizeof(_NavStack));
  ret->left = Stack_new();
  ret->right= Stack_new();
  return (NavStack)ret;
}

void         
NavStack_destroy(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  Stack_destroy(stack->right);
  Stack_destroy(stack->left);
  free(stack);
}

void         
NavStack_push(NavStack* stk, char* data, int pos)
{
  _NavStack * stack = (_NavStack*) stk;
  if (NavStack_left_size(stk) > 0)
  {
    NavStackElement * last = NavStack_get(stk);
    if (strcmp(last->path, data) == 0) 
    {
      return;
    }
  }

  NavStackElement * elem = (NavStackElement*) malloc (sizeof(NavStackElement));
  elem->path = strdup(data);
  elem->pos  = pos;
  Stack_push(stack->left, elem);
  Stack_clear(stack->right);
}

void         
NavStack_back(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  NavStackElement * cur = Stack_pop(stack->left);
  Stack_push(stack->right, cur);
}

void         
NavStack_next(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  NavStackElement * cur = Stack_pop(stack->right);
  Stack_push(stack->left, cur);
}

NavStackElement*        
NavStack_get(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  return Stack_top(stack->left);
}

unsigned int 
NavStack_size(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  return (Stack_size(stack->left) + Stack_size(stack->right));
}

unsigned int 
NavStack_left_size(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  return Stack_size(stack->left);
}

unsigned int 
NavStack_right_size(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  return Stack_size(stack->right);
}

void         
NavStack_clear(NavStack* stk)
{
  _NavStack * stack = (_NavStack*) stk;
  Stack_clear(stack->left);  
  Stack_clear(stack->right);  
}

