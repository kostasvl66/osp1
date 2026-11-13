#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define O_PERMS O_CREAT | O_RDWR
#define S_PERMS S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

#define SHM_FD "shmtest"

int main(void) {
    printf("Starting main\n");

    char *msg = "testing";

    // Opening shared memory descriptor
    int fd = shm_open(SHM_FD, O_PERMS, S_PERMS);
    if (fd < 0) {
        printf("shm_open failure\n");
    }

    shm_unlink(SHM_FD);

    return 0;
}
