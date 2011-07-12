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

#include <fm-folder-view.h>
#include <fm-path-entry.h>
#include "main.h"

void on_go_back(GtkAction* act, TcSmartWindow* win)
{
  if (NavStack_left_size(win->nav_stack) > 1)
  {
    NavStack_back(win->nav_stack);
    NavStackElement * elem = NavStack_get(win->nav_stack);
    fm_main_win_chdir_by_name(win, elem->path);
  }
}

void on_go_forward(GtkAction* act, TcSmartWindow* win)
{
  if (NavStack_right_size(win->nav_stack) > 0)
  {
    NavStack_next(win->nav_stack);
    NavStackElement * elem = NavStack_get(win->nav_stack);
    fm_main_win_chdir_by_name(win, elem->path);
  }
}

void on_view_loaded( FmFolderView* view, FmPath* path, gpointer user_data)
{
  TcSmartWindow* win = (TcSmartWindow*)user_data;

  if (NavStack_left_size(win->nav_stack) > 0)
  {
    NavStackElement * elem = NavStack_get(win->nav_stack);
    gtk_adjustment_set_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(view)), elem->pos);
  }
}

