#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

char *encrypt(char*, char*);
char* append(char*, char);
char shiftKeyUp(char, char);
char shiftKeyDown(char, char);
char *shuffle(char *);
char *decrypt(char *, char*, int);
