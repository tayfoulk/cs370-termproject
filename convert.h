#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED
#include <stdint.h>

union conversions{
	uint32_t val[5];
	char str[128];
};
//convert hash to str
extern void ui32_to_char(uint32_t*, char*);
//convert str to hash[5]
extern void char_to_ui32(char*, uint32_t*);
#endif
