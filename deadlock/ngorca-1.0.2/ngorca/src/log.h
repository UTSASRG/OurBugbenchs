
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


#ifndef __LOG_H__
#define __LOG_H__


/* =========== INCLUDES ==================================================== */

#include "base_types.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* =========== DEFINES ===================================================== */

/* removes the debug function calls if DEBUG is not set */
#ifndef DEBUG
#define log_debug(formatStr, ...)
#define log_debugMutexed(formatStr, ...)
#endif

/* =========== DATA TYPES ================================================== */

/*
 * log level enumeration
 * for setting the loglevel
 */
typedef enum {
   LOG_BASIC = 1,
   LOG_INFO,
   LOG_FINE,
   LOG_FINEST
} logLevel_t;

/* =========== PUBLIC PROTOTYPES =========================================== */

/*---------------------------------------------------------------------------*/
/*
 * initialisation of logging
 * open logfile, must be closed by log_clean call
 *
 * @param logfile          in : file name of loggingfile
 * @param loglevel         in : level of logging
 * @return baseError_t     RET_OK for success or BASE_ERR_DATA
 */
baseError_t
log_init(
      const char* logfile,
      logLevel_t logLevel
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * close the logging file
 */
void
log_clean(
      void
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * error logging
 * write on standard output and loggingfile
 * no loglevel is needed
 *
 * @param err              in : error type (not used atm)
 * @param formatStr        in : format string
 */
void
log_error(
      baseError_t err,
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * TODO depends on platform if this is needed
 * mutexed error logging
 * write on standard output and loggingfile
 * no loglevel is needed
 *
 * @param err              in : error type (not used atm)
 * @param formatStr        in : format string
 */
void
log_errorMutexed(
      baseError_t,
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * stdout printer logger
 * writes only on standard output
 * if param log level is equal or less than the privat log level
 *
 * @param level            in : log level for this log
 * @param formatStr        in : format string
 */
void
log_printOut(
      logLevel_t level,
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * TODO depends on platform if this is needed
 * mutexed stdout printer logger
 * writes only on standard output
 * if param log level is equal or less than the privat log level
 *
 * @param level            in : log level for this log
 * @param formatStr        in : format string
 */
void
log_printOutMutexed(
      logLevel_t level,
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * info logger
 * write on standard output and loggingfile
 * if param log level is equal or less than the privat log level
 *
 * @param level            in : log level for this log
 * @param formatStr        in : format string
 */
void
log_info(
      logLevel_t level,
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * TODO depends on platform if this is needed
 * mutexed info logger
 * write on standard output and loggingfile
 * if param log level is equal or less than the privat log level
 *
 * @param level            in : log level for this log
 * @param formatStr        in : format string
 */
void
log_infoMutexed(
      logLevel_t level,
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/

#ifdef DEBUG
/*---------------------------------------------------------------------------*/
/*
 * debug logger
 * writes only on standard output
 *
 * @param formatStr        in : format string
 */
void
log_debug(
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * TODO depends on platform if this is needed
 * debug logger
 * writes only on standard output
 *
 * @param formatStr        in : format string
 */
void
log_debugMutexed(
      const char* formatStr,
      ...
      );
/*---------------------------------------------------------------------------*/
#endif /* ifdef DEBUG */

#endif
/* ========================== END OF FILE ================================== */

/*
 * vim settings, please do not remove!
 * vim:autoindent:filetype=c:syntax=c:
 * vim:ts=3:sw=3:sts=3:expandtab:cindent:tw=75:formatoptions=croql:
 * vim600:foldmethod=syntax:
 */

