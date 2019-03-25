#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/msg.h>
#include <string.h>

void sigint_handler(int sig)
{
    write(0, "Ahhh! SIGINT!\n", 14);
}
typedef struct qmsg {
    long mtype;
    char name[100];
} qmsg;

typedef struct req {
    int shmid;
    char path[1024];
} request;

typedef struct qmsg2 {
    long mtype;
    request request;
} qmsg2;

int main() {

    key_t qkey = ftok("/tmp", 'C');
    if (qkey == -1)
    {
        printf("errno: %i\n", errno);
        printf("EACCES: %i\n", EACCES);
        printf("EINVAL: %i\n", EINVAL);
        printf("ELOOP: %i\n", ELOOP);
        printf("ENAMETOOLONG: %i\n", ENAMETOOLONG);
        printf("ENOENT: %i\n", ENOENT);
        printf("ENOTDIR: %i\n", ENOTDIR);

    }
    int msg_qid = msgget(qkey, 0666 | IPC_CREAT);
    printf("msg_qid: %i\n", msg_qid);
    printf("qkey: %i\n", qkey);

    /* qmsg outmsg;
    outmsg.mtype = 1;
    strcpy(outmsg.name, "Chris"); */


    qmsg2 outmsg;
    outmsg.mtype = 1;

    request req;
    strcpy(req.path, "/tmp/test");
    req.shmid = 1;
    outmsg.request = req;

    int sendout = msgsnd(msg_qid, (void*)&outmsg, sizeof(qmsg2), 0);

    printf("sendout is: %d\n", sendout);


    /* qmsg recvmsg;
    int recvout = msgrcv(msg_qid, &recvmsg, sizeof(msg.name), 1, 0);*/

//    qmsg2 recvmsg;
//    int recvout = msgrcv(msg_qid, &recvmsg, sizeof(qmsg2), 1, 0);
//    printf("recvout: %s\n", recvmsg.request.path);


    // msgctl(msg_qid, IPC_RMID, NULL);
    return 0;

}