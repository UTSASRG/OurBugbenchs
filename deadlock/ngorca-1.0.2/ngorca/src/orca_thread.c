
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


/* =========== INCLUDES ==================================================== */

#include "orca_thread.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ngorca.h"
#include "log.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* =========== GLOBALS ===================================================== */

static pthread_mutex_t
countMutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t
conditionMutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t
conditionCond = PTHREAD_COND_INITIALIZER;

static int
percInfo = 0;

static baseBool_t
terminate = BASE_FALSE;


/* =========== PRIVATE PROTOTYPES ========================================== */

/*
 * calculates the case sensitive password if 11g is used
 */
static baseError_t
searchCaseSensPasswd(
      hash_t* hash,
      char* const passwd
      );


/* =========== PUBLIC FUNCTIONS ============================================ */

void*
thr_run(
      void* argum
      )
{
   threadArg_t* arg = (threadArg_t*)argum;
   unsigned long long int pwd = arg->th[arg->id].sPwd;
   unsigned long long int maxpwd = arg->th[arg->id].ePwd;
   unsigned long long int tmp = 0;
   char password[MAX_PASSLENGTH] = {0};
   unsigned char currentHash[HASH_LEN] = {0};
   unsigned long long int startPerc = pwd;
   unsigned long long int perc = (maxpwd - pwd) / 100;

   log_debugMutexed("start thread %x\n", arg->th[arg->id].tid);

   while (pwd <= maxpwd) {
      tmp = pwd;

      orc_getPassword(password, tmp);
      orc_generateDESHash(arg->th[arg->id].hash, password, currentHash);

      if (orc_compareHash(arg->th[arg->id].hash->desHash, currentHash,
               HASH_LEN) == BASE_TRUE) {
         arg->th[arg->id].hash->found = BASE_TRUE;

         if (arg->th[arg->id].hash->shaHash[0]) {
            searchCaseSensPasswd(arg->th[arg->id].hash, password);
         }

         terminate = BASE_TRUE;

         pthread_mutex_lock(&conditionMutex);
         pthread_cond_signal(&conditionCond);
         pthread_mutex_unlock(&conditionMutex);

         log_infoMutexed(LOG_FINEST, "\n\n");
         log_infoMutexed(LOG_BASIC, " found pwd --- beer!\n");
         orc_printResult(arg->th[arg->id].hash, password);
      }

      if (terminate) {
         return NULL;
      }

      if (arg->percPrint && ((pwd - startPerc) % perc) == 0) {
         pthread_mutex_lock(&conditionMutex);
         pthread_mutex_lock(&countMutex);
         percInfo++;
         pthread_mutex_unlock(&countMutex);
         pthread_cond_signal(&conditionCond);
         pthread_mutex_unlock(&conditionMutex);
      }
      pwd++;
   }
   return NULL;
}


void*
thr_percentPrint(
      void* argum
      )
{
   int percent = 0;
   percThreadArg_t* arg = (percThreadArg_t*)argum;

   while(percent < 101) {
      pthread_mutex_lock(&conditionMutex);
      pthread_cond_wait(&conditionCond, &conditionMutex);
      pthread_mutex_unlock(&conditionMutex);

      if (terminate) {
         return NULL;
      }

      if (percInfo == arg->threadCount) {
         log_printOutMutexed(LOG_FINEST, "\r [passlength=%d] status %3d %% ",arg->passLen, percent);
         fflush(stdout);

         pthread_mutex_lock(&countMutex);
         percInfo = 0;
         pthread_mutex_unlock(&countMutex);
         percent += 1;
      }
   }

   return NULL;
}


void
thr_setThreadsRun(
      void
      )
{
   terminate = BASE_FALSE;
}


void
thr_terminatePercThr(
      void
      )
{
   if (!terminate) {
      terminate = BASE_TRUE;
      pthread_mutex_lock(&conditionMutex);
      pthread_cond_signal(&conditionCond);
      pthread_mutex_unlock(&conditionMutex);
   }
}


/* =========== PRIVATE FUNCTIONS =========================================== */


static baseError_t
searchCaseSensPasswd(
      hash_t* hash,
      char* const passwd
      )
{
   baseError_t err = BASE_ERR_OK;
   int maxpwd = 1;
   char* pwdsalt = NULL;
   char password[MAX_PASSLENGTH] = {0};
   unsigned char currentHash[SHA_DIGEST_LENGTH] = {0};
   int passLen = hsh_getPassLength();
   int i;

   memcpy(password, passwd, passLen);

   pwdsalt = malloc(passLen + SHA_SALT_LEN);
   if (pwdsalt == NULL) {
      log_error(err, " error while allocating memory\n");
      return BASE_ERR_MEM;
   }

   memcpy(pwdsalt + passLen, hash->shaSalt, SHA_SALT_LEN);

   for (i=0; i<passLen; i++) {
      maxpwd *= 2;
   }

   for (i=0; i<maxpwd; i++) {
      orc_getCaseSensPassword(password, i);
      memcpy(pwdsalt, password, passLen);
      err = orc_generateSHAHash(pwdsalt, currentHash);
      if (orc_compareHash(hash->shaHash, currentHash, SHA_DIGEST_LENGTH)
            == BASE_TRUE) {
         memcpy(passwd, password, passLen);
         break;
      }
   }

   if (pwdsalt)
      free(pwdsalt);

   return err;
}


/* ========================== END OF FILE ================================== */

/*
 * vim settings, please do not remove!
 * vim:autoindent:
 * vim:ts=3:sw=3:sts=3:expandtab:cindent:tw=75:formatoptions=croql:
 * vim600:foldmethod=syntax:
 */
