#include "../lib/msglib.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO: Initialize semaphores here and in proc(check if sem_init works fine with already-initialized semaphores)

int main(int argc, char *argv[]) {

    int inst = atoi(argv[1]);
    printf("I am ENC instance: %d\n", inst);

    Message p1mesg = msg_Open(SHM_PENC1);

    char txt2[256] = "Initial txt value";
    while (!strcmp(txt2, "Initial txt value")) {
        msg_Recv(txt2, &p1mesg->in_text);
    }
    printf("ENC reading through SHM_PENC1: %s\n", txt2);

    // msg_Destroy(mesg, SHM_FD);
    // msg_Destroy(p1mesg, SHM_PENC1);

    return 0;
}
