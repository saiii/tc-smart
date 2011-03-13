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

#include <gtk/gtk.h>
#include <fm-path-entry.h>
#include "main.h"
#include "config.h"

int 
main(int argc, char** argv)
{
  GtkWidget* window;
  gtk_init(&argc, &argv);

  fm_gtk_init(0);
  Config_Initialize();

  window = fm_main_win_new();
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_widget_show(window);

  FmPath* path = fm_path_new(Config_Get("DefaultDirectory"));
  fm_main_win_chdir(FM_MAIN_WIN(window), path);
  fm_path_unref(path);

  gtk_main();

  Config_Destroy();
  fm_finalize();
  return 0;
}

