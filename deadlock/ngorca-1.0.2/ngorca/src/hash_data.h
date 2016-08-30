
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


#ifndef __HASH_DATA_H__
#define __HASH_DATA_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* =========== INCLUDES ==================================================== */

#include "base_types.h"

#include <openssl/sha.h>

/* =========== DEFINES ===================================================== */

/* maximum user name length */
#define  UNAME_LEN      64
/* maximum password length */
#define  MAX_PASSLENGTH 20
/* hash length */
#define  HASH_LEN       8
/* sha salt */
#define SHA_SALT_LEN    10
/* TODO */
#define SHA_STRING_LEN  (SHA_DIGEST_LENGTH * 2) + (SHA_SALT_LEN * 2)

/* =========== DATA TYPES ================================================== */

/*
 * charset enumeration
 */
typedef enum {
   NUM_CHARSET = 1,
   AL_CHARSET,
   ALNUM_CHARSET,
   ALNUM_SPEC_CHARSET
} charSet_t;

/*
 * structure for the user hash data
 */
typedef struct {
   char username[UNAME_LEN];
   int unameLen;
   char password[MAX_PASSLENGTH];
   unsigned char desHash[HASH_LEN];
   char desHashStr[HASH_LEN * 2];
   unsigned char shaHash[SHA_DIGEST_LENGTH];
   unsigned char shaSalt[SHA_SALT_LEN];
   char shaHashStr[SHA_DIGEST_LENGTH * 2];
   char shaSaltStr[SHA_SALT_LEN * 2];
   baseBool_t found;
} hash_t;


/* =========== PUBLIC PROTOTYPES =========================================== */

/*---------------------------------------------------------------------------*/
/* set password length
 * check the range of the password length
 *
 * @param len              in : length of the passwords
 * @return baseError_t     RET_OK for success or BASE_ERR_LENGTH
 */
baseError_t
hsh_setPassLength(
      int len
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* get password length
 *
 * @return int             returns length of password
 */
int
hsh_getPassLength(
      void
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* get the choosen charset
 *
 * @param c                in : charset
 * @return const char*     pointer of the charset
 */
const char*
hsh_getCharset(
      charSet_t c
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* fills a hash table with data from file.
 * allocates memory for the table, must be freed by the caller.
 *
 * @param hashTable        out: pointer to hash table
 * @param hashCount        out: number of hash in table
 * @param file             in : file name to read from
 * @return baseError_t     RET_OK for success or baseError_t error type
*/
baseError_t
hsh_readHashList(
      hash_t** const hashTable,
      int* const hashCount,
      const char* const file
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

