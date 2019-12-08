#ifndef __BINARY_SEARCH_TREE_
#define __BINARY_SEARCH_TREE_

#define is_empty(tree) (tree->size == 0)

typedef int (*comp)(int a, int b);

typedef struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
}bs_node;

typedef struct tree
{
    bs_node *root;
    comp cp;
    int size;
}bs_tree;


#endif 