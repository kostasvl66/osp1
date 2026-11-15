#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
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

// TODO: Implement Reader/Writer thread functinality, with RW-lock
// Implement semaphores for mapping P1's writer to P2's reader, and the opposite

void *write_routine(void *arg) {
    Message tosend = (Message)arg;
    int i = 0;
    while (strcmp(tosend->text, "TERM") && (i < 5)) {
        printf("Writer: Not terminating\n");
        i++;
    }
    printf("Writer: Terminating\n");

    return NULL;
}

void *read_routine(void *arg) {

    Message sent = (Message)arg;
    printf("Reader: Message text is: %s with id: %d\n", sent->text, sent->id);

    return NULL;
}

int main(void) {
    printf("Starting main\n");
    pthread_t thread_handle[2];
    int x = 0;

    // Initializing shared memory
    int fd = shm_open(SHM_FD, O_RDWR, 0666);
    Message msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    // Start reader thread
    pthread_create(&thread_handle[1], NULL, read_routine, (void *)msg);
    pthread_join(thread_handle[1], NULL);

    // Start writer thread
    pthread_create(&thread_handle[0], NULL, write_routine, (void *)msg);
    pthread_join(thread_handle[0], NULL);

    munmap(msg, sizeof(*msg));
    shm_unlink(SHM_FD);
    return 0;
}
