#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>


#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600  //user read/write

char array[ARRAY_SIZE];  //未初始化，bss段

int main() {
    int shmid;
    char *ptr, *shmptr;
    printf("array from %p to %p\n", (void*)&array[0], (void*)&array[ARRAY_SIZE]);
    printf("stack around %p\n", (void *)&shmid);

    if ((ptr = (char *)malloc(MALLOC_SIZE)) == NULL) {
        printf("malloc error\n");
        return -1;
    }
    printf("malloc from %p to %p\n", (void *)ptr, (void*)ptr+MALLOC_SIZE);

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) { //IPC_PRIVATE 保证创建一个新IPC结构。获得一个共享内存标识符
        printf("shmget error\n");
        return -1;
    }
    
    //把共享内存附加到进程地址空间，由内核选择第一个可用地址，这个地址不重要，每个进程都可以使用自己地址空间中的不同地址。可读可写。
    if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1) { 
        printf("shmat error\n");
        return -1;
    }
    printf("shared memory attached from %p to %p\n", (void *)shmptr, (void *)shmptr + SHM_SIZE);

    if (shmctl(shmid, IPC_RMID, 0) < 0) { //从系统中删除该共享内存
        printf("shmctl error\n");
        return -1;
    }

    return 0;
}


