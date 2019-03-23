#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>

typedef struct message {
    int x;
    char y;
    long z;
} message;


int main()
{
    key_t shmkey = ftok("/tmp", 'A');
    int shmid = shmget(shmkey, 1024, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
    }
    printf("shmid: %d\n", shmid);

    char* shmptr = shmat(shmid, (void*)0, 0);

    const char * msg = "this is a test shared message.";
    strcpy(shmptr, msg);

    message m;
    m.x = 11;
    m.y = 'z';
    m.z = 111222333444555;

    memcpy(shmptr+sizeof(msg)+1, &m, sizeof(m));

    return 0;

}