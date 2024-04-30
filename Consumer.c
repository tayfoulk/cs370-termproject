#include "Consumer.h"
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
    //hold hash
    uint32_t hash[5];

    sha1(encrypted, hash);
    char hash_str[128];
    //store hashval in hash_str
    ui32_to_char(hash, hash_str);

    uint32_t valread=read(fd, &shmid, sizeof(shmid));
    answer = (int*)shmat(shmid, NULL, 0);

    *answer = 0;
    
    //compare hash_str to argv[4], the provided hash
    if (strcmp(hash_str, argv[4])) {
        *answer = 1;
    }

    close(fd);
    shmdt(answer);
    exit(0);
}
