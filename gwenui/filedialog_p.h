/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Mon Feb 09 2004
    copyright   : (C) 2004 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GWEN_UI_FILEDIALOG_P_H
#define GWEN_UI_FILEDIALOG_P_H

#include <gwenhywfar/misc.h>
#include <gwenhywfar/inherit.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/ui/widget.h>
#include <gwenhywfar/ui/filedialog.h>


typedef struct GWEN_FILEDIALOG GWEN_FILEDIALOG;
struct GWEN_FILEDIALOG {
  GWEN_WIDGET_EVENTHANDLER_FN previousHandler;

  GWEN_TYPE_UINT32 flags;
  GWEN_WIDGET *wTable;
  GWEN_WIDGET *wSelected;
  GWEN_WIDGET *wPatterns;
  int entries;
  char *currentDir;
  char *startDir;
  GWEN_DB_NODE *files;
};
void GWEN_FileDialog_freeData(void *bp, void *p);



GWEN_UI_RESULT GWEN_FileDialog_EventHandler(GWEN_WIDGET *w, GWEN_EVENT *e);
int GWEN_FileDialog_ScanDir(GWEN_WIDGET *w, const char *s, GWEN_DB_NODE *db);
int GWEN_FileDialog_Files2Table(GWEN_WIDGET *w, GWEN_DB_NODE *db);
int GWEN_FileDialog_Update(GWEN_WIDGET *w);
int GWEN_FileDialog_Run(GWEN_WIDGET *w);



#endif




