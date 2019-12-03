/*
节点高度：节点到叶子节点的最长路径(边数)
节点深度：根节点到这个节点所经历的边的个数
节点层数：节点深度+1
树的高度：根节点的高度
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* lchild;
    struct node* rchild;
}Node, Tree;

void add_node(Node **tree, int data) {
    if (*tree == NULL) {
        Node *node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->lchild = node->rchild = NULL;
        *tree = node;

        return;
    }

    if (data <= (*tree)->data) {
        add_node(&(*tree)->lchild, data);
    }else {
        add_node(&(*tree)->rchild, data);
    }
}

//先序遍历 自身->左子树->右子树
void print_preorder(Node *tree) {
    if (tree == NULL) {
        return;
    }

    printf("data:%d\n", tree->data);
    print_preorder(tree->lchild);
    print_preorder(tree->rchild);
}

//中序遍历 左子树->自身->右子树
void print_inorder(Node *tree) {
    if (tree == NULL) {
        return;
    }

    print_preorder(tree->lchild);
    printf("data:%d\n", tree->data);
    print_preorder(tree->rchild);
}

//后序遍历 左子树->右子树->自身
void print_postorder(Node *tree) {
    if (tree == NULL) {
        return;
    }

    print_preorder(tree->lchild);
    print_preorder(tree->rchild);
    printf("data:%d\n", tree->data);
}

//输出叶子节点
void print_leaves(Node *tree) {
    if (tree) {
        if (!tree->lchild && !tree->rchild) {
            printf("%d ", tree->data);
        }
        print_leaves(tree->lchild);
        print_leaves(tree->rchild);
    }
}

//二叉树高度,根节点的高度
int print_tree_height(Node *tree) {
    int hl, hr, maxh;
    if (!tree) {
        return 0;
    }else{
        hl = print_tree_height(tree->lchild); //左子树高度
        hr = print_tree_height(tree->rchild); //右子树高度
        maxh = (hl > hr) ? hl : hr;
        return maxh + 1;   //? 高度是否需要加1
    }
}
//TODO 层级遍历，队列.  遍历非递归需用堆栈

int main() {
    Tree tree = { .data = 9, .lchild = NULL, .rchild = NULL };
    Tree *t = &tree; 
    add_node(&t, 5);
    add_node(&t, 2);
    add_node(&t, 1);
    add_node(&t, 5);

    printf("---------------前序\n");
    print_preorder(t);
    printf("---------------中序\n");
    print_inorder(t);
    printf("---------------后序\n");
    print_postorder(t);

    printf("---------------叶子\n");
    print_leaves(t);
    printf("\n");

    printf("---------------树高\n");
    int h = print_tree_height(t);
    printf("h:%d\n", h);
    printf("\n");

    return 0;
}





