#include "../lib/msglib.h"
#include "stdlib.h"
#include <semaphore.h>
#include <string.h>

Message msg_Init(char shm_fd[]) {
    int fd = shm_open(shm_fd, O_RDWR, 0666);
    ftruncate(fd, sizeof(struct message));
    Message msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    return msg;
}

Message msg_Open(char shm_fd[]) {
    int fd = shm_open(shm_fd, O_RDWR, 0666);
    Message msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    return msg;
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
