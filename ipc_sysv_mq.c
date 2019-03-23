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

int main() {

    key_t qkey = ftok("/tmp", 43);
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

    qmsg msg;
    msg.mtype = 1;
    strcpy(msg.name, "Chris");

    int sendout = msgsnd(msg_qid, (void*)&msg, sizeof(msg.name), 0);

    printf("sendout is: %d\n", sendout);


    qmsg recvmsg;
    int recvout = msgrcv(msg_qid, &recvmsg, sizeof(msg.name), 1, 0);

    printf("recvout: %s\n", recvmsg.name);

//    msgctl(65536, IPC_RMID, NULL);
//    msgctl(65537, IPC_RMID, NULL);
//    msgctl(65538, IPC_RMID, NULL);
//    msgctl(65539, IPC_RMID, NULL);
        msgctl(msg_qid, IPC_RMID, NULL);
    return 0;

}