#include "../lib/msglib.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    printf("Writer Process:");

    char *test_msg = "hello world!";

    int fd = shm_open(SHM_FD, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("shm open error");
    }

    ftruncate(fd, sizeof(struct message));

    Message msg = mmap(NULL, sizeof(*msg), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (msg == MAP_FAILED) {
        perror("mmap error");
    }
    close(fd);

    msg->id = 100;
    strcpy(msg->text, test_msg);

    printf("test message is: %s\n", msg->text);

    // if (shm_unlink(SHM_FD)) {
    //     perror("unlink error");
    // }

    munmap(msg, sizeof(*msg));

    return 0;
}
