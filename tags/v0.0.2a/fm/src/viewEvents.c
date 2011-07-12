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
#include "main.h"

extern gboolean open_folder_func(GAppLaunchContext* ctx, GList* folder_infos, gpointer user_data, GError** err);

void
on_file_clicked(FmFolderView* fv, FmFolderViewClickType type, FmFileInfo* fi, TcSmartWindow* win)
{
  switch(type)
  {
    case FM_FV_CLICK_NONE:
      break;
    case FM_FV_MIDDLE_CLICK:
      break;
    case FM_FV_CONTEXT_MENU:
      break;
    case FM_FV_ACTIVATED: /* file activated */
      if(fm_file_info_is_dir(fi))
      {
        fm_main_win_chdir(win, fi->path);
      }
#if 1
      else if(fi->target) 
      {
        fm_main_win_chdir_by_name( win, fi->target);
      }
#else
// SAI Note: The following block of code needs to be modified later.
      else if(fm_file_info_get_target(fi) && !fm_file_info_is_symlink(fi))
      {
        /* symlinks also has fi->target, but we only handle shortcuts here. */
        FmFileInfo* target_fi;
        FmPath* real_path = fm_path_new(fm_file_info_get_target(fi));
        /* query the info of target */
        FmJob* job = fm_file_info_job_new(NULL, 0);
        fm_file_info_job_add(FM_FILE_INFO_JOB(job), real_path);
        g_signal_connect(job, "error", NULL, win);
        fm_job_run_sync_with_mainloop(job);
        target_fi = FM_FILE_INFO(fm_list_peek_head(FM_FILE_INFO_JOB(job)->file_infos));
        if(target_fi)
          fm_file_info_ref(target_fi);
        g_object_unref(job);
        if(target_fi)
        {
          if(fm_file_info_is_dir(target_fi))
            fm_main_win_chdir( win, real_path);
          else
            fm_launch_path_simple(GTK_WINDOW(win), NULL, real_path, open_folder_func, win);
          fm_path_unref(FM_PATH(target_fi));
        }
        fm_path_unref(real_path);
      }
#endif
      else
      {
        fm_launch_file_simple(GTK_WINDOW(win), NULL, fi, open_folder_func, win);
      }
      break;
  }
}

void on_sel_changed(FmFolderView* fv, FmFileInfoList* files, TcSmartWindow* win)
{
  /* popup previous message if there is any */
  gtk_statusbar_pop(GTK_STATUSBAR(win->statusbar), win->statusbar_ctx2);
  if(files)
  {
    char* msg;
    /* FIXME: display total size of all selected files. */
    if(fm_list_get_length(files) == 1) /* only one file is selected */
    {
      FmFileInfo* fi = fm_list_peek_head(files);
      const char* size_str = fm_file_info_get_disp_size(fi);
      if(size_str)
      {
        msg = g_strdup_printf("\"%s\" (%s) %s",
          fm_file_info_get_disp_name(fi),
          size_str ? size_str : "",
          fm_file_info_get_desc(fi));
      }
      else
      {
        msg = g_strdup_printf("\"%s\" %s",
          fm_file_info_get_disp_name(fi),
          fm_file_info_get_desc(fi));
      }
    }
    else
    {
      msg = g_strdup_printf("%d items selected", fm_list_get_length(files));
    }
    gtk_statusbar_push(GTK_STATUSBAR(win->statusbar), win->statusbar_ctx2, msg);
    g_free(msg);
  }
}

