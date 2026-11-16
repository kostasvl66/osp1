#define SHM_FD "shmtest"

typedef struct message {
    char text[256];
    int id;
} *Message;
