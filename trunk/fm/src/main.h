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

#ifndef __TCSMART_FM_MAIN__
#define __TCSMART_FM_MAIN__

#include <gtk/gtk.h>
#include "navstack.h"

#define FM_MAIN_WIN_TYPE             (fm_main_win_get_type())
#define FM_MAIN_WIN(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), FM_MAIN_WIN_TYPE, HakoWindow))
#define FM_MAIN_WIN_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), FM_MAIN_WIN_TYPE, HakoWindowClass))
#define IS_FM_MAIN_WIN(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), FM_MAIN_WIN_TYPE))
#define IS_FM_MAIN_WIN_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), FM_MAIN_WIN_TYPE))

typedef struct _HakoWindow
{
  GtkWindow     dummy;
  GtkUIManager* ui;
  GtkWidget*    toolbar;
  GtkWidget*    hpaned;
  GtkWidget*    folder_view;
  GtkWidget*    statusbar;

  /* <private> */
  NavStack      nav_stack;
  guint         statusbar_ctx;
  guint         statusbar_ctx2;
}HakoWindow;

typedef struct _HakoWindowClass
{
  GtkWindowClass parent_class;
}HakoWindowClass;

#endif
