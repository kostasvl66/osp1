#include "../lib/msglib.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int inst = atoi(argv[1]);
    printf("I am ENC instance: %d\n", inst);

    int fd = shm_open(SHM_FD, O_RDWR, 0666);
    Message mesg = mmap(NULL, sizeof(*mesg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    printf("ENC reading: %s\n", mesg->text);

    return 0;
}
