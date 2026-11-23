#include "../lib/msglib.h"

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

int msg_Destroy(Message msg, char shm_fd[]) {
    munmap(msg, sizeof(*msg));
    shm_unlink(shm_fd);

    return 0;
}
