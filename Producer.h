#include <stdio.h>
#include <math.h>

//shared memory
#include <sys/shm.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/socket.h>

// our headers
#include "Encryption.h"
#include "convert.h"
#include "sha1.h"
#include "socket_conn.h"
#include "mifareReader.c"
