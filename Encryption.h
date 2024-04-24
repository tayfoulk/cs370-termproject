#include <stdio.h>
#include <math.h>

char *encrypt(char *FileContents, char *key) {
  char *temp;
  char *result;

  strcpy (temp, "");
  
  for (int i; i < strlen(FileContents); i++) {
    if (i % 10 != 9) {
      strcat (temp, FileContents[i] + key[i % strlen(key);
    } else {
      strcat (result, shuffle(temp));
      strcpy (temp, "");
    }
  }
}

char *shuffle(char *input) {
  
}

char *decrypt(char *FileContents, char *key) {

}
