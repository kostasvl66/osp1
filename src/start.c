#include "../lib/msglib.h"
#include <fcntl.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

int main(void) {
    int fd = shm_open(SHM_FD, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(struct message));

    Message msg = mmap(NULL, sizeof(*msg), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(msg->text, "[Initialization Message]");
    msg->id = 114;

    munmap(msg, sizeof(*msg));
    return 0;
}
