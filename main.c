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

#define SHM_BLOCKSZ 1024

typedef struct shmblock {
    pthread_mutex_t mutex;
    pthread_cond_t shmsegcond;
    int done;
    int code;
    int ownerpid;
    char data[SHM_BLOCKSZ];
} shmblock;

int main()
{
//    key_t shmkey = ftok("/tmp", 'A');
//    int shmid = shmget(shmkey, 1024, 0644 | IPC_W | IPC_R);
//    if (shmid < 0) {
//        perror("shmget failed");
//    }
//    printf("shmid: %d\n", shmid);
    int shmid = 327681;

    void* shmptr = shmat(shmid, (void*)0, SHM_RDONLY);

    printf("shared memory content: %s\n", (char*)shmptr);

//    message * m = shmptr+strlen(shmptr)+1;
//    printf("m.x: %d, m.y: %c, m.z: %li\n", m->x, m->y, m->z);

    shmblock * sb = (shmblock*)shmptr;
    printf("sb.done: %d, sb.code: %d, sb.data: %s\n", sb->done, sb->code, sb->data);
}