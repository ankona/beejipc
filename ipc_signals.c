#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig)
{
    write(0, "Ahhh! SIGINT!\n", 14);
}
int main() {
    void sigint_handler(int sig);

    char s[200];
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Enter a string: \n");

    if (fgets(s, sizeof s, stdin) == NULL)
        perror("fgets");
    else
        printf("you entered: %s\n", s);

    return 0;

}