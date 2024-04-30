#include "Producer.h"


int main (int argc, char *argv[]) {
    pid_t pid[4];
    int status;
    int fd[argv[2]][2];
    int shmid[argv[2]];

    int c_socket = makeClientSocket(argv[1]);

    char *encryptedFile; 
    char *key; // = key recieved from rfid reader
    char hash[128];
    int FileSize = 0;
    
    read(c_socket, (int)FileSize, sizeof(int));
    encryptedFile = malloc(sizeof(char) * FileSize);
    read(c_socket, (char *)&encryptedFile, sizeof(char) * FileSize);
    read(c_socket, (char)hash, sizeof(char) * 128);
    
    for (int i = 0; i < argv[2], i++;) {
        pipe(fd[i]);

        pid[i] = fork();

        if (pid[i] < 0) {
            exit(-1);
        } else if (pid[i] == 0) {
            char buffer[8];
            execlp("./Consumer", "Consumer", buffer, fileSplit(encryptedFile, i, argv[2])), /* rfid call*/ , hash);
        } else {
            close(fd[i][0]);
            shmid[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
            write (fd[i][1], &shmid[i], sizeof(shmid[i]));
            close(fd[i][1]);
        }
    }

    free(encryptedFile);
    free(key);
    
    for (int i = 0; i < argv[2]; i++) {
        tempPID[i]= wait(&status);

        for (int j = 0; j <= i; j++) {
            if (tempPID[j] == pid[i]){
                pidFound = 1;
            }
        }

        if (pidFound == 1){
            sharedMemory = (int*)shmat(shmid[i], NULL, 0);

            if (*sharedMemory == 0) {
                failed(c_socket);
            } 
            
            shmctl(*sharedMemory, IPC_RMID, NULL);
        }
        pidFound = 0;
    }
    succeed(c_socket);
}


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
    send(c_socket, 0, sizeof(int), 0);
    close(c_socket);
    exit (-1);
}

void success(int c_socket) {
    send(c_socket, 1, sizeof(int), 0);
    close(c_socket);
    exit (0);
}
