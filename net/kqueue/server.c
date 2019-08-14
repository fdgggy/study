#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/event.h>
#include <stdio.h>

/*
kqueue I/O多路复用服务端程序
 */

int MAX_EVENT_COUNT = 5000;

int main() {
    printf("server start\n");

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
        return 0;
    }
    printf("bind success\n");

    if (listen(listenfd, SOMAXCONN) == -1) {  //默认是128，队列长度[8,128]
        printf("listen socket failed!\n");
        return 0;
    }
    printf("listen success\n");

    int kq = kqueue();
//     struct kevent { 
//      uintptr_t ident;       /* 事件 ID */ 
//      short     filter;       /* 事件过滤器 */ 
//      u_short   flags;        /* 行为标识 */ 
//      u_int     fflags;       /* 过滤器标识值 */ 
//      intptr_t  data;         /* 过滤器数据 */ 
//      void      *udata;       /* 应用透传数据 */ 
//  }; 
// 在一个 kqueue 中，{ident, filter} 确定一个唯一的事件。
//EV_SET(&kev, ident, filter, flags, fflags, data, udata);
    struct kevent changes;
    //初始化时间结构体
    EV_SET(&changes, listenfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    //将事件附加到kqueue
    //kevent 提供向内核注册/反注册事件和返回就绪事件或错误事件
    if (kevent(kq, &changes, 1, NULL, 0, NULL) == -1) {
        printf("attach to kqueue failed\n");
        return 0;
    }

    for (;;) {
        struct kevent events[MAX_EVENT_COUNT];
        printf("kevent recevive start, blocking process\n");
        int count = kevent(kq, NULL, 0, events, MAX_EVENT_COUNT, NULL);  //阻塞，直到有事件触发
        printf("kevent recevive end, blocking process end\n");
        

        if (count == -1) {
            printf("listen event failed\n");
            return 0;
        }

        for (int i = 0; i < count; i++) {
            int sock = events[i].ident;
            int length = events[i].data;

            if (sock == listenfd) {
                for (int j = 0; j < length; j++) {
                    int clientfd = accept(listenfd, NULL, NULL);//监听socket返回新的fd
                    if (clientfd == -1) {
                        printf("accept failed\n");
                        continue;
                    }

                    struct kevent changes;
                    //初始化时间结构体
                    EV_SET(&changes, clientfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                    //将事件附加到kqueue
                    //kevent 提供向内核注册/反注册事件和返回就绪事件或错误事件
                    if (kevent(kq, &changes, 1, NULL, 0, NULL) == -1) {
                        printf("attach to kqueue failed\n");
                        continue;
                    }
                }
            }else {
                char buff[1024];
                memset(buff, '\0', sizeof(buff));
                int res = recv(sock, buff, length, 0);
                if (res < 0) {
                    close(sock);
                    printf("recv error\n");
                    continue;
                }
                printf("recv message:%s\n", buff);
            }
        }
    }

    return 0;
}
