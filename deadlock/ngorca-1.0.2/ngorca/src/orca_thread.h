
/******************************************************************************
 *
 * ngorca - Password Recovery Tool for Oracle Hashes (7-11g Rel.2)
 *
 * Author:        Dennis Krzyzaniak
 * E-mail:        ebrosius@netgarage.org
 * WWW:           http://www.netgarage.org
 * Copyright (C): 2010 by Dennis Krzyzaniak
 *
 * This file is part of ngorca.
 *
 * ngorca is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ngorca is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ngorca.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations including
 * the two. You must obey the GNU General Public License in all
 * respects for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so. If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source files
 * in the program, then also delete it here.
 *
 *****************************************************************************/


#ifndef __ORCA_THREAD_H__
#define __ORCA_THREAD_H__


/* =========== INCLUDES ==================================================== */

#include "hash_data.h"

#include <pthread.h>

/* =========== DATA TYPES ================================================== */

/*
 * thread type
 * holds the start and end password
 * and a pointer to a hash type
 */
typedef struct
{
   pthread_t tid;
   unsigned long long int sPwd;
   unsigned long long int ePwd;
   hash_t* hash;
} thread_t;


/*
 * thread argument struct
 * needed for easy identification of the thread
 */
typedef struct
{
   thread_t* th;
   int id;
   int threadCount;
   baseBool_t percPrint;
} threadArg_t;


/*
 * thread argument struct for the percent thread
 */
typedef struct
{
   int threadCount;
   int passLen;
} percThreadArg_t;

/* =========== PUBLIC PROTOTYPES =========================================== */

/*---------------------------------------------------------------------------*/
/* thread function which every thread is running
 * calculates the passwords
 */
void*
thr_run(
      void* argum
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* thread function for the percent print out thread
 * prints out status
 */
void*
thr_percentPrint(
      void* argum
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* joins the thr_percentPrint running thread if exists.
 * must be called before thr_setThreadsRun call
 */
void
thr_terminatePercThr(
      void
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* set the static terminate status to false.
 * must be called after thr_joinPercentThread call
 */
void
thr_setThreadsRun(
      void
      );
/*---------------------------------------------------------------------------*/

#endif
/* ========================== END OF FILE ================================== */

/*
 * vim settings, please do not remove!
 * vim:autoindent:filetype=c:syntax=c:
 * vim:ts=3:sw=3:sts=3:expandtab:cindent:tw=75:formatoptions=croql:
 * vim600:foldmethod=syntax:
 */

