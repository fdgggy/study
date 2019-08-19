#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>

/*
epoll I/O多路复用服务端程序
 */

int MAX_EVENT_COUNT = 5000;

int main() {
    printf("server start\n");
    extern int errno;

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);  //创建套接字
    if (listenfd == -1) {
        printf("create socket failed!\n");
        return 0;
    }
    printf("create socket success,listenfd:%d\n", listenfd);

    struct sockaddr_in servaddr; //地址格式描述
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;  //IPV4
    servaddr.sin_port = htons(123);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) == -1) {
        printf("bind socket addr failed!\n");
        char * mesg = strerror(errno);
        printf("errno:%d mesg:%s\n", errno, mesg);
        return 0;
    }
    printf("bind success\n");

    if (listen(listenfd, SOMAXCONN) == -1) {  //默认是128，队列长度[8,128]
        printf("listen socket failed!\n");
        return 0;
    }
    printf("listen success\n");

    //int epoll_create(int size);
    //创建一个epoll实例，从linux2.6.8开始，size参数忽略，但必须大于0
    int epfd = epoll_create(1024);
    if (epfd < 0) {
        printf("epoll create failed!\n");
        return 0;
    }
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = listenfd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event) == -1) {
        printf("attach to epoll failed\n");
        return 0;
    }

    for (;;) {
        struct epoll_event events[100];
        // printf("epoll wait start, blocking process\n");
        int count = epoll_wait(epfd, events, 20, 5000);  //阻塞，直到有事件触发
        // printf("epoll wait end, blocking process end\n");

        if (count == -1) {
            printf("listen event failed\n");
            char * mesg = strerror(errno);
            printf("errno:%d mesg:%s\n", errno, mesg);
            return 0;
        }else if (count == 0) {
            printf("listen event timeout\n");
            continue;
        }

        for (int i = 0; i < count; i++) {
            int fd = events[i].data.fd;
            int ets = events[i].events;
            if (ets & (EPOLLIN | EPOLLERR)) {
                // printf("fd:%d\n", fd);
                if (fd == listenfd) {
                    int clientfd = accept(listenfd, NULL, NULL);//监听socket返回新的fd
                    if (clientfd == -1) {
                        printf("accept failed\n");
                        continue;
                    }

                    printf("clientfd:%d\n", clientfd);

                    struct epoll_event event;
                    memset(&event, 0, sizeof(event));
                    event.events = EPOLLIN;
                    event.data.fd = clientfd;
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &event) == -1) {
                        printf("attach to epoll failed\n");
                        continue;
                    }
                }else {
                    char buff[1024];
                    memset(buff, '\0', sizeof(buff));
                    int res = read(fd, buff, 1024);
                    if (res < 0) {
                        close(fd);
                        printf("recv error\n");
                        return 0;
                    }
                    printf("recv fd:%d message:%s\n", fd, buff);
                }
            }else if (ets & EPOLLOUT) {

            }else {
                printf("unknown event\n");
            }
        }
    }

    return 0;
}
