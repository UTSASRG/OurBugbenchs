
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


#ifndef __NGORCA_H__
#define __NGORCA_H__


/* =========== INCLUDES ==================================================== */

#include "base_types.h"
#include "hash_data.h"

/* =========== PUBLIC PROTOTYPES =========================================== */

/*---------------------------------------------------------------------------*/
/* initialise and sets the DES key.
 *
 * @param cest             in : pointer to a charset
 * @return baseBool_t      BASE_TRUE for success
*/
baseBool_t
orc_init(
      const char* const cset
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * get the next password
 *
 * @param passwd           out : pointer to the password buffer
 * @param pwd              in  : actual password as numerical data
*/
void
orc_getPassword(
      char* const passwd,
      unsigned long long int pwd
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * get the next case sensitive password
 *
 * @param passwd           out : pointer to the password buffer
 * @param pwd              in  : actual password as numerical data
*/
void
orc_getCaseSensPassword(
      char* const passwd,
      int pwd
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* generates the hash to a given input and writes it to currentHash.
 *
 * @param hash             in : pointer to hash data
 * @param password         in : pointer to plaintext
 * @param currentHash      out: hash over the plaintext
 * @return baseError_t     RET_OK for success or baseError_t error type
*/
baseError_t
orc_generateDESHash(
      hash_t* const hash,
      char* const password,
      unsigned char* const currentHash
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* generates the hash to a given input and writes it to currentHash.
 *
 * @param password         in : pointer to plaintext
 * @param currentHash      out: hash over the plaintext
 * @return baseError_t     RET_OK for success or baseError_t error type
*/
baseError_t
orc_generateSHAHash(
      char* const password,
      unsigned char* const currentHash
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * compares two hash values
 *
 * @param hash             in : pointer to first hash
 * @param currentHash      in : pointer to second hash
 * @return baseBool_t      BASE_TRUE for identical hash values
*/
baseBool_t
orc_compareHash(
      const unsigned char* const hash,
      const unsigned char* const currentHash,
      int size
      );
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*
 * prints the result to standard output and logging file
 * uses log_info from log.h
 *
 * @param hash             in : pointer to the hash struct
 * @param pwd              in : pointer to the pwd of the hash data
*/
void
orc_printResult(
      const hash_t* const hash,
      const char* const pwd
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

