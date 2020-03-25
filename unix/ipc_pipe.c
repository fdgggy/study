#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int fd[2];
    char line[128];

    if (pipe(fd) < 0) {  //fd[0]为读端，fd[1]为写端
        printf("create pipe failed\n");
        return -1;
    }
    if ((pid = fork()) < 0) {
        printf("create process failed\n");
        return -1;
    }else if (pid > 0) {  //parent  父进程->子进程的管道
        close(fd[0]); //关闭读端
        write(fd[1], "hello world\n", 12);
    }else if (pid == 0) {
        close(fd[1]); //关闭写端
        int n = read(fd[0], line, 128);
        printf("read:%s", line);
    }


    return 0;
}


