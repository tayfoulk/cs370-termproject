#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "socket_conn.h"
#include "Encryption.h"
#include "sha1.h"
#include "convert.h"
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
	//get hash and convert to string
	uint32_t myhash[5];
	char hash_str[128];
	sha1(filedat, myhash);
	ui32_to_char(myhash, hash_str);
	//convert flen to char pointer
	sprintf(filesize, "%d", flen);
	//set up client connection
	//this waits until client connects to server
	int s_socket=makeServerSocket();
	int c_socket=connectClient(s_socket);
	//first send over file size
	send(c_socket, filesize, 8, 0);
	//encrypt file
	encrypt(filedat, "idk what the key is");
	//then send encrypted file contents
	send(c_socket, filedat, flen+1, 0);
	//finally send hash
	send(c_socket, hash_str, 128, 0);
	//await response from client...
	//read result from client
	int result;
	uint32_t valread=read(c_socket, (char*)&result, sizeof(int));
	printf("Result: %d\n", result);
	//cleanup
	close(c_socket);
	close(s_socket);
	free(filedat);
}
