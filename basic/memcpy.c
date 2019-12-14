#include <stdio.h>
#include <string.h>

int main() {
    char pc[] = "1234567890";
    char *p1 = pc;
    char *p2 = pc+1;


    memcpy(p2, p1, 5);
    // memmove(p2, p1, 5);
    printf("p2:%s\n", p2);

    return 0;
}