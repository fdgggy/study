#include <stdio.h>

#define MAX_TREE_NODES (1 << 8)

struct node {
    int data;
};

struct binary_tree{
    union {
        unsigned long node;
        struct node *n[MAX_TREE_NODES];
    };
};

int main() {
    struct node n;
    struct binary_tree tree;
    printf("tree:%ld node:%ld\n", sizeof(tree), sizeof(n)); //2048,4

    

    return 0;
}