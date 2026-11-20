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

#define SHM_FD "msg_shm"
#define SEM_FULL "/sem_full"
#define SEM_EMPT "/sem_empty"

// TODO: Add in/out functionality to struct for more organized IPC
typedef struct message {
    char text[256]; // HACK: Needs to be removed later, kept only for debugging
    char in[256];
    char out[256];
    int id;
} *Message;
