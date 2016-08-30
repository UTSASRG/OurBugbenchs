
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

#include "log.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>

/* =========== GLOBALS ===================================================== */

static logLevel_t
verbose = LOG_BASIC;

static FILE*
fd = NULL;

static pthread_mutex_t
logMutex = PTHREAD_MUTEX_INITIALIZER;

/* =========== PRIVATE PROTOTYPES ========================================== */

/* =========== PUBLIC FUNCTIONS ============================================ */

baseError_t
log_init(
      const char* logfile,
      logLevel_t logLevel
      )
{
   baseError_t err = BASE_ERR_OK;

   fd = fopen(logfile, "a");
   if (fd == NULL) {
      fprintf(stderr, " error open/create log file: %s\n", logfile);
      err = BASE_ERR_DATA;
   } else {
      verbose = logLevel;
   }

   return err;
}


void
log_clean(
      void
      )
{
   if (fd)
      fclose(fd);
}


void
log_error(
      baseError_t err,
      const char* formatStr,
      ...
      )
{
   va_list arg;

   if (fd) {
      va_start(arg, formatStr);
      vfprintf(fd, formatStr, arg);
      va_end(arg);
   }

   va_start(arg, formatStr);
   vprintf(formatStr, arg);
   va_end(arg);
}


void
log_errorMutexed(
      baseError_t err,
      const char* formatStr,
      ...
      )
{
   va_list arg;

   pthread_mutex_lock(&logMutex);

   if (fd) {
      va_start(arg, formatStr);
      vfprintf(fd, formatStr, arg);
      va_end(arg);
   }

   va_start(arg, formatStr);
   vprintf(formatStr, arg);
   va_end(arg);

   pthread_mutex_unlock(&logMutex);
}


void
log_printOut(
      logLevel_t level,
      const char* formatStr,
      ...
      )
{
   if (level <= verbose) {
      va_list arg;

      va_start(arg, formatStr);
      vprintf(formatStr, arg);
      va_end(arg);
   }
}


void
log_printOutMutexed(
      logLevel_t level,
      const char* formatStr,
      ...
      )
{
   if (level <= verbose) {
      va_list arg;

      pthread_mutex_lock(&logMutex);

      va_start(arg, formatStr);
      vprintf(formatStr, arg);
      va_end(arg);

      pthread_mutex_unlock(&logMutex);
   }
}


void
log_info(
      logLevel_t level,
      const char* formatStr,
      ...
      )
{
   if (level <= verbose) {
      va_list arg;

      if (fd) {
         va_start(arg, formatStr);
         vfprintf(fd, formatStr, arg);
         va_end(arg);
      }

      va_start(arg, formatStr);
      vprintf(formatStr, arg);
      va_end(arg);
   }
}


void
log_infoMutexed(
      logLevel_t level,
      const char* formatStr,
      ...
      )
{
   if (level <= verbose) {
      va_list arg;

      pthread_mutex_lock(&logMutex);

      if (fd) {
         va_start(arg, formatStr);
         vfprintf(fd, formatStr, arg);
         va_end(arg);
      }

      va_start(arg, formatStr);
      vprintf(formatStr, arg);
      va_end(arg);

      pthread_mutex_unlock(&logMutex);
   }
}


#ifdef DEBUG
void
log_debug(
      const char* formatStr,
      ...
      )
{
      va_list arg;

      va_start(arg, formatStr);
      vprintf(formatStr, arg);
      va_end(arg);
}


void
log_debugMutexed(
      const char* formatStr,
      ...
      )
{
      va_list arg;

      pthread_mutex_lock(&logMutex);

      va_start(arg, formatStr);
      vprintf(formatStr, arg);
      va_end(arg);

      pthread_mutex_unlock(&logMutex);
}
#endif

/* ========================== END OF FILE ================================== */

/*
 * vim settings, please do not remove!
 * vim:autoindent:
 * vim:ts=3:sw=3:sts=3:expandtab:cindent:tw=75:formatoptions=croql:
 * vim600:foldmethod=syntax:
 */
