#include "../lib/msglib.h"
#include "stdlib.h"
#include <semaphore.h>
#include <string.h>

int msg_Init(Message msg, char shm_fd[]) {
    int fd = shm_open(shm_fd, O_RDWR, 0666);
    ftruncate(fd, sizeof(struct message));
    msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    return 0;
}

int msg_Open(Message msg, char shm_fd[]) {
    int fd = shm_open(shm_fd, O_RDWR, 0666);
    msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    return 0;
}

int msg_Send(char *text, Text buff) {
    // sem_wait(&buff->buf_empt);
    strcpy(buff->buf, text);
    // sem_post(&buff->buf_full);

    return 0;
}

int msg_Recv(char *text, Text buff) {
    // sem_wait(&buff->buf_full);
    strcpy(text, buff->buf);
    // sem_post(&buff->buf_empt);

    return 0;
}

int msg_Destroy(Message msg, char shm_fd[]) {
    munmap(msg, sizeof(*msg));
    shm_unlink(shm_fd);

    return 0;
}
