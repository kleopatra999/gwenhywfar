/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Tue Sep 16 2003
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


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "ipc_p.h"
#include <gwenhywfar/debug.h>
#include <gwenhywfar/error.h>




static int gwen_ipc_is_initialized=0;
static GWEN_ERRORTYPEREGISTRATIONFORM *gwen_ipc_errorform=0;



/* --------------------------------------------------------------- FUNCTION */
const char *GWEN_IPC_ErrorString(int c){
  const char *s;

  switch(c) {
  case GWEN_IPC_ERROR_INQUEUE_FULL:
    s="Incoming message queue full";
    break;
  case GWEN_IPC_ERROR_OUTQUEUE_FULL:
    s="Outgoing message queue full";
    break;
  case GWEN_IPC_ERROR_BAD_STATE:
    s="Bad state";
    break;
  case GWEN_IPC_ERROR_NO_CONNECTIONS:
    s="No connections";
    break;
  case GWEN_IPC_ERROR_CONNECTION_NOT_FOUND:
    s="Connection not found";
    break;
  case GWEN_IPC_ERROR_XMLFILE:
    s="Error loading XML file";
    break;
  case GWEN_IPC_ERROR_SEG_NOT_FOUND:
    s="Segment not found";
    break;
  case GWEN_IPC_ERROR_BAD_MSG:
    s="Bad message";
    break;
  case GWEN_IPC_ERROR_HANDSHAKING:
    s="Error in handshaking";
    break;
  case GWEN_IPC_ERROR_UNKNOWN_MSG:
    s="Unknown message";
    break;
  case GWEN_IPC_ERROR_INVALID:
    s="Invalid argument";
    break;
  case GWEN_IPC_ERROR_GENERIC:
    s="Generic error";
    break;
  case GWEN_IPC_ERROR_INQUEUE_EMPTY:
    s="Input queue empty";
    break;
  case GWEN_IPC_ERROR_SOME_FAILED:
    s="Some messages had errors";
    break;
  case GWEN_IPC_ERROR_REQUEST_NOT_FOUND:
    s="Request not found";
    break;
  default:
    s=0;
  } /* switch */

  return s;
}



/* --------------------------------------------------------------- FUNCTION */
GWEN_ERRORCODE GWEN_IPC_ModuleInit(){
  if (!gwen_ipc_is_initialized) {
    GWEN_ERRORCODE err;

    gwen_ipc_errorform=GWEN_ErrorType_new();
    GWEN_ErrorType_SetName(gwen_ipc_errorform,
                           GWEN_IPC_ERROR_TYPE);
    GWEN_ErrorType_SetMsgPtr(gwen_ipc_errorform,
                             GWEN_IPC_ErrorString);
    err=GWEN_Error_RegisterType(gwen_ipc_errorform);
    if (!GWEN_Error_IsOk(err))
      return err;
    gwen_ipc_is_initialized=1;
  }
  return 0;
}



/* --------------------------------------------------------------- FUNCTION */
GWEN_ERRORCODE GWEN_IPC_ModuleFini(){
  if (gwen_ipc_is_initialized) {
    GWEN_ERRORCODE err;

    err=GWEN_Error_UnregisterType(gwen_ipc_errorform);
    GWEN_ErrorType_free(gwen_ipc_errorform);
    if (!GWEN_Error_IsOk(err))
      return err;
    gwen_ipc_is_initialized=0;
  }
  return 0;
}





