#ifndef SOCKET_CONN_H_INCLUDED
#define SOCKET_CONN_H_INCLUDED
#ifndef PORTNUM
#define PORTNUM 37024
#endif
//server side
extern int makeServerSocket();
extern int connectClient(int);
//client side
extern int makeClientSocket(char*);
#endif
