#include "Producer.h"


int main (int argc, char *argv[]) {
    pid_t pid[4];
    int status;
    int fd[argv[2]][2];
    int shmid[argv[2]];
    int i = 0;

    char *encryptedFile; // = file received from server
    char *key; // = key recieved from rfid reader

    for (int i = 0; i < argv[2], i++;) {
        pipe(fd[i]);

        pid[i] = fork();

        if (pid[i] < 0) {
            exit(-1);
        } else if (pid[i] == 0) {
            char buffer[8];
            execlp("./Consumer", "Consumer", buffer, fileSplit(encryptedFile, i, argv[2])), // rfid call, // hash to compare);
        } else {
            close(fd[i][0]);
            shmid[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
            write (fd[i][1], &shmid[i], sizeof(shmid[i]));
            close(fd[i][1]);
        }
    }

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
                failed();
            } else {
                succeed();
            }
            shmctl(*sharedMemory, IPC_RMID, NULL);
        }
        pidFound = 0;
    }
}


char *fileSplit(char *input, int pos, int size) {
    int segment = trunc(0.5 + (strlen(input) / size));
    char *result = malloc(sizeof(char) * segment);

    for (int i = pos; i < segment; i++) {
        result[i - pos] = input[i];
    }

    return (result);
}

void failed (int c_socket) {
    // send failure code
    exit (-1);
}

void success(int c_socket) {
    // send success code
    exit (0);
}
