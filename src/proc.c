#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_FD "shmtest"

int main(void) {
    printf("Starting main\n");

    // TODO: Implement Reader/Writer thread functinality, with RW-lock
    // Implement semaphores for mapping P1's writer to P2's reader, and the opposite

    return 0;
}
