#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define SHM_FD "shmtest"
#define SEM_EMPT "/esem"
#define SEM_FULL "/fsem"

typedef struct message {
    char text[256];
    int id;
} *Message;
