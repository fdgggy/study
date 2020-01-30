#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
/*
    fork调用1次，但返回2次。子进程返回值是0，父进程返回值是新建子进程的进程ID。
    子进程是父进程的副本。子进程获得父进程数据空间，堆和栈的副本，并不共享这些存储空间部分。只共享正文段,即代码段。
*/

int globvar = 6;
char buf[] = "a write to stdout]n";

int main() {
    int var;
    pid_t pid;
    var = 88;

    pid = fork();
    if (pid < 0) {
        printf("fork error\n");
    }else if (pid == 0) {
        printf("child process\n");
        globvar++;
        var++;
        sleep(1);
    }else {
        printf("parent process\n");
    }

    printf("pid:%ld, glob:%d, var:%d\n", (long)getpid(), globvar, var);
    /*
    child process
    pid:6072, glob:7, var:89
    parent process
    pid:6071, glob:6, var:88
    */
    waitpid(pid, NULL, 0);

    return 0;
}