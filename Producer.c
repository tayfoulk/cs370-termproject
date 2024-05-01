#include "Producer.h"

/* arguments
1. IP address
2. Number of threads
*/

char *fileSplit(char *input, int pos, int size) {
    int segment = trunc(0.5 + (strlen(input) / size));
    char *result = malloc(sizeof(char) * segment);

    for (int i = pos; i < segment; i++) {
        if (i >= strlen(input)) break;
        result[i - pos] = input[i];
    }

    return (result);
}

void failed (int c_socket) {
    int *message = malloc(sizeof(int));
    *message = 0;

    send(c_socket, message, sizeof(int), 0);
    close(c_socket);
    free(message);
    exit (-1);
}

void succeed(int c_socket) {
    int *message = malloc(sizeof(int));
    *message = 1;

    send(c_socket, message, sizeof(int), 0);
    close(c_socket);
    free(message);
    exit (0);
}


int main (int argc, char *argv[]) {
    pid_t pid[4];
    int status;
    int fd[atoi(argv[2])][2];
    int shmid[atoi(argv[2])];

    int c_socket = makeClientSocket(argv[1]);

    char *encryptedFile; 
    char *key; // = key recieved from rfid reader
    char *hash;
    int* FileSize;
    char *message;
    
    read(c_socket, (int *)FileSize, sizeof(int));
    encryptedFile = malloc(sizeof(char) * *FileSize);
    read(c_socket, (char *)&encryptedFile, sizeof(char) * *FileSize);
    read(c_socket, (char *)hash, sizeof(char) * 128);

    int segment = trunc(*FileSize / atoi(argv[2]));
    if (segment <= 0) segment = 1;
    int count = 0;
    
    for (int i = 0; i < atoi(argv[2]), i++;) {
        if (i * segment >= *FileSize) break;

        message = fileSplit(encryptedFile, i * segment, atoi(argv[2]));        
        pipe(fd[i]);
        pid[i] = fork();

        if (pid[i] < 0) {
            exit(-1);
        } else if (pid[i] == 0) {
            char buffer[8];
            execlp("./Consumer", "Consumer", buffer, fileSplit(encryptedFile, i * segment, atoi(argv[2])) /* rfid call*/ , hash, NULL);
        } else {
            close(fd[i][0]);
            shmid[i] = shmget(IPC_PRIVATE, sizeof(char) * segment, IPC_CREAT | 0666);
            write (fd[i][1], &shmid[i], sizeof(shmid[i]));
            close(fd[i][1]);
            free(message);
        }
        count++;
    }

    free(encryptedFile);
    free(key);
    
    char *sharedMemory;
    char *result = malloc(sizeof(char) * *FileSize);
    pid_t tempPID[4];
    int pidFound = 0;
    
    for (int i = 0; i < count; i++) {
        tempPID[i] = wait(&status);

        for (int j = 0; j <= i; j++) {
            if (tempPID[j] == pid[i]){
                pidFound = 1;
            }
        }

        if (pidFound == 1){
            sharedMemory = (char*)shmat(shmid[i], NULL, 0);
            strcat(result, sharedMemory);
            shmctl(*sharedMemory, IPC_RMID, NULL);
        }
        pidFound = 0;
    }

    //hold hash
    uint32_t hashU[5];

    sha1(encryptedFile, hashU);
    char hash_str[128];
    
    //store hashval in hash_str
    ui32_to_char(hashU, hash_str);

    if (strcmp(hash_str, hash)) succeed(c_socket);

    failed (c_socket);
}
