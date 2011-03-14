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

// This file is a modification of 'main-win-ui.c' which is a part of
// demonstration of the libfm by PCMan.

#ifndef __TCSMART_FM_ACTIONSMAP__
#define __TCSMART_FM_ACTIONSMAP__

#include <glib/gi18n.h>

extern void on_new_win(GtkAction* act, TcSmartWindow* win);
extern void on_close_win(GtkAction* act, TcSmartWindow* win);
extern void on_open_in_new_win(GtkAction* act, TcSmartWindow* win);

extern void on_go_back(GtkAction* act, TcSmartWindow* win);
extern void on_go_forward(GtkAction* act, TcSmartWindow* win);
extern void on_go_network(GtkAction* act, TcSmartWindow* win);

extern void on_select_all(GtkAction* act, TcSmartWindow* win);
extern void on_invert_select(GtkAction* act, TcSmartWindow* win);
extern void on_show_hidden(GtkToggleAction* act, TcSmartWindow* win);
extern void on_change_mode(GtkRadioAction* act, GtkRadioAction *cur, TcSmartWindow* win);
extern void on_sort_by(GtkRadioAction* act, GtkRadioAction *cur, TcSmartWindow* win);
extern void on_sort_type(GtkRadioAction* act, GtkRadioAction *cur, TcSmartWindow* win);

extern void on_cut(GtkAction* act, TcSmartWindow* win);
extern void on_copy(GtkAction* act, TcSmartWindow* win);
extern void on_copy_to(GtkAction* act, TcSmartWindow* win);
extern void on_move_to(GtkAction* act, TcSmartWindow* win);
extern void on_paste(GtkAction* act, TcSmartWindow* win);
extern void on_del(GtkAction* act, TcSmartWindow* win);
extern void on_rename(GtkAction* act, TcSmartWindow* win);
extern void on_create_new(GtkAction* action, TcSmartWindow* win);
extern void on_prop(GtkAction* action, TcSmartWindow* win);

static const char main_menu_xml[] = 
"<menubar>"
  "<menu action='FileMenu'>"
    "<menuitem action='New'/>"
    "<menuitem action='Close'/>"
  "</menu>"
  "<menu action='EditMenu'>"
    "<menuitem action='Cut'/>"
    "<menuitem action='Copy'/>"
    "<menuitem action='Paste'/>"
    "<menuitem action='Del'/>"
    "<separator/>"
    "<menuitem action='Rename'/>"
    "<menuitem action='Link'/>"
    "<menuitem action='MoveTo'/>"
    "<menuitem action='CopyTo'/>"
    "<separator/>"
    "<menuitem action='SelAll'/>"
    "<menuitem action='InvSel'/>"
    "<separator/>"
    "<menuitem action='Pref'/>"
  "</menu>"
  "<menu action='GoMenu'>"
    "<menuitem action='Prev'/>"
    "<menuitem action='Next'/>"
    "<menuitem action='Up'/>"
    "<separator/>"
    "<menuitem action='Home'/>"
    "<menuitem action='Desktop'/>"
    "<menuitem action='Computer'/>"
    "<menuitem action='Trash'/>"
    "<menuitem action='Network'/>"
    "<menuitem action='Apps'/>"
  "</menu>"
  "<menu action='BookmarksMenu'>"
    "<menuitem action='AddBookmark'/>"
  "</menu>"
  "<menu action='ViewMenu'>"
    "<menuitem action='ShowHidden'/>"
    "<separator/>"
    "<menuitem action='IconView'/>"
    "<menuitem action='CompactView'/>"
    "<menuitem action='ThumbnailView'/>"
    "<menuitem action='ListView'/>"
    "<separator/>"
    "<menu action='Sort'>"
      "<menuitem action='Desc'/>"
      "<menuitem action='Asc'/>"
      "<separator/>"
      "<menuitem action='ByName'/>"
      "<menuitem action='ByMTime'/>"
    "</menu>"
  "</menu>"
  "<menu action='HelpMenu'>"
    "<menuitem action='About'/>"
  "</menu>"
"</menubar>"
"<toolbar>"
    "<toolitem action='New'/>"
    "<toolitem action='Prev'/>"
    "<toolitem action='Up'/>"
    "<toolitem action='Home'/>"
    "<toolitem action='Go'/>"
"</toolbar>"
"<popup>"
  "<menu action='CreateNew'>"
    "<menuitem action='NewFolder'/>"
    "<menuitem action='NewBlank'/>"
  "</menu>"
  "<separator/>"
  "<menuitem action='Paste'/>"
  "<menu action='Sort'>"
    "<menuitem action='Desc'/>"
    "<menuitem action='Asc'/>"
    "<separator/>"
    "<menuitem action='ByName'/>"
    "<menuitem action='ByMTime'/>"
  "</menu>"
  "<menuitem action='ShowHidden'/>"
  "<separator/>"
  "<menuitem action='Prop'/>"
"</popup>"
"<accelerator action='Location'/>"
"<accelerator action='Location2'/>";

static GtkActionEntry main_win_actions[]=
{

    {"FileMenu", NULL, N_("_File"), NULL, NULL, NULL},
        {"New", GTK_STOCK_NEW, N_("_New Window"), "<Ctrl>N", NULL, G_CALLBACK(on_new_win)},
        {"Close", GTK_STOCK_CLOSE, N_("_Close Window"), "<Ctrl>W", NULL, G_CALLBACK(on_close_win)},
    {"EditMenu", NULL, N_("_Edit"), NULL, NULL, NULL},
        {"Cut", GTK_STOCK_CUT, NULL, NULL, NULL, G_CALLBACK(on_cut)},
        {"Copy", GTK_STOCK_COPY, NULL, NULL, NULL, G_CALLBACK(on_copy)},
        {"Paste", GTK_STOCK_PASTE, NULL, NULL, NULL, G_CALLBACK(on_paste)},
        {"Del", GTK_STOCK_DELETE, NULL, NULL, NULL, G_CALLBACK(on_del)},
        {"Rename", NULL, N_("Rename"), "F2", NULL, G_CALLBACK(on_rename)},
        {"Link", NULL, NULL, NULL, NULL, NULL},
        {"MoveTo", NULL, N_("Move To..."), NULL, NULL, G_CALLBACK(on_move_to)},
        {"CopyTo", NULL, N_("Copy To..."), NULL, NULL, G_CALLBACK(on_copy_to)},
        {"SelAll", GTK_STOCK_SELECT_ALL, NULL, NULL, NULL, G_CALLBACK(on_select_all)},
        {"InvSel", NULL, N_("Invert Selection"), NULL, NULL, G_CALLBACK(on_invert_select)},
        {"Pref", GTK_STOCK_PREFERENCES, NULL, NULL, NULL, NULL},
    {"ViewMenu", NULL, N_("_View"), NULL, NULL, NULL},
        {"Sort", NULL, N_("_Sort Files"), NULL, NULL, NULL},
    {"HelpMenu", NULL, N_("_Help"), NULL, NULL, NULL},
    {"GoMenu", NULL, N_("_Go"), NULL, NULL, NULL},
        {"Home", NULL, NULL, NULL, NULL, NULL},
        {"Computer", NULL, NULL, NULL, NULL, NULL},
        {"Desktop", NULL, NULL, NULL, NULL, NULL},
        {"Trash", NULL, NULL, NULL, NULL, NULL},
        {"Apps", NULL, NULL, NULL, NULL, NULL},
        {"About", NULL, NULL, NULL, NULL, NULL},
        {"Prev", GTK_STOCK_GO_BACK, N_("Previous Folder"), "<Alt>Left", N_("Previous Folder"), G_CALLBACK(on_go_back)},
        {"Next", GTK_STOCK_GO_FORWARD, N_("Next Folder"), "<Alt>Right", N_("Next Folder"), G_CALLBACK(on_go_forward)},
        {"Up", NULL, NULL, NULL, NULL, NULL},
        {"Network", NULL, NULL, "<Alt>N", NULL, G_CALLBACK(on_go_network)},
        {"Go", NULL, NULL, NULL, NULL, NULL},
    {"BookmarksMenu", NULL, NULL, NULL, NULL, NULL},
        {"AddBookmark", NULL, NULL, NULL, NULL, NULL},
    /* for accelerators */
    {"Location", NULL, NULL, NULL, NULL, NULL},
    {"Location2", NULL, NULL, NULL, NULL, NULL},
    /* for popup menu */
    {"CreateNew", NULL, NULL, NULL, NULL, NULL},
    {"NewFolder", "folder", N_("Folder"), NULL, NULL, G_CALLBACK(on_create_new)},
    {"NewBlank", "text-x-generic", N_("Blank FIle"), NULL, NULL, G_CALLBACK(on_create_new)},
    {"Prop", NULL, NULL, NULL, NULL, NULL}
};

static GtkToggleActionEntry main_win_toggle_actions[]=
{
    {"ShowHidden", NULL, N_("Show _Hidden"), "<Ctrl>H", NULL, G_CALLBACK(on_show_hidden), FALSE}
};

static GtkRadioActionEntry main_win_mode_actions[]=
{
    {"IconView", NULL, N_("_Icon View"), NULL, NULL, FM_FV_ICON_VIEW},
    {"CompactView", NULL, N_("_Compact View"), NULL, NULL, FM_FV_COMPACT_VIEW},
    {"ThumbnailView", NULL, N_("Thumbnail View"), NULL, NULL, FM_FV_THUMBNAIL_VIEW},
    {"ListView", NULL, N_("Detailed _List View"), NULL, NULL, FM_FV_LIST_VIEW},
};

static GtkRadioActionEntry main_win_sort_type_actions[]=
{
    {"Asc", GTK_STOCK_SORT_ASCENDING, NULL, NULL, NULL, GTK_SORT_ASCENDING},
    {"Desc", GTK_STOCK_SORT_DESCENDING, NULL, NULL, NULL, GTK_SORT_DESCENDING},
};

static GtkRadioActionEntry main_win_sort_by_actions[]=
{
    {"ByName", NULL, N_("By _Name"), NULL, NULL, COL_FILE_NAME},
    {"ByMTime", NULL, N_("By _Modification Time"), NULL, NULL, COL_FILE_MTIME}
};


static const char folder_menu_xml[]=
"<popup>"
  "<placeholder name='ph1'>"
    /* "<menuitem action='NewTab'/>" */
    "<menuitem action='NewWin'/>"
    /* "<menuitem action='Search'/>" */
  "</placeholder>"
"</popup>";

#endif

