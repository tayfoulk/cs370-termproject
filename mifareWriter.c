#include "mifareWriter.h"
  
void write_to_mifare_classic(char* encrypted_message){
    
    execl("/usr/bin/mifare-classic-write-ndef", "-y", "-i", encrypted_message, (char *)NULL);
};
