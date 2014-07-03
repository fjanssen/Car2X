#ifndef _CLIENT_LIST_H
#define _CLIENT_LIST_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>

#include "list.h"


struct client {
	struct sockaddr_in sa;
	int sd;
	struct timeval ts;
	int spam;
};


struct client_list {
	struct list_head list;
	struct client cl;
	int count;
};


void cl_init(struct client_list *cl);

void cl_purge(struct client_list *cl);

void cl_add(struct client_list *cl, int sd, struct sockaddr_in sa);

struct client *cl_find(struct client_list *cl, fd_set rfd);

struct client *cl_find_by_ip(struct client_list *cl, struct sockaddr_in sa);

int cl_remove_by_ip(struct client_list *cl, struct sockaddr_in sa);

int cl_remove(struct client_list *cl, int sd);

#endif


