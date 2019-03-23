#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <string.h>

struct message {
    int x;
    char y;
    long z;
};


int main() {
    int unlinkout = mq_unlink("/myq");
    printf("unlinkout %d.\n", unlinkout);
    if (unlinkout < 0) {
        perror("unlink failure.");
    }

    struct mq_attr attr;


    attr.mq_flags = 0;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = sizeof(struct message);
    attr.mq_curmsgs = 0;

    mqd_t qid = mq_open("/myq", O_RDWR | O_CREAT, 0666, &attr);

    printf("qid: %d\n", qid);
    if (qid < 0) {
        perror("server: mq_open");
    }

    unsigned int priority = 100;

    struct message msgout;
    msgout.x = 17;
    msgout.y = 'q';
    msgout.z = -2;

    int sendout = mq_send(qid, (char*)&msgout, sizeof(struct message), 0);
    mq_close(qid);
    printf("sendout: %d\n", sendout);
    if (sendout < 0) {
        perror("send fail.");
    }

    struct message msgin;
    mqd_t mqd = mq_open("/myq", O_RDONLY);
    int recvout = mq_receive(mqd, (char*)&msgin, sizeof(struct message), NULL);
    printf("recvout: %d\n", recvout);
    if (recvout < 0) {
        perror("receive fail.\n");
    }

    printf("msgin: %i-%d-%li\n", msgin.x, msgin.y, msgin.z);

    mq_close(mqd);
    return 0;

}