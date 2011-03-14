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
#include "config.h"
#include "actionsMap.h"

G_DEFINE_TYPE(TcSmartWindow, fm_main_win, GTK_TYPE_WINDOW);

static guint n_wins = 0;

extern void on_file_clicked(FmFolderView* fv, FmFolderViewClickType type, FmFileInfo* fi, TcSmartWindow* win);
extern void on_sel_changed(FmFolderView* fv, FmFileInfoList* files, TcSmartWindow* win);
extern void on_status(FmFolderView* fv, const char* msg, TcSmartWindow* win);
extern void on_entry_activate(GtkEntry* entry, TcSmartWindow* self);
extern void on_view_loaded( FmFolderView* view, FmPath* path, gpointer user_data);

gboolean open_folder_func(GAppLaunchContext* ctx, GList* folder_infos, gpointer user_data, GError** err)
{
  TcSmartWindow* win = FM_MAIN_WIN(user_data);
  GList* l = folder_infos;
  FmFileInfo* fi = (FmFileInfo*)l->data;
  fm_main_win_chdir(win, fi->path);
  return TRUE;
}

void 
fm_main_win_init(TcSmartWindow *self)
{
  GtkWidget *vbox, *toolitem;
  GtkUIManager* ui;
  GtkActionGroup* act_grp;
  GtkAction* act;
  GtkAccelGroup* accel_grp;
  
  ++n_wins;
  
  vbox = gtk_vbox_new(FALSE, 0);
  
  self->hpaned = gtk_hpaned_new();
  gtk_paned_set_position(GTK_PANED(self->hpaned), 150);

  /* folder view */
  self->folder_view = fm_folder_view_new( FM_FV_ICON_VIEW );
  fm_folder_view_set_show_hidden(FM_FOLDER_VIEW(self->folder_view), FALSE);
  fm_folder_view_sort(FM_FOLDER_VIEW(self->folder_view), GTK_SORT_ASCENDING, COL_FILE_NAME);
  fm_folder_view_set_selection_mode(FM_FOLDER_VIEW(self->folder_view), GTK_SELECTION_MULTIPLE);
  g_signal_connect(self->folder_view, "clicked", on_file_clicked, self);
  g_signal_connect(self->folder_view, "status", on_status, self);
  g_signal_connect(self->folder_view, "sel-changed", on_sel_changed, self);
  
  gtk_paned_add2(GTK_PANED(self->hpaned), self->folder_view);
  
  /* create menu bar and toolbar */
  ui = gtk_ui_manager_new();
  act_grp = gtk_action_group_new("Main");
  gtk_action_group_add_actions(act_grp, main_win_actions, G_N_ELEMENTS(main_win_actions), self);
  gtk_action_group_add_toggle_actions(act_grp, main_win_toggle_actions, 
    G_N_ELEMENTS(main_win_toggle_actions), self);
  gtk_action_group_add_radio_actions(act_grp, main_win_mode_actions, 
    G_N_ELEMENTS(main_win_mode_actions), FM_FV_ICON_VIEW, on_change_mode, self);
  gtk_action_group_add_radio_actions(act_grp, main_win_sort_type_actions, 
    G_N_ELEMENTS(main_win_sort_type_actions), GTK_SORT_ASCENDING, on_sort_type, self);
  gtk_action_group_add_radio_actions(act_grp, main_win_sort_by_actions, 
    G_N_ELEMENTS(main_win_sort_by_actions), 0, on_sort_by, self);
  
  accel_grp = gtk_ui_manager_get_accel_group(ui);
  gtk_window_add_accel_group(GTK_WINDOW(self), accel_grp);
  gtk_ui_manager_insert_action_group(ui, act_grp, 0);
  gtk_ui_manager_add_ui_from_string(ui, main_menu_xml, -1, NULL);

  self->toolbar = gtk_ui_manager_get_widget(ui, "/toolbar"); 
  gtk_toolbar_set_icon_size(GTK_TOOLBAR(self->toolbar), GTK_ICON_SIZE_LARGE_TOOLBAR);
  gtk_toolbar_set_style(GTK_TOOLBAR(self->toolbar), GTK_TOOLBAR_ICONS);
  
  /* create 'Next' button manually and add a popup menu to it */
  toolitem = g_object_new(GTK_TYPE_MENU_TOOL_BUTTON, NULL);
  gtk_toolbar_insert(GTK_TOOLBAR(self->toolbar), toolitem, 2);
  gtk_widget_show(GTK_WIDGET(toolitem));
  act = gtk_ui_manager_get_action(ui, "/menubar/GoMenu/Next"); 
  gtk_activatable_set_related_action(GTK_ACTIVATABLE(toolitem), act);
  
  /* set up history menu */
  self->nav_stack = NavStack_new();
  
  gtk_box_pack_start((GtkBox*)vbox, self->toolbar, FALSE, TRUE, 0);
  
  g_signal_connect(self->folder_view, "loaded", G_CALLBACK(on_view_loaded), (gpointer) self);
  
  gtk_box_pack_start((GtkBox*)vbox, self->hpaned, TRUE, TRUE, 0);
  
  /* status bar */
  self->statusbar = gtk_statusbar_new();
  gtk_box_pack_start( (GtkBox*)vbox, self->statusbar, FALSE, TRUE, 0 );
  self->statusbar_ctx  = gtk_statusbar_get_context_id(GTK_STATUSBAR(self->statusbar), "status");
  self->statusbar_ctx2 = gtk_statusbar_get_context_id(GTK_STATUSBAR(self->statusbar), "status2");
  
  g_object_unref(act_grp);
  self->ui = ui;
  
  gtk_container_add( (GtkContainer*)self, vbox );
  gtk_widget_show_all(vbox);
  
  fm_folder_view_set_show_hidden(FM_FOLDER_VIEW(self->folder_view), FALSE);
  fm_main_win_chdir_by_name(self, Config_Get("DefaultDirectory"));
  
  gtk_widget_grab_focus(self->folder_view);
}

void 
fm_main_win_finalize(GObject *object)
{
  TcSmartWindow *self;
  
  g_return_if_fail(object != NULL);
  g_return_if_fail(IS_FM_MAIN_WIN(object));
  
  --n_wins;
  
  self = FM_MAIN_WIN(object);
  
  NavStack_destroy(self->nav_stack);
  g_object_unref(self->ui);
  
  if (G_OBJECT_CLASS(fm_main_win_parent_class)->finalize)
  {
    (* G_OBJECT_CLASS(fm_main_win_parent_class)->finalize)(object);
  }
  
  if(n_wins == 0)
  {
    gtk_main_quit();
  }
}

void 
fm_main_win_class_init(TcSmartWindowClass *klass)
{
  GObjectClass *g_object_class;
  g_object_class = G_OBJECT_CLASS(klass);
  g_object_class->finalize = fm_main_win_finalize;
  fm_main_win_parent_class = (GtkWindowClass*)g_type_class_peek(GTK_TYPE_WINDOW);
}

void 
fm_main_win_chdir_by_name(TcSmartWindow* win, const char* path_str)
{
  FmPath* path;
  char* tmp;
  path = fm_path_new_for_str(path_str);
  fm_folder_view_chdir(FM_FOLDER_VIEW(win->folder_view), path);
  tmp = fm_path_display_name(path, FALSE);
  g_free(tmp);
  fm_path_unref(path);
  NavStack_push(win->nav_stack, path_str, 0);
}

void 
fm_main_win_chdir_without_history(TcSmartWindow* win, FmPath* path)
{
  fm_folder_view_chdir(FM_FOLDER_VIEW(win->folder_view), path);
}

void 
fm_main_win_chdir(TcSmartWindow* win, FmPath* path)
{
  int scroll_pos = gtk_adjustment_get_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(win->folder_view)));
  char * str = fm_path_to_str(path);
  NavStack_push(win->nav_stack, str, scroll_pos);
  free(str);
  fm_main_win_chdir_without_history(win, path);
}

GtkWidget* 
fm_main_win_new(void)
{
  return (GtkWidget*)g_object_new(FM_MAIN_WIN_TYPE, NULL);
}

