#ifndef _WEBSERVER_H
#define _WEBSERVER_H

void setUpServer(int srvport, void (*onRequest)(void*));

void* openServer(void *data);

int closeServer();



#endif /* _WEBSERVER_H */
