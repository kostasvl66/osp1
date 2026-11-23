#include "../lib/msglib.h"
#include <bits/pthreadtypes.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define ENCPATH "/home/kostas/Desktop/SCHOOL/OS/p1/lib/enc"

void *init_enc(void *arg) {
    int *x = (int *)arg;
    printf("Initializing ENC: %d\n", *x);
    int y;
    char strx[2];
    switch (y = fork()) {
    case 0:
        sprintf(strx, "%d", *x);
        execl(ENCPATH, ENCPATH, strx, NULL);
    default:
        wait(NULL);
    }
    printf("Shutting down ENC: %d\n", *x);

    x = NULL;
    return NULL;
}

int main(void) {

    int fd = shm_open(SHM_FD, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(struct message));
    Message msg = mmap(NULL, sizeof(*msg), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    strcpy(msg->text, "[Initialization Message]");
    msg->id = 114;

    munmap(msg, sizeof(*msg));

    int p1fd = shm_open(SHM_PENC1, O_CREAT | O_RDWR, 0666);
    ftruncate(p1fd, sizeof(struct message));
    Message p1mesg = mmap(NULL, sizeof(*p1mesg), PROT_WRITE | PROT_READ, MAP_SHARED, p1fd, 0);
    close(p1fd);

    // TODO: Initialize ENC1 and ENC2 using 2 parallel threads
    pthread_t thread_handle[2];
    int enc_inst[2];

    // Starting init threads for ENC1 and ENC2
    for (long i = 0; i < 2; i++) {
        enc_inst[i] = i + 1;
        pthread_create(&thread_handle[i], NULL, init_enc, (void *)&enc_inst[i]);
    }

    // Joining init threads for ENC1 and ENC2
    pthread_join(thread_handle[0], NULL);
    pthread_join(thread_handle[1], NULL);

    printf("Start terminates\n");

    return 0;
}
