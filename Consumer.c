#include "Consumer.h"
/*
Arguments:
    1. shared memory name
    2. message
    3. key
*/

int main (int argc, char *argv[]) {
    if (argc != 4) {
        exit (-1);
    }

    int fd = atoi(argv[1]);
    int shmid;
    char *encrypted;
    int *answer;

    strcpy (encrypted, argv[2]);

    encrypted = decrypt(encrypted, argv[3]);


    uint32_t valread=read(fd, &shmid, sizeof(shmid));
    answer = (char*)shmat(shmid, NULL, 0);

    close(fd);
    shmdt(answer);
    exit(0);
}
