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

#include <unistd.h>
#include <net/Net.h>
#include <StreamingManager.h>
#include <Main.h>

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

  sai::net::Net::GetInstance()->mainLoop();
  return true;
}

//=============================================================================

MainWindow::MainWindow(const wxString& title):
  wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 500)),
  _mgr(0),
  _drop(0),
  _menu(0),
  _mainPanel(0),
  _position(0)
{
  _mgr = new StreamingManager();

  _drop = new TextDrop(this);
  SetDropTarget(_drop);

  _menu = new Menu();
  SetMenuBar(_menu);
  Connect(wxID_EXIT,  wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnQuit));
  Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnAbout));
  Connect(wxID_OPEN,  wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnOpen));

  CreateStatusBar();    
  SetStatusText(wxT("Ready"));

  wxColour c1(0xcc, 0x44, 0x00, 0x50);

  _mainPanel = new wxPanel(this, -1);
  _mainPanel->SetBackgroundColour(c1);

  wxBoxSizer *vbox  = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

  hbox1->Add(new wxPanel(_mainPanel, wxID_ANY), 0, 0, 0);

  _position = new wxSlider(_mainPanel, wxID_ANY, 0, 0, 10000); 

  wxButton * play   = new wxButton(_mainPanel, -1, wxT("Play"));
  wxButton * stop   = new wxButton(_mainPanel, -1, wxT("Stop"));

  hbox2->Add(_position, 8, 0, 0);
  hbox2->Add(stop, 0, 0, 0);
  hbox2->Add(play, 0, 0, 0);

  vbox->Add(hbox1, 1, wxEXPAND, 0);
  vbox->Add(hbox2, 0, wxEXPAND, 0);
  _mainPanel->SetSizer(vbox);

  Center();
}

MainWindow::~MainWindow()
{
  delete _mgr;
}

void 
MainWindow::OnQuit(wxCommandEvent& event)
{
  Close(true);
}

void 
MainWindow::OnAbout(wxCommandEvent& event)
{
  wxMessageDialog * dialog = new wxMessageDialog(NULL, wxT("tc-smart\nBy Athip"), wxT("About"), wxOK | wxICON_INFORMATION);
  dialog->ShowModal();
}

void 
MainWindow::OnOpen(wxCommandEvent& event)
{
  wxFileDialog * dialog = new wxFileDialog(this);

  if (dialog->ShowModal() == wxID_OK)
  {
    wxString fileName = dialog->GetPath();

    if (access(fileName.c_str(), R_OK) == 0)
    {
      SetStatusText(fileName);
      //std::string name = std::string(fileName.mb_str());
      //_mgr->start(name);
    }
  }
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

