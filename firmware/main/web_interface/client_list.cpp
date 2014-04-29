#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client_list.h"

void
cl_init(struct client_list *cl) 
{
	INIT_LIST_HEAD(&cl->list);
	cl->count = 0;
}


void
cl_purge(struct client_list *cl)
{
	struct client_list *tmp;
	struct list_head *pos;
	struct list_head *q;

	list_for_each_safe(pos, q, &(cl->list)) {
		tmp = list_entry(pos, struct client_list, list);
		list_del(pos);
		free(tmp);
		cl->count--;
	}
}


void
cl_add(struct client_list *cl, int sd, struct sockaddr_in sa)
{
	struct client_list *tmp;
	
	tmp = (struct client_list *)malloc(sizeof(struct client_list));
	memset(tmp,0,sizeof(*tmp));
	tmp->cl.sd = sd;
	tmp->cl.sa = sa;
	tmp->cl.spam = 0;
	gettimeofday(&tmp->cl.ts,NULL);
	list_add(&(tmp->list), &cl->list);
	cl->count++;
}

struct client *
cl_find(struct client_list *cl, fd_set rfd)
{
	struct client_list *tmp;
	struct list_head *pos;
	struct list_head *q;

	list_for_each_safe(pos, q, &(cl->list)) {
		tmp = list_entry(pos, struct client_list, list);
		if (FD_ISSET(tmp->cl.sd,&rfd))
			return &tmp->cl;
	}

	return NULL;
}

struct client *
cl_find_by_ip(struct client_list *cl, struct sockaddr_in sa)
{
	struct client_list *tmp;
	struct list_head *pos;
	struct list_head *q;

	list_for_each_safe(pos, q, &(cl->list)) {
		tmp = list_entry(pos, struct client_list, list);
		if (sa.sin_addr.s_addr == tmp->cl.sa.sin_addr.s_addr)
			return &tmp->cl;
	}

	return NULL;
}

int
cl_remove_by_ip(struct client_list *cl, struct sockaddr_in sa)
{
	struct client_list *tmp;
	struct list_head *pos;
	struct list_head *q;

	list_for_each_safe(pos, q, &(cl->list)) {
    	tmp = list_entry(pos, struct client_list, list);
		if (tmp->cl.sa.sin_addr.s_addr == sa.sin_addr.s_addr) {
			list_del(pos);
			free(tmp);
			cl->count--;
			return 0;
		}
	}
	
	fprintf(stderr,"failed to remove client from list\n");

	return -1;
}

int
cl_remove(struct client_list *cl, int sd) 
{
	struct client_list *tmp;
	struct list_head *pos;
	struct list_head *q;

	list_for_each_safe(pos, q, &(cl->list)) {
    	tmp = list_entry(pos, struct client_list, list);
		if (tmp->cl.sd == sd) {
			list_del(pos);
			free(tmp);
			cl->count--;
			return 0;
		}
	}

	fprintf(stderr,"failed to remove client from list\n");

	return -1;
}


