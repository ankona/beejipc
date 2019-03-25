#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <pthread.h>

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
    char data[SHM_BLOCKSZ];
} shmblock;

int main()
{
    key_t shmkey = ftok("/tmp", 'A');
    int shmid = shmget(shmkey, sizeof(shmblock), 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
    }
    printf("shmid: %d\n", shmid);

    char* shmptr = shmat(shmid, (void*)0, 0);

    const char * msg = "this is a test shared message.";
    strcpy(shmptr, msg);

//    message m;
//    m.x = 11;
//    m.y = 'Y';
//    m.z = 111222333444555;

    shmblock sb;
    sb.done=1;
    sb.code=0;
    strcpy(sb.data, "foo fighters");

    memcpy(shmptr, &sb, sizeof(shmblock));

//    memcpy(shmptr+strlen(msg)+1, &m, sizeof(m));

//    int delout = shmctl(shmid, IPC_RMID, NULL);
//    if (delout < 0) {
//        printf("shmctl->IPC_RMID fail.");
//    }
//    printf("delout: %d\n", delout);

    return 0;

}