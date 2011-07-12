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

#include <stdio.h>
#include <cstring>

#include "Cmd.h"

Cmd::Cmd()
{
}

Cmd::~Cmd()
{
}

std::string
Cmd::execute(std::string cmd)
{
  static std::string result = "";
  result.clear();
#ifdef _WIN32
  FILE * fp = _popen(cmd.c_str(), "r");
#else
  FILE * fp = popen(cmd.c_str(), "r");
#endif
  if (fp)
  {
    char tmp[256] = {0};
    while(!feof(fp))
    {
      size_t bytes = fread(tmp, 1, sizeof(tmp)-1, fp);
      if (bytes > 0)
      {
        result.append(tmp);
      }
      memset(tmp, 0, sizeof(tmp));
    }
#ifdef _WIN32
    _pclose(fp);
#else
    pclose(fp);
#endif
  }
  if (result.length() > 0 && result.at(result.length() - 1) == '\n')
  {
    result = result.substr(0, result.length() - 1);
  }
  return result;
}

