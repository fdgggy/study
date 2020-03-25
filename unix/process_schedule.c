#include <stdio.h>
#include <sys/syslimits.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

unsigned long long count;
struct timeval end;

int main(int argc, char *argv[]) {
    pid_t pid;
    char *s;
    int nzero, ret;
    int adj = 0;
    nzero = NZERO;

    if (argc == 2) {
        adj = strtol(argv[1], NULL, 10);
    }

    pid = fork();
    if (pid < 0) {
        printf("fork error\n");
    }else if (pid == 0) {
        s = "child";
        printf("current nice value in child is %d, adjusting by %d\n", nice(0)+nzero, adj);
        if ((ret = nice(adj)) == -1) {
            printf("child set scheduling priority error\n");
        }
        printf("now child nice value is %d\n", ret);
    }else {
        s = "parent";
        printf("current nice value in parent is %d\n", nice(0)+nzero);
    }

    return 0;
}

