#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

/*
select 客户端程序
 */

int main(){
    printf("client start\n");
    int count = 0;
    int clientfd;
    extern int errno;
    count++;
    clientfd = socket(AF_INET, SOCK_STREAM, 0);  //创建套接字
    if (clientfd == -1) {
        char * mesg = strerror(errno);
        printf("create socket failed!count:%d\n", count);
        printf("errno:%d\n", errno);
        printf("errmsg:%s\n", mesg);
        return 0;
    }
    //@addr 服务器地址结构
    //int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    struct sockaddr_in servaddr; //地址格式描述
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;  //IPV4
    servaddr.sin_port = htons(123);
    //转换IP地址到网络地址结构
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    if(connect(clientfd, (struct sockaddr *)&servaddr,  sizeof(struct sockaddr_in)) == -1) {
        char * mesg = strerror(errno);
        printf("connect failed!\n");
        printf("errno:%d\n", errno);
        printf("errmsg:%s\n", mesg);
        return 0;
    }
    printf("connect success!\n");

    char sendBuf[1024];
    printf("fgets:%s!\n", sendBuf);

    while (fgets(sendBuf, 1024, stdin) != NULL) {
        //向另一个socket发送消息
        //ssize_t send(int sockfd, const void *buf, size_t len, int flags);
        if (send(clientfd, sendBuf, strlen(sendBuf), 0) < 0) {
            printf("send msg failed");
            return 0;
        }
    }

    close(clientfd);

    return 0;
}