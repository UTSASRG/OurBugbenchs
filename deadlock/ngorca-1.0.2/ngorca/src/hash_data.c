
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

#include "hash_data.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "log.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* =========== MODULE CONFIGURATION ======================================== */

/* =========== DEFINES ===================================================== */

/* max line from hashfile */
#define MAX_LINE        123

/* =========== DATA TYPES ================================================== */

/* =========== GLOBALS ===================================================== */

/*
 * charsets
 */
static const char
num_charset[11] = "0123456789";

static const char
al_charset[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char
alnum_charset[37] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

static const char
alnumspecial_charset[67] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:,;-_#'+?="
            "()/&%$§\"!<>|\\}][{~@";

/*
 * length of the password
 */
static int
passwordLength = 8;

/* =========== PRIVATE PROTOTYPES ========================================== */

/*
 * converts a hex to unsigned char
 */
static unsigned char
hexDigit(
      char c
      );


/*
 * converts hexstring to unsigned char
 */
static void
readHex(
      const char* x,
      unsigned char* p
      );


/*
 * parse the file content and fills a hash_t type
 */
static baseBool_t
parseHashList(
      hash_t* const hash,
      const char* const line,
      size_t size
      );


/*
 * getline implementation to avoid gnu extensions
 */
static size_t
_getline(
      char* line,
      size_t max,
      FILE* fd
      );

/* =========== PUBLIC FUNCTIONS ============================================ */

baseError_t
hsh_setPassLength(
      int len
      )
{
   if ((len < 1) || (len > MAX_PASSLENGTH)) {
      return BASE_ERR_LENGTH;
   }
   passwordLength = len;
   return BASE_ERR_OK;
}


int
hsh_getPassLength(
      void
      )
{
   return passwordLength;
}


const char*
hsh_getCharset(
      charSet_t c
      )
{
   const char* set = NULL;

   switch(c) {
      case ALNUM_CHARSET:
         set = alnum_charset;
         break;
      case AL_CHARSET:
         set = al_charset;
         break;
      case NUM_CHARSET:
         set = num_charset;
         break;
      case ALNUM_SPEC_CHARSET:
         set = alnumspecial_charset;
         break;
   }
   return set;
}


baseError_t
hsh_readHashList(
      hash_t** const hashTable,
      int* const hashCount,
      const char* const file
      )
{
   baseError_t err = BASE_ERR_OK;
   char line[MAX_LINE] = { 0 };
   size_t maxLen = MAX_LINE;
   FILE* fd = NULL;
   void* ptr = NULL;
   size_t size = 0;
   hash_t tmp;

   *hashCount = 0;
   fd = fopen(file, "r");

   memset(&tmp, 0, sizeof(hash_t));

   if (fd) {
      while(1) {
         memset(line, 0, maxLen);
         size = _getline(line, maxLen, fd);
         if (size != -1) {
            line[size - 1] = 0;
            if (parseHashList(&tmp, line, size) == BASE_FALSE) {
               log_info(LOG_INFO, " wrong file format in hash file %s\n",
                     file);
               log_info(LOG_INFO, " %s\n\n", line);
            } else {
               ptr = realloc(*hashTable, (sizeof(hash_t) * (*hashCount + 1)));
               if (ptr == NULL) {
                  err = BASE_ERR_MEM;
                  log_error(err, " error while allocating memory\n");
                  log_debug("ptr size: %lu\n",
                        sizeof(hash_t) *
                        (*hashCount + 1));
                  break;
               }
               *hashTable = ptr;
               memcpy(&((*hashTable)[*hashCount]), &tmp, sizeof(hash_t));
               (*hashCount)++;
               memset(&tmp, 0, sizeof(hash_t));
            }
         } else {
            break;
         }
      }
      fclose(fd);
   } else {
      err = BASE_ERR_DATA;
      log_error(err, " error open hash file: %s\n", file);
   }

   return err;
}


/* =========== PRIVATE FUNCTIONS =========================================== */

static unsigned char
hexDigit(
      char c
      )
{
  if(c<='9') return c-'0';
  else if (c<'a') return c-'A'+10;
  else return c-'a'+10;
}


static void
readHex(
      const char* x,
      unsigned char* p
      )
{
  for(; *x; x += 2)
     *p++ = hexDigit(x[0])*16 + hexDigit(x[1]);
}


static baseBool_t
parseHashList(
      hash_t* const hash,
      const char* const line,
      size_t size
      )
{
   baseBool_t ret = BASE_FALSE;
   baseError_t err = BASE_ERR_OK;
   char* locd = NULL;
   char* locs = NULL;

   locd = strstr(line, ":");
   if (locd) {
      int i;
      size_t next = size - 1;

      if ((locd - line) > UNAME_LEN) {
         err = BASE_ERR_LENGTH;
      }

      if (err == BASE_ERR_OK) {
         hash->unameLen = locd - line;
         for (i=0; i<hash->unameLen; i++) {
            hash->username[i] = toupper(line[i]);
         }

         locs = strstr(locd + 1, ":");
         if (locs) {
            next = locs - line;
            if (((size - 1) -  (next + 1)) != (SHA_STRING_LEN)) {
               err = BASE_ERR_LENGTH;
            }
         }
      }

      if (err == BASE_ERR_OK) {
         if ((next - hash->unameLen - 1) != (HASH_LEN * 2)) {
            err = BASE_ERR_LENGTH;
         }
      }

      if (err == BASE_ERR_OK) {
         memcpy(hash->desHashStr, locd + 1, next - hash->unameLen -1);
         readHex(locd + 1, hash->desHash);
         if (locs) {
            memcpy(hash->shaHashStr, locs + 1, (SHA_DIGEST_LENGTH * 2));
            readHex(hash->shaHashStr, hash->shaHash);
            memcpy(hash->shaSaltStr, locs + 1 + (SHA_DIGEST_LENGTH * 2), (SHA_SALT_LEN * 2));
            readHex(hash->shaSaltStr, hash->shaSalt);
         }
         ret = BASE_TRUE;
      }

   }

   return ret;
}


static size_t
_getline(
      char* line,
      size_t max,
      FILE* fd
      )
{
   if (fgets(line, max, fd) != NULL) {
      return strlen(line);
   }
   return -1;
}

/* ========================== END OF FILE ================================== */

/*
 * vim settings, please do not remove!
 * vim:autoindent:
 * vim:ts=3:sw=3:sts=3:expandtab:cindent:tw=75:formatoptions=croql:
 * vim600:foldmethod=syntax:
 */
