#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct message {
    int x;
    char y;
    long z;
} message;

int main()
{
    key_t shmkey = ftok("/tmp", 'A');
    int shmid = shmget(shmkey, 1024, 0644 | IPC_W);
    if (shmid < 0) {
        perror("shmget failed");
    }
    printf("shmid: %d\n", shmid);

    void* shmptr = shmat(shmid, (void*)0, 0);

    printf("shared memory content: %s\n", (char*)shmptr);

    message * m = shmptr+sizeof(shmptr)+1;
    printf("m.x: %d, m.y: %d, m.z: %li\n", m->x, m->y, m->z);
}