/*
 * Copyright (c) 1987, 1993, 1994
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <signal.h>
#include <pcap.h>		// for PCAP_ERRBUF_SIZE

#include "portability.h"	// this includes <string.h>
#include "rpcapd.h"
#include "fileconf.h"
#include "sockutils.h"		// for SOCK_ASSERT
#include "rpcap-protocol.h"

static int strrem(char *string, char chr);

void fileconf_read(int sign)
{
	FILE *fp;
	char msg[PCAP_ERRBUF_SIZE + 1];
	int i;

#ifndef _WIN32
	signal(SIGHUP, fileconf_read);
#endif

	if ((fp = fopen(loadfile, "r")) != NULL)
	{
		char line[MAX_LINE + 1];
		char *ptr;

		hostlist[0] = 0;
		i = 0;

		while (fgets(line, MAX_LINE, fp) != NULL)
		{
			if (line[0] == '\n') continue;	// Blank line
			if (line[0] == '\r') continue;	// Blank line
			if (line[0] == '#') continue;	// Comment

			if ((ptr = strstr(line, "ActiveClient")))
			{
				char *address, *port;
				char *lasts;

				ptr = strchr(ptr, '=') + 1;
				address = pcap_strtok_r(ptr, RPCAP_HOSTLIST_SEP, &lasts);

				if ((address != NULL) && (i < MAX_ACTIVE_LIST))
				{
					port = pcap_strtok_r(NULL, RPCAP_HOSTLIST_SEP, &lasts);
					strlcpy(activelist[i].address, address, MAX_LINE);

					if (strcmp(port, "DEFAULT") == 0) // the user choose a custom port
						strlcpy(activelist[i].port, RPCAP_DEFAULT_NETPORT_ACTIVE, MAX_LINE);
					else
						strlcpy(activelist[i].port, port, MAX_LINE);

					activelist[i].address[MAX_LINE] = 0;
					activelist[i].port[MAX_LINE] = 0;
				}
				else
					SOCK_ASSERT("Only MAX_ACTIVE_LIST active connections are currently supported.", 1);

				i++;
				continue;
			}

			if ((ptr = strstr(line, "PassiveClient")))
			{
				ptr = strchr(ptr, '=') + 1;
				strlcat(hostlist, ptr, MAX_HOST_LIST);
				strlcat(hostlist, ",", MAX_HOST_LIST);
				continue;
			}

			if ((ptr = strstr(line, "NullAuthPermit")))
			{
				ptr = strstr(ptr, "YES");
				if (ptr)
					nullAuthAllowed = 1;
				else
					nullAuthAllowed = 0;
				continue;
			}
		}

		// clear the remaining fields of the active list 
		while (i < MAX_ACTIVE_LIST)
		{
			activelist[i].address[0] = 0;
			activelist[i].port[0] = 0;
			i++;
		}

		// Remove all '\n' and '\r' from the strings
		strrem(hostlist, '\r');
		strrem(hostlist, '\n');

		pcap_snprintf(msg, PCAP_ERRBUF_SIZE, "New passive host list: %s\n\n", hostlist);
		SOCK_ASSERT(msg, 1);
		fclose(fp);
	}
}

int fileconf_save(const char *savefile)
{
	FILE *fp;

	if ((fp = fopen(savefile, "w")) != NULL)
	{
		char *token; /*, *port;*/					// temp, needed to separate items into the hostlist
		char temphostlist[MAX_HOST_LIST + 1];
		int i = 0;
		char *lasts;

		fprintf(fp, "# Configuration file help.\n\n");

		// Save list of clients which are allowed to connect to us in passive mode
		fprintf(fp, "# Hosts which are allowed to connect to this server (passive mode)\n");
		fprintf(fp, "# Format: PassiveClient = <name or address>\n\n");

		strncpy(temphostlist, hostlist, MAX_HOST_LIST);
		temphostlist[MAX_HOST_LIST] = 0;
	
		token = pcap_strtok_r(temphostlist, RPCAP_HOSTLIST_SEP, &lasts);
		while(token != NULL)
		{
			fprintf(fp, "PassiveClient = %s\n", token);
			token = pcap_strtok_r(NULL, RPCAP_HOSTLIST_SEP, &lasts);
		}


		// Save list of clients which are allowed to connect to us in active mode
		fprintf(fp, "\n\n");
		fprintf(fp, "# Hosts to which this server is trying to connect to (active mode)\n");
		fprintf(fp, "# Format: ActiveClient = <name or address>, <port | DEFAULT>\n\n");


		while ((activelist[i].address[0] != 0) && (i < MAX_ACTIVE_LIST))
		{
			fprintf(fp, "ActiveClient = %s, %s\n", activelist[i].address, activelist[i].port);
			i++;
		}

		// Save if we want to permit NULL authentication
		fprintf(fp, "\n\n");
		fprintf(fp, "# Permit NULL authentication: YES or NOT\n\n");

		if (nullAuthAllowed)
			fprintf(fp, "NullAuthPermit = YES\n");
		else
			fprintf(fp, "NullAuthPermit = NO\n");

		fclose(fp);
		return 0;
	}
	else
	{
		return -1;
	}

}

static int strrem(char *string, char chr)
{
	char *pos;
	int num = 0;
	int len, i;

	while ((pos = strchr(string, chr)) != NULL)
	{
		num++;
		len = strlen(pos);
		for (i = 0; i < len; i++)
			pos[i] = pos[i+1];
	}

	return num;
}
