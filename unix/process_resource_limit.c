#include <stdio.h>
#include <sys/resource.h>
/*
参考：UNIX环境高级编程
进程资源限制函数:
int getrlimit(int resource, struct rlimit *rlptr);
int setrlimit(int resource, const struct rlimit *rlptr);

resource:
RLIMIT_AS  进程总的可用存储空间的最大长度，影响到sbrk函数和mmap函数
RLIMIT_STACK 栈的最大字节长度
RLIMIT_CPU CPU时间的最大量值，超过此限制，向该进程发送SIGXCPU信号
RLIMIT_DATA 数据段的最大字节长度，为初始化数据，非初始化以及堆的总和
RLIMIT_NPROC 可拥有的最大子进程数。

进程的资源限制结构体信息
struct rlimit {
    rlim_t rlim_cur; //软限制，当前限制
    rlim_t rlim_max; //硬限制，rlim_cur软限制的最大限制
}
更改资源限制时：
1.任何一个进程都可将一个软限制值更改为小于或等于其硬限制值。
2.任何一个进程都可降低其硬限制值，但必须大于或等于软限制值，普通用户不可逆。
3.只有超级用户可以提高硬限制值。

RLIM_INFINITY 无限量的限制。
*/

#define doit(name) pr_limits(#name, name)  //#为字符串创建符，如doit(RLIMIT_AS)->pr_limits("RLIMIT_AS", RLIMIT_AS)
void pr_limits(char *, int);

int main() {
    doit(RLIMIT_AS);
    doit(RLIMIT_STACK);
    doit(RLIMIT_DATA);

    return 0;
}

void pr_limits(char *name, int resource) {
    struct rlimit limit;
    unsigned long long lim;
    if (getrlimit(resource, &limit) < 0) {
        printf("getrlimit error for %s\n", name);
        return;
    }
    printf("%-18s", name);
    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite)   "); //无限
    }else {
        lim = limit.rlim_cur;
        printf("%10lld  ", lim);
    }

    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)   "); //无限
    }else {
        lim = limit.rlim_max;
        printf("%10lld  ", lim);
    }
    printf("\n");
}


