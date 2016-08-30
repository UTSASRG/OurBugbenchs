
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


#include "base_types.h"
#include "hash_data.h"
#include "orca_thread.h"
#include "ngorca.h"
#include "log.h"

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>


#define MAX_NUM         19
#define MAX_AL          13
#define MAX_ALNUM       12
#define MAX_ALNUMSPEC   10





void
usage()
{
   const char* usage =
      "\n"
      " usage: ngorca -f <hashfile> [options]\n\n"
      "   -f  <file>\n"
      "       hashfile (format username:hash)\n"
      "   -l  <passLen>\n"
      "       length of the password.\n"
      "   -c  <charset>\n"
      "       1 for num, 2 for alpha\n"
      "       3 for alphanum ,\n"
      "       4 for alnum + special chars, default 3\n"
      "   -o  <logfile>\n"
      "       file containing the cracked hashes\n"
      "       and the status. default ngorca.log\n"
      "   -v  <verbose>\n"
      "       loglevel for logfile and standard output\n"
      "       1 to 4, 4 for finest logging. default 1\n"
      "   -t  <threads>\n"
      "       number of threads to use. default 1\n";

   printf("\n %s (http://netgarage.org)\n", PACKAGE_STRING);
   printf("%s\n", usage);
   exit(0);
}


void
sigInt(
      int s
      )
{
   log_clean();
   printf("\n");
   exit(0);
}


baseBool_t
checkUpperLimit(
      charSet_t c,
      int passlen
      )
{
   baseBool_t ret = BASE_TRUE;

   switch (c) {
      case NUM_CHARSET:
         if(passlen > MAX_NUM)
            ret = BASE_FALSE;
         break;
      case AL_CHARSET:
         if(passlen > MAX_AL)
            ret = BASE_FALSE;
         break;
      case ALNUM_CHARSET:
         if(passlen > MAX_ALNUM)
            ret = BASE_FALSE;
         break;
      case ALNUM_SPEC_CHARSET:
         if(passlen > MAX_ALNUMSPEC)
            ret = BASE_FALSE;
         break;
   }
   return ret;
}


void
setThreadPwds(
      unsigned long long int* pwds,
      int threadCount,
      charSet_t charset
      )
{
   const char* set = NULL;
   int charsetLen = 0;
   int passLen = hsh_getPassLength();
   unsigned long long int maxpwd = 1, tmp = 0;
   int i = 0;

   set = hsh_getCharset(charset);
   charsetLen = strlen(set);
   for (i=0; i<passLen; i++) {
      maxpwd *= charsetLen;
   }
   tmp = maxpwd / threadCount;
   pwds[0] = 0;
   for (i=1; i<threadCount+1; i++) {
      pwds[i] = tmp * i;
   }
   pwds[threadCount] += (maxpwd % threadCount);
}


int main(int argc, char *argv[])
{
   baseError_t err = BASE_ERR_OK;
   int hashCount = 0;
   char hashFile[MAX_FILENAME] = {0};
   char logFile[MAX_FILENAME] = {0};
   logLevel_t loglevel = LOG_BASIC;
   charSet_t charset = ALNUM_CHARSET;
   hash_t* hashTable = NULL;
   thread_t* threads = NULL;
   threadArg_t* thrArgs = NULL;
   pthread_t percThr = 0;
   unsigned long long int* pwds = NULL;
   int threadCount = 1;
   int i, j=0;
   int opt = 0;
   int startNum = 5, endNum =8;

   strncpy(logFile, "ngorca.log", MAX_FILENAME);

   printf("\n");

   if (argc < 2) {
      usage();
   }

   while ((opt = getopt(argc, argv, "l:s:f:c:o:v:t:h")) != -1) {
      switch(opt) {
         case 'f':
            strncpy(hashFile, optarg, MAX_FILENAME);
            hashFile[MAX_FILENAME - 1] = 0;
            break;
         case 'l':
            err = hsh_setPassLength(atoi(optarg));
            if (err != BASE_ERR_OK) {
               fprintf(stderr, " error invalid password length %d\n",
                     atoi(optarg));
            } else {
               startNum = hsh_getPassLength();
               endNum = startNum;
            }
            break;
         case 'c':
            charset = atoi(optarg);
            if ((charset < 1) || (charset > sizeof(charSet_t))) {
               err = BASE_ERR_DATA;
               fprintf(stderr, " error invalid charset %d\n", atoi(optarg));
            }
            break;
         case 'o':
            strncpy(logFile, optarg, MAX_FILENAME);
            logFile[MAX_FILENAME - 1] = 0;
            break;
         case 'v':
            loglevel = atoi(optarg);
            if ((loglevel < 1) || (loglevel > sizeof(logLevel_t))) {
               err = BASE_ERR_DATA;
               fprintf(stderr, " error invalid loglevel %d\n", atoi(optarg));
            }
            break;
         case 't':
            threadCount = atoi(optarg);
            if (threadCount < 1) {
               err = BASE_ERR_DATA;
               fprintf(stderr, " error invalid thread count %d\n", atoi(optarg));
            }
            break;
         case 'h':
         default:
            usage();
      }
   }

   if (err == BASE_ERR_OK) {
      if (checkUpperLimit(charset, hsh_getPassLength()) == BASE_FALSE) {
         fprintf(stderr, " error number of possible passwords is to high\n");
         err = BASE_ERR_LENGTH;
      }
   } else {
      fprintf(stderr, " use -h for help\n");
   }

   if (err == BASE_ERR_OK) {

      log_init(logFile, loglevel);
      signal(SIGINT, sigInt);
      log_info(LOG_BASIC, "\n %s (http://netgarage.org)\n\n", PACKAGE_STRING);

      log_debug("hashfile: %s\npasslength: %d\ncharset: %d\nlogfile: %s\n"
            "loglevel: %d\nthreadcount: %d\n\n", hashFile, hsh_getPassLength(),
            charset, logFile, loglevel, threadCount);
   }

   if (err == BASE_ERR_OK) {
      pwds = malloc(sizeof(unsigned long long int) * (threadCount + 1));
      if (pwds == NULL) {
         err = BASE_ERR_MEM;
         log_error(err, " error while allocating memory\n");
         log_debug("pwds size: %lu\n", sizeof(unsigned long long int) *
               (threadCount + 1));
      }
   }

   if (err == BASE_ERR_OK) {
      err = hsh_readHashList(&hashTable, &hashCount, hashFile);
   }

   if (err == BASE_ERR_OK) {
      threads = malloc(sizeof(thread_t) * threadCount);
      if (threads == NULL) {
         err = BASE_ERR_MEM;
         log_error(err, " error while allocating memory\n");
         log_debug("threads size: %d\n", sizeof(thread_t) * threadCount);
      } else {
         thrArgs = malloc(sizeof(threadArg_t) * threadCount);
         if (thrArgs == NULL) {
            err = BASE_ERR_MEM;
            log_error(err, " error while allocating memory\n");
            log_debug("thrArgs size: %d\n", sizeof(threadArg_t) * threadCount);
         }
      }
   }

   if (err == BASE_ERR_OK) {
      const char* set = NULL;
      set = hsh_getCharset(charset);
      if (orc_init(set) == BASE_FALSE) {
         err = BASE_ERR_CRYPT;
         log_error(err, " error while initialise orca\n");
      }
   }

   if (err == BASE_ERR_OK) {
      struct rusage startUsage;
      struct rusage endUsage;
      struct rusage tmpUsage;
      time_t stime, ttime, etime;
      const char* seperator =
         " .................................................\n\n";
      int hashcount = hashCount;
      baseBool_t percentPrint = BASE_FALSE;
      percThreadArg_t percArg = {0};
      int k;

      getrusage(RUSAGE_SELF, &startUsage);
      time(&stime);
      log_info(LOG_BASIC, " starting %d thread(s) to calculate %d hash value(s)\n",
            threadCount, hashCount);
      log_info(LOG_BASIC, seperator);



      while (hashcount > 0) {
         getrusage(RUSAGE_SELF, &tmpUsage);
         time(&ttime);

         for (k=startNum; k<=endNum; k++) {
            hsh_setPassLength(k);
            setThreadPwds(pwds, threadCount, charset);
            thr_setThreadsRun();
            if (loglevel == LOG_FINEST) {
               percArg.threadCount = threadCount;
               percArg.passLen = k;
               if (pthread_create(&percThr, NULL, thr_percentPrint, &percArg) != 0) {
                  log_error(BASE_ERR_KO, " error could not start percent print out thread\n");
               } else {
                  percentPrint = BASE_TRUE;
               }
            }

            for (i=0; i<threadCount; i++) {
               thrArgs[i].id = i;
               thrArgs[i].th = threads;
               thrArgs[i].threadCount = threadCount;
               thrArgs[i].percPrint = percentPrint;
               threads[i].sPwd = pwds[i];
               threads[i].ePwd = pwds[i+1];
               threads[i].hash = &(hashTable[j]);
               if (pthread_create(&threads[i].tid, NULL, thr_run, &thrArgs[i]) != 0) {
                  log_error(BASE_ERR_KO, " error could not start thread %d\n", i);
               }
            }

            for (i=0; i<threadCount; i++) {
               pthread_join(threads[i].tid, NULL);
               log_debug(" thread %x finished\n", threads[i].tid);
            }

            if (loglevel == LOG_FINEST) {
               thr_terminatePercThr();
               pthread_join(percThr, NULL);
            }

            if (hashTable[j].found == BASE_TRUE) {
               break;
            }
         }

         if (hashTable[j].found == BASE_FALSE) {
            log_info(LOG_BASIC, "\n no pwd found for %s\n", hashTable[j].username);
         }

         getrusage(RUSAGE_SELF, &endUsage);
         time(&etime);
         log_info(LOG_FINE, " needed %lu seconds of cpu time\n",
               ((endUsage.ru_utime.tv_sec - tmpUsage.ru_utime.tv_sec) +
                (endUsage.ru_stime.tv_sec - tmpUsage.ru_stime.tv_sec)));
         log_info(LOG_INFO, " needed %d seconds\n\n",
               etime - ttime);
         log_info(LOG_BASIC, seperator);
         getrusage(RUSAGE_SELF, &tmpUsage);
         time(&ttime);
         hashcount--;
         j++;
      }


      getrusage(RUSAGE_SELF, &endUsage);
      time(&etime);
      log_info(LOG_FINE, " needed %lu seconds of cpu time\n",
            ((endUsage.ru_utime.tv_sec - startUsage.ru_utime.tv_sec) +
             (endUsage.ru_stime.tv_sec - startUsage.ru_stime.tv_sec)));
      log_info(LOG_INFO, " needed %d seconds\n\n",
            etime - stime);
   }

   if (hashTable)
      free(hashTable);
   if (pwds)
      free(pwds);
   if (threads)
      free(threads);
   if (thrArgs)
      free(thrArgs);

   log_clean();

   printf("\n");

   return 0;
}


















