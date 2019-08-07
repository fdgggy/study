#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

int main() {
    printf("server start\n");
    int listenfd;

    //int socket(int domain, int type, int protocol);
    //创建一个通信端点并返回一个引用该端点的文件描述符
    //@domain(通信域),用于通信的协议簇
    //AF_UNIX      Local communication 
    //AF_INET      IPv4 Internet protocols
    //AF_INET6     IPv6 Internet protocols
    //@type 套接字指示类型，制定通信的语义
    //SOCK_STREAM 有序，可靠，双向，基于连接的字节流   TCP
    //SOCK_DGRAM 数据报,无连接，不可靠，具有固定最大长度  UDP
    //@protocol 特定协议，只有一个协议指定填0
    listenfd = socket(AF_INET, SOCK_STREAM, 0);  //创建套接字
    if (listenfd == -1) {
        printf("create socket failed!")
        return
    }
    printf("create socket success, listenfd:%d\n", listenfd);

    //int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen); 为套接字分配名称
    //套接字创建后保存在一个名字空间但并没有地址分配给他，bind通过addr参数分配地址给sockfd所引用的套接字

    struct sockaddr_in servaddr; //地址格式描述
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET  //IPV4
    servaddr

    return 0;
}
