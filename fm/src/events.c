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

#include <fm-places-view.h>
#include <fm-folder-view.h>
#include "main.h"
#include "config.h"

void 
on_entry_activate(GtkEntry* entry, TcSmartWindow* self)
{
  fm_folder_view_chdir_by_name(FM_FOLDER_VIEW(self->folder_view), gtk_entry_get_text(entry));
}

void 
on_status(FmFolderView* fv, const char* msg, TcSmartWindow* win)
{
  gtk_statusbar_pop(GTK_STATUSBAR(win->statusbar), win->statusbar_ctx);
  gtk_statusbar_push(GTK_STATUSBAR(win->statusbar), win->statusbar_ctx, msg);
}

void 
on_bookmark(GtkMenuItem* mi, TcSmartWindow* win)
{
  FmPath* path = (FmPath*)g_object_get_data(G_OBJECT(mi), "path");
  fm_main_win_chdir(win, path);
}

void 
on_places_chdir(FmPlacesView* view, guint button, FmPath* path, TcSmartWindow* win)
{
  fm_main_win_chdir(win, path);
}

void 
on_new_win(GtkAction* act, TcSmartWindow* win)
{
  win = fm_main_win_new();
  gtk_window_set_default_size(GTK_WINDOW(win), 640, 480);
  fm_main_win_chdir_by_name(win, Config_Get("DefaultDirectory")); 
  gtk_window_present(GTK_WINDOW(win));
}

void 
on_close_win(GtkAction* act, TcSmartWindow* win)
{
  gtk_widget_destroy(GTK_WIDGET(win));
}

void 
on_open_in_new_win(GtkAction* act, TcSmartWindow* win)
{
  FmPathList* sels = fm_folder_view_get_selected_file_paths(FM_FOLDER_VIEW(win->folder_view));
  GList* l;
  for( l = fm_list_peek_head_link(sels); l; l=l->next )
  {
    FmPath* path = (FmPath*)l->data;
    win = fm_main_win_new();
    gtk_window_set_default_size(GTK_WINDOW(win), 640, 480);
    fm_main_win_chdir(win, path);
    gtk_window_present(GTK_WINDOW(win));
  }
  fm_list_unref(sels);
}

void 
on_go_network(GtkAction* act, TcSmartWindow* win)
{
  fm_main_win_chdir_by_name( win, Config_Get("DefaultDirectory"));
}

void 
on_select_all(GtkAction* act, TcSmartWindow* win)
{
  fm_folder_view_select_all(FM_FOLDER_VIEW(win->folder_view));
}

void 
on_invert_select(GtkAction* act, TcSmartWindow* win)
{
  fm_folder_view_select_invert(FM_FOLDER_VIEW(win->folder_view));
}

void 
on_show_hidden(GtkToggleAction* act, TcSmartWindow* win)
{
  gboolean active = gtk_toggle_action_get_active(act);
  fm_folder_view_set_show_hidden( FM_FOLDER_VIEW(win->folder_view), active );
}

void 
on_change_mode(GtkRadioAction* act, GtkRadioAction *cur, TcSmartWindow* win)
{
  int mode = gtk_radio_action_get_current_value(cur);
  fm_folder_view_set_mode(FM_FOLDER_VIEW(win->folder_view), mode);
}

void 
on_sort_by(GtkRadioAction* act, GtkRadioAction *cur, TcSmartWindow* win)
{
  int val = gtk_radio_action_get_current_value(cur);
  fm_folder_view_sort(FM_FOLDER_VIEW(win->folder_view), -1, val);
}

void 
on_sort_type(GtkRadioAction* act, GtkRadioAction *cur, TcSmartWindow* win)
{
  int val = gtk_radio_action_get_current_value(cur);
  fm_folder_view_sort(FM_FOLDER_VIEW(win->folder_view), val, -1);
}

