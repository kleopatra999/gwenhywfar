/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Mon Nov 17 2003
    copyright   : (C) 2003 by Martin Preuss
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


#ifndef GWENHYWFAR_IPCXMLKEYMANAGER_H
#define GWENHYWFAR_IPCXMLKEYMANAGER_H


#include <gwenhywfar/keymanager.h>
#include <gwenhywfar/crypt.h>


GWEN_KEYMANAGER *GWEN_IPCXMLKeyManager_new();

int GWEN_IPCXMLKeyManager_KeysFromDB(GWEN_KEYMANAGER *km,
                                     GWEN_DB_NODE *db);
int GWEN_IPCXMLKeyManager_KeysToDB(GWEN_KEYMANAGER *km,
                                   GWEN_DB_NODE *db);



#endif



