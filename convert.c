#include "convert.h"
#include <stdint.h>
#include <stdlib.h>
//converthelp defined in header
//don't mess with converthelp directly

//Converting raw bytes to hash
void char_to_ui32(char* str, uint32_t* hash){
	union conversions converthelp;
	//copy raw data into union
	for(int i=0; i<(sizeof(uint32_t)*5); i++) converthelp.str[i]=str[i];
	for(int i=0; i<5; i++) hash[i]=converthelp.val[i];
}
//pass str of size 128 or above for safety
//convert string to hash[5]
void ui32_to_char(uint32_t* hash, char* str){
	union conversions converthelp;
	for(int i=0; i<5; i++) converthelp.val[i]=hash[i];
	for(int i=0; i<(sizeof(uint32_t)*5); i++) str[i]=converthelp.str[i];
	str[sizeof(uint32_t)*5]='\0';
	//str must be sufficiently large to hold the value
}
