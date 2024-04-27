//socket stuff
#include <sys/socket.h>
//internet stuff
#include <netinet/in.h>
#include <arpa/inet.h>
//standard stuff
#include <unistd.h>
#include <stdio.h>
#include "socket_conn.h"
//easily changable port number
//#define PORTNUM 37024
/*
	----------------SERVER SIDE----------------
	Server knows its own IP, so no need to specify it
*/
//bind the server socket and allow for listen
int makeServerSocket(){
	int serverSocket=socket(AF_INET, SOCK_STREAM, 0);
	//specify address, found on geeksforgeeks
	struct sockaddr_in serverAddress;
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(PORTNUM);
	serverAddress.sin_addr.s_addr=INADDR_ANY;
	//bind socket
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	return serverSocket;
}
//wait for client to connect, then return clientSocket
int connectClient(int s_socket){
	listen(s_socket, 5);
	int c_socket=accept(s_socket, NULL, NULL);
	return c_socket;
}
/*
	----------------CLIENT SIDE----------------
	Server IP must be provided
*/
//client socket creation and connection to server
//must be run after server starts
int makeClientSocket(char* ipv4_addr){
	int clientSocket=socket(AF_INET, SOCK_STREAM, 0);
	//specify address
	struct sockaddr_in serverAddress;
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(PORTNUM);
	//must be supplied with server IP address
	inet_pton(AF_INET, ipv4_addr, &serverAddress.sin_addr);
	//connect to server
	connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	return clientSocket;
}
