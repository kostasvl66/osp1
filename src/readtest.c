#include "../lib/msglib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    printf("Reader Process:");

    int fd = shm_open(SHM_FD, O_RDONLY, 0666);
    if (fd < 0) {
        perror("shm error");
    }

    Message msg = mmap(NULL, sizeof(*msg), PROT_READ, MAP_SHARED, fd, 0);
    if (msg == MAP_FAILED) {
        perror("mmap error");
    }
    close(fd);

    printf("Message read is: %s, with id: %d\n", msg->text, msg->id);

    munmap(msg, sizeof(*msg));
    if (shm_unlink(SHM_FD) < 0) {
        perror("unlink error");
    }

    return 0;
}
