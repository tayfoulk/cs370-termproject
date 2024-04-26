#include <stdio.h>
#include <math.h>

char *encrypt(char *FileContents, char *key) {
  char *temp;
  char *result;
  double difference;
  char letter;

  strcpy (temp, "");
  
  for (int i; i < strlen(FileContents); i++) {
    letter = ((Filecontents[i] + key[i % strlen(key)]) - 32) % 94;
    strcat (temp, letter);

    if (i % 10 == 9) {
      strcat (result, shuffle(temp));
      strcpy (temp, "");
    }
    
    difference = i;
  }
  
  int i = difference;
  
  while (i % 10 != 9) {
    i++;
    letter = (("x" + key[i % strlen(key)]) - 32) % 94;
    strcat(temp, letter);
  }    
  
  strcat (result, shuffle(temp));
  return result;  
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
