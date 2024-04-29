#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "socket_conn.h"
char* read_file(FILE* file, int* flen){
	fseek(file, 0L, SEEK_END);
	//save file size to flen address
	*flen=ftell(file);
	char* data=(char*)malloc(*flen);
	rewind(file);
	//printf("%d\n", flen);
	uint32_t valread=fread(data, sizeof(char), *flen, file);
	return data;
}
char* open_read_close(const char* filename, int* flen){
	//file handling
	FILE* file;
	file=fopen(filename, "r");
	if(file==NULL){
		printf("Unable to open file \"%s\": File may not exist, or is lacking permission\n", filename);
		exit(1);
		return NULL;
	}
	char* data=read_file(file, flen);
	fclose(file);
	return data;
}
//Desktop is the server
/*
	1: filename
	if this needs to be changed to work do so
	
	Reads a file, sends the raw file data over
	to the pi, then displays the result from the
	raspberry pi.
*/
int main(int argc, char **argv){
	if(argc<=1){
		printf("No filename provided. Ending execution\n");
		return 1;
	}
	int flen;
	//read file contents
	char* filedat=open_read_close(argv[1], &flen);
	char filesize[8];
	//convert flen to char pointer
	sprintf(filesize, "%d", flen);
	//set up client connection
	//this waits until client connects to server
	int s_socket=makeServerSocket();
	int c_socket=connectClient(s_socket);
	//first send over file size
	send(c_socket, filesize, 8, 0);
	//then send file contents
	send(c_socket, filedat, flen+1, 0);
	//now wait, compute file hash while waiting
	//uint32_t myhash[5];
	
	
	//not sure exactly what happens here
	
	
	//read result from client
	int result;
	uint32_t valread=read(c_socket, (char*)&result, sizeof(int));
	printf("Result: %d\n", result);
	//cleanup
	close(c_socket);
	close(s_socket);
	free(filedat);
}
