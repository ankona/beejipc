#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int rv;

    switch(pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            printf("CHILD: this is the child process.\n");
            printf("CHILD: my pid is %d.\n", pid);
            printf("CHILD: my parent pid is %d\n", getpid());
            printf("CHILD: enter my exit status: ");
            scanf(" %d", &rv);
            printf("CHILD: I'm outta here!\n");
            exit(rv);
        default:
            printf("PARENT: this is the parent.\n");
            printf("PARENT: my pid is %d.\n", getpid());
            printf("PARENT: my childs pid is %d\n", pid);
            printf("PARENT: now i'm waiting for my child to exit...\n");
            wait(&rv);
            printf("PARENT: my child's exit status is %d\n", WEXITSTATUS(rv));
            printf("PARENT: i'm outta here!\n");
    }
}