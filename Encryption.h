#include <stdio.h>
#include <math.h>

char *encrypt(char *FileContents, char *key) {
  char *temp;
  char *result;

  strcpy (temp, "");
  
  for (int i; i < strlen(FileContents); i++) {
    if (i % 10 != 9) {
      strcat (temp, FileContents[i] + key[i % strlen(key)];
    } else {
      strcat (temp, FileContents[i] + key[i % strlen(key)];
      strcat (result, shuffle(temp));
      strcpy (temp, "");
    }
  }

  for (int i; i < 
}

char *shuffle(char *input) {
  char *temp;
  strcpy (temp, "");

  strcat(temp, input[7]);
  strcat(temp, input[3]);
  strcat(temp, input[2]);
  strcat(temp, input[1]);
  strcat(temp, input[8]);
  strcat(temp, input[6]);
  strcat(temp, input[5]);
  strcat(temp, input[0]);
  strcat(temp, input[4]);
  strcat(temp, input[9]);

}

char *decrypt(char *FileContents, char *key) {

}
