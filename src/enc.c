#include "../lib/msglib.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO: Initialize semaphores here and in proc(check if sem_init works fine with already-initialized semaphores)

int main(int argc, char *argv[]) {

    int inst = atoi(argv[1]);
    printf("I am ENC instance: %d\n", inst);

    int fd = shm_open(SHM_FD, O_RDWR, 0666);
    Message mesg = mmap(NULL, sizeof(*mesg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    // int p1fd = shm_open(SHM_PENC1, O_RDWR, 0666);
    // Message p1mesg = mmap(NULL, sizeof(*p1mesg), PROT_WRITE | PROT_READ, MAP_SHARED, p1fd, 0);
    // close(p1fd);

    Message p1mesg = msg_Open(SHM_PENC1);

    char txt[256];
    msg_Recv(txt, &mesg->in_text);
    printf("ENC reading through SHM_FD: %s\n", txt);

    char txt2[256] = "Initial txt value";
    while (!strcmp(txt2, "Initial txt value")) {
        msg_Recv(txt2, &p1mesg->in_text);
    }
    printf("ENC reading through SHM_PENC1: %s\n", txt2);

    // msg_Destroy(mesg, SHM_FD);
    // msg_Destroy(p1mesg, SHM_PENC1);

    return 0;
}
