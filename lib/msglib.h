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

typedef struct text_buffer {
    char buf[256];
    sem_t buf_empt;
    sem_t buf_full;
} *Text;

typedef struct message {
    char text[256]; // HACK: Needs to be removed later, kept only for debugging
    struct text_buffer in_text;
    char in[256];  // HACK: remove
    sem_t in_empt; // HACK: remove
    sem_t in_full; // HACK: remove
    struct text_buffer out_text;
    char out[256];  // HACK: remove
    sem_t out_empt; // HACK: remove
    sem_t out_full; // HACK: remove
    int id;
} *Message;

int msg_Init(Message msg, char shm_fd[]);

int msg_Open(Message msg, char shm_fd[]);

int msg_Send(char *text, Text buff);

int msg_Recv(char *text, Text buff);

int msg_Destroy(Message msg, char shm_fd[]);
