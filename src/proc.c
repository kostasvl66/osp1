#include "../lib/msglib.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

// TODO: Implement Reader/Writer thread functinality, with RW-lock
// Implement semaphores for mapping P1's writer to P2's reader, and the opposite

void *write_routine(void *arg) {
    Message tosend = (Message)arg;
    // int i = 0;
    // char *st;
    // while (strcmp(tosend->text, "TERM") && (i < 5)) {
    //     scanf("%s", st);
    //     printf("Writer: Wrote: %s\n", st);
    //     // i++;
    // }

    strcpy(tosend->text, "Writer writes writingly");

    printf("Writer: Terminating\n");

    return NULL;
}

void *read_routine(void *arg) {

    Message sent = (Message)arg;
    // int i = 0;
    // while (strcmp(sent->text, "TERM") && (i < 5)) {
    //     printf("Reader: Message text is: %s with id: %d\n", sent->text, sent->id);
    //     // i++;
    // }
    printf("Reader: Terminating\n");

    return NULL;
}

int main(int argc, char *argv[]) {
    printf("Starting main\n");

    if (argc != 2) {
        perror("Program must be called as ./proc <instance>");
        return 1;
    }

    int program_instance = atoi(argv[1]);

    pthread_t thread_handle[2];
    int x = 0;

    // Initializing shared memory
    int fd = shm_open(SHM_FD, O_RDWR, 0666);
    Message msg = mmap(NULL, sizeof(*msg), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    // Start reader/writer threads
    pthread_create(&thread_handle[1], NULL, read_routine, (void *)msg);
    pthread_create(&thread_handle[0], NULL, write_routine, (void *)msg);

    // Join reader/writer threads
    pthread_join(thread_handle[1], NULL);
    pthread_join(thread_handle[0], NULL);

    // munmap(msg, sizeof(*msg));
    // shm_unlink(SHM_FD);
    return 0;
}
