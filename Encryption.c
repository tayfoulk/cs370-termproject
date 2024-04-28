#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

char *encrpypt(char*, char*);
char* append(char*, char);
char shiftKeyUp(char, char);
char shiftKeyDown(char, char);
char *shuffle(char *);
char *decrypt(char *, char*);


char *encrypt(char *FileContents, char *key) {
  char *temp = malloc(sizeof(char));
  char *result = malloc(sizeof(char) * (strlen(FileContents) + 10));
  int difference;
  char letter;

  strcpy (temp, "");


  for (int i = 0; i < strlen(FileContents); i++) {
    letter = shiftKeyUp(FileContents[i], key[(i % strlen(key))]);
    temp = append (temp, letter);

    if (i % 10 == 9) {
      strcat (result, shuffle(temp));

      free(temp);
      temp = malloc(sizeof(char));
      strcpy (temp, "");
    }

    difference = i;
  }

  int i = difference;


  while (i % 10 != 9) {
    letter = shiftKeyUp('~', key[(1 + i) % strlen(key)]);
    temp = append(temp, letter);
    i++;

  }

  strcat (result, shuffle(temp));
  return result;
}

char* append(char *input, char add) {
    char *temp = malloc(sizeof(char) * (strlen(input) + 2));
    strcpy (temp, input);
    temp[strlen(input)] = add;
    temp[strlen(input) + 1] = '\0';

    free(input);
    return temp;
}

char *shuffle(char *input) {
  char *temp = malloc(sizeof(char) * 10);
  strcpy (temp, "");

  temp = append(temp, input[7]);
  temp = append(temp, input[3]);
  temp = append(temp, input[9]);
  temp = append(temp, input[1]);
  temp = append(temp, input[8]);
  temp = append(temp, input[6]);
  temp = append(temp, input[5]);
  temp = append(temp, input[0]);
  temp = append(temp, input[4]);
  temp = append(temp, input[2]);

  return temp;
}

char shiftKeyUp(char input, char key) {
  return 32 + (((input + key) - 64) % 95);
}

char shiftKeyDown(char input, char key) {

  int temp = input - key;

  if (temp < 0) {
    temp += 95;
  }
  return (char)(32 + temp);
}

char *decrypt(char *FileContents, char *key) {
  char *temp = malloc(sizeof(char));
  char *temp2 = malloc(sizeof(char));
  char *result = malloc(sizeof(char) * (strlen(FileContents) + 10));
  char letter;
  int pos = 0;

  strcpy (temp, "");
  strcpy (temp2, "");

  for (int i = 0; i < strlen(FileContents); i++) {
    temp = append (temp, FileContents[i]);

    if (i % 10 == 9) {
      temp = shuffle(temp);

      for (int j = 0; j < 10; j++) {
        temp2 = append(temp2, shiftKeyDown(temp[j], key[(pos + j) % strlen(key)]));
      }
      pos+=10;


      strcat (result, temp2);

      free(temp);
      free(temp2);
      temp = malloc(sizeof(char));
      temp2 = malloc(sizeof(char));
      strcpy (temp, "");
      strcpy (temp2, "");
    }
  }
  return result;
}
