#include <fcntl.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define SHM_FD "shmtest"

typedef struct message {
    char text[256];
    int id;
} *Message;

int main(void) {
    int fd = shm_open(SHM_FD, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(struct message));

    Message msg = mmap(NULL, sizeof(*msg), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(msg->text, "[Initialization Message]");
    msg->id = 114;

    munmap(msg, sizeof(*msg));
    return 0;
}
