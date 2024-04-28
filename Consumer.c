#include <stdio.h>
#include "Encryption.h"
#include "sha1.h"

/*
Arguments:
    1. shared memory name
    2. message
    3. key
    4. hash to compare
*/

int main (int argc, char *argv[]) {
    if (argc != 5) {
        exit (-1);
    }

    int fd = atoi(argv[1]);
    int shmid;
    char *encrypted;
    int *answer;

    strcpy (encrypted, argv[2]);

    encrypted = decrypt(encrypted, argv[3]);

    char* hash;

    sha1(encrypted, hash);

    read(fd, &shmid, sizeof(shmid));
    answer = (int*)shmat(shmid, NULL, 0);

    *answer = 0;

    if (strcmp(hash, argv[4])) {
        *answer = 1;
    }

    close(fd);
    shmdt(answer);
    exit(0);
}
