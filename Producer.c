#include "Producer.h"

int main (int argc, char *argv[]) {
  pid_t pid[4];
  int status;
  int fd[4][2];
  int shmid[4];
  int i = 0;
  
  while(true) {
    pipe(fd[i]);
  
    pid[i] = fork();
    
    if (pid[i] < 0) {
      exit(-1);
    } else if (pid[i] == 0) {
      char buffer[8];
      execlp("./Consumer", "Consumer", buffer, fileSplit(), // rfid call, // hash to compare);
    } else {
      close(fd[i][0]);
      shmid[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
      write (fd[i][1], &shmid[i], sizeof(shmid[i]));
      close(fd[i][1]);
    }
    i++;
  }
  
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



char *fileSplit() {

}

void failed () {

}

void success() {

}