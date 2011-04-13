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

#include <StreamingManager.h>
#include <Main.h>

//=============================================================================

class TcsVdoServer : public wxApp
{
public:
  virtual bool OnInit();
};

IMPLEMENT_APP(TcsVdoServer)

bool
TcsVdoServer::OnInit()
{
  MainWindow * window = new MainWindow(wxT("tc-smart"));
  window->Show(true);

  return true;
}

//=============================================================================
enum
{
  BUTTON_PLAYPAUSE = wxID_HIGHEST + 1,
  BUTTON_STOP      = wxID_HIGHEST + 2
};


MainWindow * MainWindow::_instance = 0;

MainWindow::MainWindow(const wxString& title):
  wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 500)),
  _drop(0),
  _menu(0),
  _mainPanel(0),
  _position(0)
{
  StreamingManager* mgr = StreamingManager::GetInstance();
  _instance = this;
  _drop = new TextDrop(this);
  SetDropTarget(_drop);

  _menu = new Menu();
  SetMenuBar(_menu);
  Connect(wxID_EXIT,  wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::onQuit));
  Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::onAbout));
  Connect(wxID_OPEN,  wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::onOpen));
  Connect(BUTTON_PLAYPAUSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::onPlayPause));
  Connect(BUTTON_STOP,      wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::onStop));

  CreateStatusBar();    
  SetStatusText(wxT("Ready"));

  wxColour c1(0x00, 0xFF, 0x00, 0x00);
  wxColour c2(0xcc, 0x44, 0x00, 0x50);  

  wxBoxSizer *vbox  = new wxBoxSizer(wxVERTICAL);
  wxPanel * mn = new wxPanel(this, wxID_ANY);

  _mainPanel   = new wxPanel(mn, wxID_ANY);
  wxPanel * pL = new wxPanel(mn, wxID_ANY);

  mn->SetBackgroundColour(c1);
  _mainPanel->SetBackgroundColour(c2);
  pL->SetBackgroundColour(c2);

  vbox->Add(_mainPanel, 25, wxEXPAND);
  vbox->Add(pL,          1, wxEXPAND);

  _position  = new wxSlider(pL, wxID_ANY, 0, 0, 100);
  _stop      = new wxButton(pL, BUTTON_STOP,      "Stop");
  _playPause = new wxButton(pL, BUTTON_PLAYPAUSE, "Play");
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
  hbox->Add(_position, 10, 0);
  hbox->Add(_stop,      1, 0);
  hbox->Add(_playPause, 1, 0);

  pL->SetSizer(hbox);
  mn->SetSizer(vbox);

  Center();
}

MainWindow::~MainWindow()
{
  StreamingManager * mgr = StreamingManager::GetInstance();
  delete mgr;
}

void 
MainWindow::onQuit(wxCommandEvent& event)
{
  Close(true);
}

void 
MainWindow::onAbout(wxCommandEvent& event)
{
  wxMessageDialog * dialog = new wxMessageDialog(NULL, wxT("tc-smart\nBy Athip"), wxT("About"), wxOK | wxICON_INFORMATION);
  dialog->ShowModal();
}

void 
MainWindow::onOpen(wxCommandEvent& event)
{
  wxFileDialog dialog(this);

  if (dialog.ShowModal() == wxID_OK)
  {
    wxString fileName(dialog.GetPath());

	const int SIZE = 2048;
	wchar_t * wbuff = new wchar_t[2048];
	memset(wbuff, 0, sizeof(wchar_t) * SIZE);

	const wchar_t* ptr = fileName.wc_str();
	memcpy(wbuff, ptr, fileName.length() * sizeof(wchar_t));

	char * tmp = new char[SIZE];
	for (int i = 0; i < 1024; i += 1)
	{
		tmp[i] = (char)wbuff[i];
	}

    SetStatusText(fileName);
    StreamingManager* mgr = StreamingManager::GetInstance();
    mgr->start(tmp);

	delete [] tmp;
	delete [] wbuff;
  }  
}

void 
MainWindow::onPlayPause(wxCommandEvent& event)
{
  if (_playPause->GetLabelText().compare("Play") == 0)
  {
    _playPause->SetLabelText(wxT("Pause"));
	StreamingManager::GetInstance()->play();
  }
  else
  {
    _playPause->SetLabelText(wxT("Play"));
	StreamingManager::GetInstance()->pause();
  }
}

void 
MainWindow::onStop(wxCommandEvent& event)
{
  StreamingManager::GetInstance()->stop();
}

void * 
MainWindow::getMainPanelHandle()
{
  return _mainPanel->GetHandle();
}

void
MainWindow::setStreamPosition(int pos, int tot)
{
  int val = (100 * pos) / tot;
  _position->SetValue(val);
}

MainWindow::TextDrop::TextDrop(MainWindow *win):
  _window(win)
{
}

MainWindow::TextDrop::~TextDrop()
{
}

bool 
MainWindow::TextDrop::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
  //SetStatusText(data);
  return true;
}

MainWindow::Menu::Menu():
  _file(0),
  _help(0)
{
  _file = new wxMenu();
  _help = new wxMenu();

  _file->Append(wxID_OPEN, wxT("&Open"));
  _file->Append(wxID_EXIT, wxT("&Quit"));
  _help->Append(wxID_ABOUT, wxT("&About"));

  this->Append(_file, wxT("&File"));
  this->Append(_help, wxT("&Help"));
}

MainWindow::Menu::~Menu()
{
}

