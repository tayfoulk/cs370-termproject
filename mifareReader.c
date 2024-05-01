#include "mifareReader.h"

void read_from_mifare_classic(){
    execl("/usr/bin/mifare-classic-read-ndef", "-y", "-o", "./readdata.txt", (char *)NULL);
};
