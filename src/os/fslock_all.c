/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Sun Nov 23 2003
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


#include "fslock_p.h"
#include <gwenhywfar/debug.h>
#include <gwenhywfar/inetsocket.h> /* for select */
#include <gwenhywfar/waitcallback.h>
#include <gwenhywfar/gwentime.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>


GWEN_FSLOCK *GWEN_FSLock_new(const char *fname, GWEN_FSLOCK_TYPE t){
  GWEN_FSLOCK *fl;
  GWEN_BUFFER *nbuf;
  const char *s;

  assert(fname);
  GWEN_NEW_OBJECT(GWEN_FSLOCK, fl);
  fl->entryName=strdup(fname);

  switch(t) {
  case GWEN_FSLock_TypeFile: s=".lck"; break;
  case GWEN_FSLock_TypeDir:  s="/.dir.lck"; break;
  default:
    DBG_ERROR(GWEN_LOGDOMAIN, "Unknown log type %d", t);
    abort();
  } /* switch */

  nbuf=GWEN_Buffer_new(0, 256, 0, 1);
  GWEN_Buffer_AppendString(nbuf, fname);
  GWEN_Buffer_AppendString(nbuf, s);
  fl->baseLockFilename=strdup(GWEN_Buffer_GetStart(nbuf));
  GWEN_Buffer_free(nbuf);

  return fl;
}



void GWEN_FSLock_free(GWEN_FSLOCK *fl){
  if (fl) {
    if (fl->lockCount) {
      DBG_WARN(GWEN_LOGDOMAIN,
               "File \"%s\" still locked", fl->entryName);
    }
    free(fl->entryName);
    free(fl->baseLockFilename);
    GWEN_FREE_OBJECT(fl);
  }
}



GWEN_FSLOCK_RESULT GWEN_FSLock__Lock(GWEN_FSLOCK *fl){
  assert(fl);

  if (fl->lockCount==0) {
    int fd;

    fd=open(fl->baseLockFilename, O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
    if (fd==-1) {
      if (errno==EEXIST) {
        return GWEN_FSLock_ResultBusy;
      }
      else {
        DBG_DEBUG(GWEN_LOGDOMAIN,
                  "open(%s): %s",
                  fl->baseLockFilename,
                  strerror(errno));
        return GWEN_FSLock_ResultError;
      }
    }
    DBG_INFO(GWEN_LOGDOMAIN, "FS-Lock applied to %s", fl->entryName);
    close(fd);
  }
  fl->lockCount++;
  return GWEN_FSLock_ResultOk;
}



GWEN_FSLOCK_RESULT GWEN_FSLock_Unlock(GWEN_FSLOCK *fl){
  assert(fl);

  if (fl->lockCount<1) {
    DBG_ERROR(GWEN_LOGDOMAIN,
              "Entry \"%s\" not locked", fl->entryName);
    return GWEN_FSLock_ResultNoLock;
  }
  fl->lockCount--;
  if (fl->lockCount<1) {
    if (remove(fl->baseLockFilename)) {
      DBG_DEBUG(GWEN_LOGDOMAIN,
                "remove(%s): %s",
                fl->baseLockFilename,
                strerror(errno));
      return GWEN_FSLock_ResultError;
    }
    DBG_INFO(GWEN_LOGDOMAIN, "FS-Lock released from %s", fl->entryName);
  }
  return GWEN_FSLock_ResultOk;
}



GWEN_FSLOCK_RESULT GWEN_FSLock_Lock(GWEN_FSLOCK *fl, int timeout){
  GWEN_TIME *t0;
  int distance;
  int count;
  GWEN_FSLOCK_RESULT rv;

  t0=GWEN_CurrentTime();
  assert(t0);

  GWEN_WaitCallback_Enter(GWEN_FSLOCK_CBID_IO);

  if (timeout==GWEN_FSLOCK_TIMEOUT_NONE)
    distance=GWEN_FSLOCK_TIMEOUT_NONE;
  else if (timeout==GWEN_FSLOCK_TIMEOUT_FOREVER)
    distance=GWEN_FSLOCK_TIMEOUT_FOREVER;
  else {
    distance=GWEN_WaitCallback_GetDistance(0);
    if (distance)
      if ((distance)>timeout)
        distance=timeout;
    if (!distance)
      distance=250;
  }

  for (count=0;;count++) {
    if (GWEN_WaitCallback()==GWEN_WaitCallbackResult_Abort) {
      DBG_ERROR(GWEN_LOGDOMAIN, "User aborted via waitcallback");
      GWEN_WaitCallback_Leave();
      return GWEN_FSLock_ResultUserAbort;
    }

    rv=GWEN_FSLock__Lock(fl);
    if (rv==GWEN_FSLock_ResultError) {
      DBG_INFO(GWEN_LOGDOMAIN, "here");
      GWEN_Time_free(t0);
      GWEN_WaitCallback_Leave();
      return rv;
    }
    else if (rv==GWEN_FSLock_ResultOk) {
      GWEN_Time_free(t0);
      GWEN_WaitCallback_Leave();
      return rv;
    }
    else {
      /* check timeout */
      if (timeout!=GWEN_FSLOCK_TIMEOUT_FOREVER) {
        GWEN_TIME *t1;
        double d;

        if (timeout==GWEN_FSLOCK_TIMEOUT_NONE) {
          GWEN_WaitCallback_Leave();
          return GWEN_FSLock_ResultTimeout;
        }
        t1=GWEN_CurrentTime();
        assert(t1);
        d=GWEN_Time_Diff(t1, t0);
        GWEN_Time_free(t1);

        if (d>=timeout) {
          DBG_DEBUG(GWEN_LOGDOMAIN,
                    "Could not lock within %d milliseconds, giving up",
                    timeout);
          GWEN_Time_free(t0);
          GWEN_WaitCallback_Leave();
          return GWEN_FSLock_ResultTimeout;
        }
      }
      /* sleep for the distance of the WaitCallback */
      GWEN_Socket_Select(0, 0, 0, distance);
    }
  } /* for */
  GWEN_WaitCallback_Leave();

  DBG_WARN(GWEN_LOGDOMAIN, "We should never reach this point");
  GWEN_Time_free(t0);
  return GWEN_FSLock_ResultError;





}







