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

#define SHM_FD "msg_shm" // HACK: Needs to be removed later, kept only for debugging
#define SHM_PENC1 "p1enc1_shm"
#define SHM_PENC2 "p2enc2_shm"
#define SHM_ENC1CH "enc1ch_shm"
#define SHM_ENC2CH "enc2ch_shm"

// TODO: Add in/out functionality to struct for more organized IPC
typedef struct message {
    char text[256]; // HACK: Needs to be removed later, kept only for debugging
    char in[256];
    char out[256];
    sem_t in_sem;
    sem_t out_sem;
    int id;
} *Message;
