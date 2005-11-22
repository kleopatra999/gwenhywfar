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

#ifndef GWEN_NET2_H
#define GWEN_NET2_H


#include <gwenhywfar/netlayer.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @name Special Timeout Values
 *
 * These special timeout values can be used whenever a timeout parameter
 * is expected.
 * Positive timeout values specify a limit for the number of seconds to wait.
 */
/*@{*/
/** don't wait at all */
#define GWEN_NET2_TIMEOUT_NONE    (0)
/** wait forever */
#define GWEN_NET2_TIMEOUT_FOREVER (-1)
/*@}*/


GWENHYWFAR_API
void GWEN_Net_AddConnectionToPool(GWEN_NETLAYER *nl);

GWENHYWFAR_API
void GWEN_Net_DelConnectionFromPool(GWEN_NETLAYER *nl);

/**
 * @param timeout timeout in milliseconds (or a special timeout value, see
 * @ref GWEN_NETCONNECTION_TIMEOUT_NONE)
 */

GWENHYWFAR_API
GWEN_NETLAYER_RESULT GWEN_Net_HeartBeat(int timeout);


GWENHYWFAR_API
int GWEN_Net_HasActiveConnections();

GWENHYWFAR_API
int GWEN_Net_HasListeningConnections();


GWENHYWFAR_API
int GWEN_Net_GetIsWorkDebugMode();

#ifdef __cplusplus
}
#endif


#endif /* GWEN_NET_H */

