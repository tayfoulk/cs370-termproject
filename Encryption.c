#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

char *encrpypt(char*, char*);
void append(char*, char);
char shiftKeyUp(char, char);
char shiftKeyDown(char, char);
char *shuffle(char *);
char *decrypt(char *, char*);


char *encrypt(char *FileContents, char *key) {
  char *temp;
  char *result;
  double difference;
  char letter;

  strcpy (temp, "");
  
  for (int i; i < strlen(FileContents); i++) {
    letter = shiftKeyUp(FileContents[i], key[i % strlen(key)]);
    append (temp, letter);

    if (i % 10 == 9) {
      strcat (result, shuffle(temp));
      strcpy (temp, "");
    }
    
    difference = i;
  }
  
  int i = difference;
  
  while (i % 10 != 9) {
    i++;
    letter = shiftKeyUp('x', key[i % strlen(key)]);
    append(temp, letter);
  }    
  
  strcat (result, shuffle(temp));
  return result;  
}

void append(char *input, char add) {
    char *temp = (char *) malloc(sizeof(char) * (strlen(input) + 1));
    for (int i = 0; i < strlen(input); i ++) {
        temp[i] = input[i];
    }
    temp[strlen(input)] = add;
    free(input);
    input = temp;
}

char *shuffle(char *input) {
  char *temp;
  strcpy (temp, "");

  append(temp, input[7]);
  append(temp, input[3]);
  append(temp, input[2]);
  append(temp, input[1]);
  append(temp, input[8]);
  append(temp, input[6]);
  append(temp, input[5]);
  append(temp, input[0]);
  append(temp, input[4]);
  append(temp, input[9]);
  
  return temp;
}

char shiftKeyUp(char input, char key) {
  return 32 + (((input + key) - 32) % 94);
}

char shiftKeyDown(char input, char key) {
  int temp = input - key - 32;

  if (temp < 0) {
    temp += 94;
  }
  
  return 32 + temp;
}

char *decrypt(char *FileContents, char *key) {
  char *temp;
  char *result;
  char letter;

  strcpy (temp, "");
  
  for (int i; i < strlen(FileContents); i++) {
    letter = shiftKeyDown(FileContents[i], key[i % strlen(key)]);
    append (temp, letter);

    if (i % 10 == 9) {
      strcat (result, shuffle(temp));
      strcpy (temp, "");
    }
  }
  return result;
}
