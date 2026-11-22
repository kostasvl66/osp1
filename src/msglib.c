#include "../lib/msglib.h"

int msg_Init(Message msg) {
    int fd = shm_open(SHM_FD, O_RDWR, 0666);
    ftruncate(fd, sizeof(struct message));
    msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    return 0;
}

int msg_Open(Message msg) {
    int fd = shm_open(SHM_FD, O_RDWR, 0666);
    msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    return 0;
}

int msg_Destroy(Message msg) {
    munmap(msg, sizeof(*msg));
    shm_unlink(SHM_FD);

    return 0;
}
