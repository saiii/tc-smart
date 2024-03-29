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

#ifndef __TCSMART_VS_MAIN__
#define __TCSMART_VS_MAIN__

#include <wx/wx.h>
#include <wx/dnd.h>
#include <wx/textdlg.h>

class StreamingManager;
class MainWindow : public wxFrame
{
  private:
    class TextDrop : public wxTextDropTarget
    {
      private:
        MainWindow* _window;

      public: 
        TextDrop(MainWindow *win);
        virtual ~TextDrop();
        bool OnDropText(wxCoord x, wxCoord y, const wxString& data);
    };

    class Menu : public wxMenuBar
    {
      private:
        wxMenu * _file;
        wxMenu * _help;
 
      public:
        Menu();
        virtual ~Menu();
    };

  private:
    static MainWindow * _instance;
    TextDrop*           _drop;
    Menu*               _menu;
    wxPanel*            _mainPanel;
    wxSlider*           _position;
	wxButton*           _playPause;
	wxButton*           _stop;

  public:
    MainWindow(const wxString& title);
    static MainWindow * GetInstance() { return _instance; }
    ~MainWindow();

    void onQuit(wxCommandEvent& event);
    void onAbout(wxCommandEvent& event);
    void onOpen(wxCommandEvent& event);

	void onPlayPause(wxCommandEvent& event);
	void onStop(wxCommandEvent& event);

    void * getMainPanelHandle();
	void   setStreamPosition(int, int);
};

#endif
