
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

#include "ngorca.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "log.h"

#include <openssl/des.h>
#include <openssl/sha.h>
#include <string.h>
#include <ctype.h>


/* =========== GLOBALS ===================================================== */

static
unsigned char initDeskey[8] = {0};

static
des_key_schedule schedule1;

static
const char* charset = NULL;

static
int charsetLength = 0;

static
baseBool_t initDone = BASE_FALSE;

static
int bitmask[19] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200,
   0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000 };


/* =========== PRIVATE PROTOTYPES ========================================== */

/* =========== PUBLIC FUNCTIONS ============================================ */

baseBool_t
orc_init(
      const char* const cset
      )
{
   baseBool_t ret = BASE_TRUE;

   initDeskey[0] = 0x01;
   initDeskey[1] = 0x23;
   initDeskey[2] = 0x45;
   initDeskey[3] = 0x67;
   initDeskey[4] = 0x89;
   initDeskey[5] = 0xab;
   initDeskey[6] = 0xcd;
   initDeskey[7] = 0xef;

   charset = cset;
   charsetLength = strlen(charset);
   if (des_set_key(&initDeskey, schedule1)) {
      log_error(BASE_ERR_CRYPT, " error while setting DES key\n");
      ret = BASE_FALSE;
   }

   if (ret == BASE_TRUE) {
      initDone = BASE_TRUE;
   }
   return ret;
}


void
orc_getPassword(
      char* const passwd,
      unsigned long long int pwd
      )
{
   int i;
   int passLen = hsh_getPassLength();

   for (i=0; i<passLen; i++) {
      passwd[i] = charset[pwd % charsetLength];
      pwd /= charsetLength;
   }
}


void
orc_getCaseSensPassword(
      char* const passwd,
      int pwd
      )
{
   int i;
   int passLen = hsh_getPassLength();

   for (i=0; i<passLen; i++) {
      if (pwd & (bitmask[i])) {
         passwd[i] = tolower(passwd[i]);
      } else {
         passwd[i] = toupper(passwd[i]);
      }
   }
}


baseError_t
orc_generateDESHash(
      hash_t* const hash,
      char* password,
      unsigned char* const currentHash
      )
{
   baseError_t err = BASE_ERR_OK;
   unsigned char plaintextstring[128] = {0};
   unsigned char ciphertextstring[128] = {0};
   unsigned char salt_iv[8] = {0};
   unsigned char deskey[8] = {0};
   des_key_schedule schedule2;
   int passLen = hsh_getPassLength();
   int length = hash->unameLen + passLen;
   int i, j;

   if (initDone == BASE_FALSE) {
      log_errorMutexed(BASE_ERR_INIT, " error ngorca is not initialisated\n");
      return BASE_ERR_INIT;
   }

   for (j=0, i=1; j<hash->unameLen; j++, i+=2) {
      plaintextstring[i] = hash->username[j];
   }
   for (j=0; j<passLen; j++, i+=2) {
      plaintextstring[i] = password[j];
   }

   length += 8 - (length % 8);
   length *= 2;

   memset(salt_iv, 0, 8);
   des_ncbc_encrypt(plaintextstring, ciphertextstring, length, schedule1, &salt_iv, 1);
   for (i=0, j=8; i<8; i++, j--) {
      deskey[i] = ciphertextstring[length - j];
   }

   if (des_set_key(&deskey, schedule2)) {
      err = BASE_ERR_CRYPT;
      log_errorMutexed(err, " error while setting DES key\n");
   }

   if (err == BASE_ERR_OK) {
      memset(salt_iv, 0, 8);
      des_ncbc_encrypt(plaintextstring, ciphertextstring, length, schedule2, &salt_iv, 1);
      for (i=0; i<8; i++) {
         currentHash[i] = ciphertextstring[length - 8 + i];
      }
   }

   return err;
}


baseError_t
orc_generateSHAHash(
      char* const password,
      unsigned char* const currentHash
      )
{
   baseError_t err = BASE_ERR_OK;
   int len = hsh_getPassLength();
   len += SHA_SALT_LEN;

   if (SHA1((unsigned char*)password, len, currentHash) == NULL) {
      err = BASE_ERR_CRYPT;
      log_errorMutexed(err, " error while calculating sha1 hash\n");
   }
   return err;
}


baseBool_t
orc_compareHash(
      const unsigned char* const hash,
      const unsigned char* const currentHash,
      int size
      )
{
   int i;
   for(i=0; i<size; i++) {
      if(hash[i] != currentHash[i])
          return BASE_FALSE;
   }
   return BASE_TRUE;
}


void
orc_printResult(
      const hash_t* const hash,
      const char* const pwd
      )
{
   log_info(LOG_BASIC, " username: %s   password: %s\n", hash->username, pwd);
}

/* ========================== END OF FILE ================================== */

/*
 * vim settings, please do not remove!
 * vim:autoindent:
 * vim:ts=3:sw=3:sts=3:expandtab:cindent:tw=75:formatoptions=croql:
 * vim600:foldmethod=syntax:
 */
