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
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "config.h"

#define DEFAULT_CONFIG "/usr/local/tc-smart/system.xml"
#define APP_NAME       "FileManager"

static xmlDoc *doc = 0;
static xmlNode *rootElement = 0;

void  
Config_Initialize()
{
  LIBXML_TEST_VERSION

  doc = xmlReadFile(DEFAULT_CONFIG, NULL, 0);
  if (doc == 0)
  {
    fprintf(stderr, "Unable to read the configuration (%s)!\n", DEFAULT_CONFIG);
    fflush(stderr);
    return;
  }

  rootElement = xmlDocGetRootElement(doc);

  xmlNode * n = 0;
  xmlNode * found = 0;
  for (n = rootElement; n != 0; n = n->next)
  {
    if (n->type == XML_ELEMENT_NODE)
    {
      if (strcmp(n->name, APP_NAME) == 0)
      {
        found = n;
        break;
      }
    }
  }

  if (!found)
  {
    rootElement = 0;
  }
  else
  {
    rootElement = found;
  }
}

void  
Config_Destroy()
{
  xmlFreeDoc(doc);
  xmlCleanupParser();

  doc = 0;
  rootElement = 0;
}

char *
_Find(xmlNode* node, char* name)
{
  xmlNode *n = NULL;

  for (n = node; n; n = n->next) 
  {
    if (n->type == XML_ELEMENT_NODE) 
    {
      if (strcmp(n->name, name) == 0)
      {
        xmlAttr *attr = n->properties;
        while (attr)
        {
          if (strcmp(attr->name, "value") == 0)
          {
            return attr->children->content;
          }
          attr = attr->next;
        }
      }
    }

    char * txt = _Find(n->children, name);
    if (txt) return txt;
  }
  return 0;
}

char* 
Config_Get(char* name)
{
  if (rootElement == 0 || name == 0)
  {
    return 0;
  }

  return _Find(rootElement, name);
}

