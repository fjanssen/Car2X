/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "webserver.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define BUFFLEN		1024


int _run;
char closeMessage[1024];

int port;
void (*callback)(void*);

void setUpServer(int srvport, void (*onRequest)(void*))
{
	port = srvport;
	callback = onRequest;
}


int closeServer()
{
	_run = 0;
	return _run;
}

void*
openServer(void *data)
{
	struct sockaddr_in sa_srv,sa_client;
	int sd,csd,len,maxfd;
	static char inbuff[BUFFLEN];
	static char outbuff[2*BUFFLEN];
	socklen_t slen;
	fd_set rfds,rfd;

	sprintf(closeMessage,"The server is shutting down\n");	

	slen	= sizeof(sa_client);

	memset(&sa_srv,0,sizeof(sa_srv));
	memset(&sa_client,0,sizeof(sa_client));

	/* Prepar sockaddr for the server */
	sa_srv.sin_family      = AF_INET;
	sa_srv.sin_port        = htons(port);
	sa_srv.sin_addr.s_addr = INADDR_ANY;

	/* Get a socket, bind to it, and mark it as passive */
	if (0 > (sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))) {
		perror("socket() failed");
		exit(1);
	}
	printf("Wait for bind()\n");
	while (0 > bind(sd,(struct sockaddr *)&sa_srv,sizeof(sa_srv))) {
		//perror("bind() failed");
		//exit(1);
	}
	printf("bind() successfull\n");
	if (0 > listen(sd,1)) {
		perror("listen() failed");
		exit(1);
	}

	/* Prepare fd_set */
	FD_ZERO(&rfds);
#if (0)
	FD_SET(sd,&rfds);
#endif
	maxfd = sd;

	/* Enter event loop */
	_run = 1;
	printf("Wait for incoming clients\n");
	while (_run) {
		memset(inbuff,0,sizeof(inbuff));
		memset(outbuff,0,sizeof(outbuff));
		rfd = rfds;
#if (0)
		/* Wait until something happens */
		if (0 > select(maxfd+1,&rfd,NULL,NULL,NULL)) {
			if (errno == EINTR)
				continue;
			perror("select() failed");
			exit(1);
		}
		/* Check for a new client */
		if (FD_ISSET(sd,&rfd)) 
#endif
		{
			csd = accept(sd,(struct sockaddr *)&sa_client,&slen);
			if (0 > csd) {
				perror("accept() failed");
				exit(1);
			}
			

			sprintf(outbuff,"server: new connection from %s:%d\n",
				inet_ntoa(sa_client.sin_addr),
				ntohs(sa_client.sin_port));
			//fprintf(stdout,"%s",outbuff);
		
			int totallen = 0;
			while(true)
			{
				len = recv(csd,inbuff+totallen,BUFFLEN-1-totallen,0);

				if (0 >= len) {
					sprintf(outbuff,"server: %s:%d quit\n",
						inet_ntoa(sa_client.sin_addr),
						ntohs(sa_client.sin_port));
					//fprintf(stdout,"%s",outbuff);

					close(csd);
#if (0)
					FD_CLR(csd,&rfds);
#endif
					break;

				}
				else {
					totallen += len;
					inbuff[totallen] = 0;
					//printf("len = %d, totallen = %d String = %s", len, totallen, inbuff);
					if (strstr(inbuff, "ENDE") != NULL)
					{
						sprintf(outbuff,"%s:%d: %s",
							inet_ntoa(sa_client.sin_addr),
							ntohs(sa_client.sin_port),inbuff);
						//fprintf(stdout,"%s",outbuff);
						callback((void*) inbuff);
				
						// Send answer
						sprintf(outbuff, "HTTP/1.0 200 OK\r\nContent-type: text/plain\r\nContent-length: 7\r\n\r\nhallo\r\n");
						send(csd, outbuff, strlen(outbuff),0);
						//printf("Inbuff = %s\n",inbuff);
						totallen = 0;
						close(csd);
						break;
					}
				}
			}
		}

	}

	close(sd);

	return 0;
}


