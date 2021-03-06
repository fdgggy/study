#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    printf("server start\n");
    int listenfd;

    //int socket(int domain, int type, int protocol);
    //创建一个通信端点并返回一个引用该端点的文件描述符
    //@domain(协议域),用于通信的协议簇
    //AF_UNIX      Local communication 
    //AF_INET      IPv4 Internet protocols
    //AF_INET6     IPv6 Internet protocols
    //@type 套接字指示类型，制定通信的语义
    //SOCK_STREAM 有序，可靠，双向，基于连接的字节流   TCP
    //SOCK_DGRAM 数据报,无连接，不可靠，具有固定最大长度  UDP
    //@protocol 特定协议，只有一个协议指定填0
    listenfd = socket(AF_INET, SOCK_STREAM, 0);  //创建套接字
    if (listenfd == -1) {
        printf("create socket failed!\n");
        return 0;
    }
    printf("create socket success,listenfd:%d\n", listenfd);
    //int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen); 为套接字分配名称
    //套接字创建后保存在一个名字空间但并没有地址分配给他，bind通过addr参数分配地址给sockfd所引用的套接字

	int flag = fcntl(listenfd, F_GETFL, 0);
	if ( -1 == flag ) {
        printf("get flag failed!\n");
		return 0;
	}
    //源码：https://my.oschina.net/alchemystar/blog/1791017
    //设置为非阻塞后，Accept一个文件描述符时如果没有新的连接就直接返回，并不阻塞, read,recv文件描述符都不阻塞，直接返回
	fcntl(listenfd, F_SETFL, flag | O_NONBLOCK);


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

    //监听套接字上的链接
    //@sockfd 引用SOCK_STREAM/SOCK_SEQPACKET类型套接字的文件描述符
    //@backlog 挂起连接的队列的最大长度, ***ddos攻击有关
    //int listen(int sockfd, int backlog);
    if (listen(listenfd, SOMAXCONN) == -1) {  //默认是128，队列长度[8,128]
        printf("listen socket failed!\n");
        return 0;
    }
    printf("listen success\n");

    //接受套接字上的链接
    //@sockfd 监听套接字，通过socket创建，bind到本地地址，listen监听的sockfd
    //@addr 客户端协议地址
    //@addrlen 地址长度
    //默认阻塞，也可以指定为非阻塞。accept成功，返回值是由内核生成的一个全新描述符，代表与此客户端的tcp链接,称为已连接套接字
    //注意：sockfd为监听套接字，返回值为已连接套接字。一个服务器通常仅创建一个监听套接字，在服务器生命周期
    //一直存在，内核为每个连接的客户端创建一个已连接套接字(TCP3路握手完成后)
    //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    int clientfd;
    struct sockaddr_in cliaddr;
	socklen_t clilen;
	clilen = sizeof(cliaddr);

    printf("accept ready\n");
    for (;;) {
        //循环去全连接队列中获取已成功的连接
        clientfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        if (clientfd == -1) {
            // printf("accept socket failed!\n");
            continue;
        }
        printf("accept success, clientfd:%d\n", clientfd);

        if (fork() == 0) {
            //从一个socket接收消息,如果sockfd无消息，会一直等待，除非socket是非阻塞
            //ssize_t recv(int sockfd, void *buf, size_t len, int flags);
            //返回值是接收到的字节数目
            for (;;) {
                char buff[1024];
                memset(buff, '\0', sizeof(buff));
                int res = read(clientfd, buff, 1024);
                if (res == -1) {
                    printf("recv error\n");
                    continue;
                }
                printf("recv message:%s\n", buff);
            }
        }
    }

    return 0;
}
